#include <stdio.h>
#include "pico/stdlib.h"
#include "led.h"

int main() {
    stdio_init_all(); 

    led_init(); 

    led_sequence();

    return 0;
}
