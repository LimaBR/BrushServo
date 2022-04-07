#ifndef __MOTOR_HPP
#define __MOTOR_HPP

#include "main.hpp"

#include "bts7960.hpp"
#include "Encoder.hpp"

class Motor{
public:
    Motor();
    void controlSpeed(float speed);
    float readSpeed();
private:
    static bool updateSpeed(struct repeating_timer *t);
    BTS7960* bts0;
    Encoder* encoder0;
    struct repeating_timer timer0;
    int32_t oldvalue;
    int32_t value;
};

#endif