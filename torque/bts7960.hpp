#ifndef __BTS7960_HPP
#define __BTS7960_HPP

#include "main.hpp"

class BTS7960{
    public:
    BTS7960(uint32_t len_pin, uint32_t ren_pin, uint32_t lpwm_pin, uint32_t rpwm_pin);
    void init();
    void setEnabled(bool enabled);
    void setSpeed(int32_t speed);
    private:
    uint32_t len_pin;
    uint32_t ren_pin;
    uint32_t lpwm_pin;
    uint32_t rpwm_pin;
    uint32_t lpwm_slice;
    uint32_t lpwm_channel;
    uint32_t rpwm_slice;
    uint32_t rpwm_channel;
};

#endif