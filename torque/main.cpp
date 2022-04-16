#include "main.hpp"

//Standard libraries
#include <stdio.h>

//Project libraries
#include "Motor.hpp"
#include "output.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

//Global variables
Motor* motor0;
OmegaOutput sendPacket;
uint8_t sendBuffer[64];

//Global objects

//Main function
int main(){
    stdio_init_all();
    uart_init(uart0, 921600);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    uart_puts(uart0, "Hello world!");
    motor0 = new Motor();
    motor0->controlSpeed(-0.25);
    while(true){
        float omega = motor0->readSpeed();
        printf("Value: %f\n", omega);
        sendPacket.omega = omega;
        sendPacket.current = 0;
        pb_ostream_t stream = pb_ostream_from_buffer(sendBuffer, 64);
        pb_encode (&stream, OmegaOutput_fields, &sendPacket);
        uart_write_blocking(uart0, sendBuffer, 64);
        sleep_ms(100);
    }
}
