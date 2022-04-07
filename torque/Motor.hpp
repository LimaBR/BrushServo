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
    BTS7960* bts0;
    Encoder* encoder0;
};

#endif