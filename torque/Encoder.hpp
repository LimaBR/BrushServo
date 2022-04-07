#ifndef __ENCODER_HPP
#define __ENCODER_HPP

#include "main.hpp"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "Encoder.pio.h"

class Encoder{
public:
    Encoder(PIO pio, uint sm, uint offset, uint pin, int max_step_rate);
    void program_init();
    void request_count();
    int32_t fetch_count();
    int32_t get_count();
private:
    PIO pio;
    uint sm;
    uint offset;
    uint pin;
    int max_step_rate;
};

#endif