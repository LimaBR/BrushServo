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
    while(true){
        int32_t value = (int32_t)motor0->readSpeed();
        printf("Value: %ld\n", value);
        sleep_ms(100);
    }
}
