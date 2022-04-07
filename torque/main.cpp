#include "main.hpp"

//Standard libraries
#include <stdio.h>

//Project libraries
#include "Motor.hpp"

//Global variables
Motor* motor0;

//Global objects

//Main function
int main(){
    stdio_init_all();
    motor0 = new Motor();
    motor0->controlSpeed(0.25);
    while(true){
        float omega = motor0->readSpeed();
        printf("Value: %f\n", omega);
        sleep_ms(100);
    }
}
