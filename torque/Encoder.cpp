#include "Encoder.hpp"

//Constructors
Encoder::Encoder(PIO pio, uint sm, uint offset, uint pin, int max_step_rate) : 
    pio(pio), sm(sm), offset(offset), pin(pin), max_step_rate(max_step_rate)
{

}

void Encoder::program_init()
{
	pio_sm_set_consecutive_pindirs(pio, sm, pin, 2, false);
	pio_gpio_init(pio, pin);
	gpio_pull_up(pin);

	pio_sm_config c = quadrature_encoder_program_get_default_config(offset);
	sm_config_set_in_pins(&c, pin); // for WAIT, IN
	sm_config_set_jmp_pin(&c, pin); // for JMP
	// shift to left, autopull disabled
	sm_config_set_in_shift(&c, false, false, 32);
	// don't join FIFO's
	sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_NONE);

	// passing "0" as the sample frequency,
	if (max_step_rate == 0) {
		sm_config_set_clkdiv(&c, 1.0);
	} else {
		// one state machine loop takes at most 14 cycles
		float div = (float)clock_get_hz(clk_sys) / (14 * max_step_rate);
		sm_config_set_clkdiv(&c, div);
	}

	pio_sm_init(pio, sm, offset, &c);
	pio_sm_set_enabled(pio, sm, true);
}


// When requesting the current count we may have to wait a few cycles (average
// ~11 sysclk cycles) for the state machine to reply. If we are reading multiple
// encoders, we may request them all in one go and then fetch them all, thus
// avoiding doing the wait multiple times. If we are reading just one encoder,
// we can use the "get_count" function to request and wait

void Encoder::request_count()
{
	pio->txf[sm] = 1;
}

int32_t Encoder::fetch_count()
{
	while (pio_sm_is_rx_fifo_empty(pio, sm))
		tight_loop_contents();
	return pio->rxf[sm];
}

int32_t Encoder::get_count()
{
	request_count();
	return fetch_count();
}