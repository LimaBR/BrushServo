#include "bts7960.hpp"

#include <hardware/pwm.h>

BTS7960::BTS7960(uint32_t len_pin, uint32_t ren_pin, uint32_t lpwm_pin, uint32_t rpwm_pin) : 
    len_pin(len_pin), ren_pin(ren_pin), lpwm_pin(lpwm_pin), rpwm_pin(rpwm_pin){

}

void BTS7960::init(){
    lpwm_slice = pwm_gpio_to_slice_num(lpwm_pin);
    lpwm_channel = pwm_gpio_to_channel(lpwm_pin);
    rpwm_slice = pwm_gpio_to_slice_num(rpwm_pin);
    rpwm_channel = pwm_gpio_to_channel(rpwm_pin);
    gpio_init(len_pin);
    gpio_init(ren_pin);
    gpio_init(lpwm_pin);
    gpio_init(rpwm_pin);
    gpio_set_function(len_pin, GPIO_FUNC_SIO);
    gpio_set_function(ren_pin, GPIO_FUNC_SIO);
    gpio_set_function(lpwm_pin, GPIO_FUNC_PWM);
    gpio_set_function(rpwm_pin, GPIO_FUNC_PWM);
    gpio_set_dir(len_pin, GPIO_OUT);
    gpio_set_dir(ren_pin, GPIO_OUT);
    gpio_put(len_pin, false);
    gpio_put(ren_pin, false);
    pwm_set_clkdiv_int_frac(lpwm_slice, 128, 0);
    pwm_set_clkdiv_int_frac(rpwm_slice, 128, 0);
    pwm_set_wrap(lpwm_slice, 255);
    pwm_set_wrap(rpwm_slice, 255);
    pwm_set_chan_level(lpwm_slice, lpwm_channel, 0);
    pwm_set_chan_level(rpwm_slice, rpwm_channel, 0);
    pwm_set_enabled(lpwm_slice, true);
    pwm_set_enabled(rpwm_slice, true);
}

void BTS7960::setEnabled(bool enabled){
    if(enabled){
        gpio_put(len_pin, true);
        gpio_put(ren_pin, true);
    }else{
        gpio_put(len_pin, false);
        gpio_put(ren_pin, false);
    }
}

void BTS7960::setSpeed(int32_t speed){
    if(speed < 0){
        //ré
        pwm_set_chan_level(lpwm_slice, lpwm_channel, 0);
        pwm_set_chan_level(rpwm_slice, rpwm_channel, -speed);
    }else{
        //frente
        pwm_set_chan_level(lpwm_slice, lpwm_channel, speed);
        pwm_set_chan_level(rpwm_slice, rpwm_channel, 0);
    }
}