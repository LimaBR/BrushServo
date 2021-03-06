#include "Motor.hpp"

//Constructors
Motor::Motor(){
    bts0 = new BTS7960(2, 3, 4, 5);
    bts0->init();
    bts0->setEnabled(true);
    uint32_t offset = pio_add_program(pio0, &quadrature_encoder_program);
    encoder0 = new Encoder(pio0, 0, offset, 16, 0);
    encoder0->program_init();
    add_repeating_timer_us(-100000, Motor::updateSpeed, this, &timer0);
}

void Motor::controlSpeed(float speed){
    if(speed>1){
        bts0->setSpeed(255);
    }else{
        bts0->setSpeed((int32_t)(speed*255));
    }
}

float Motor::readSpeed(){
    float speed = (value - oldvalue)*10*2*3.1415926535/2800;
    return speed;
}

bool Motor::updateSpeed(struct repeating_timer *t){
    ((Motor*)(t->user_data))->oldvalue = ((Motor*)(t->user_data))->value;
    ((Motor*)(t->user_data))->value = ((Motor*)(t->user_data))->encoder0->get_count();
    return true;
}