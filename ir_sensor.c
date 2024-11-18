#include "pico/stdlib.h"
#include "ir_sensor.h"

static int ir_sensor_pin;

void ir_sensor_init(int pin) {
    ir_sensor_pin = pin;
    gpio_init(ir_sensor_pin);
    gpio_set_dir(ir_sensor_pin, GPIO_IN);
}

bool ir_sensor_detect() {
    return gpio_get(ir_sensor_pin);  // Returns true if an object is detected
}
