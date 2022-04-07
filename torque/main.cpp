#include "main.hpp"

//Standard libraries
#include <stdio.h>

//Project libraries
#include "Encoder.hpp"

//Global variables
uint32_t offset;

//Global objects

//Main function
int main(){
    stdio_init_all();
    offset = pio_add_program(pio0, &quadrature_encoder_program);
    Encoder* encoder0 = new Encoder(pio0, 0, offset, 16, 0);
    encoder0->program_init();
    while(true){
        int32_t value = encoder0->get_count();
        printf("Value: %ld\n", value);
        sleep_ms(100);
    }
}
