#include "Motor.hpp"

//Constructors
Motor::Motor(){
    bts0 = new BTS7960(2, 3, 4, 5);
    bts0->init();
    uint32_t offset = pio_add_program(pio0, &quadrature_encoder_program);
    encoder0 = new Encoder(pio0, 0, offset, 16, 0);
    encoder0->program_init();
}

void Motor::ControlSpeed(float speed){

}