#include "pico/stdlib.h"
#include "button.h"

static int button_pin;

void button_init(int pin) {
    button_pin = pin;
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);  // Use pull-up resistor
}

bool button_is_pressed() {
    return !gpio_get(button_pin);  // Active low button
}
