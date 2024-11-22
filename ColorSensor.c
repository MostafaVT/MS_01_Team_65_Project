#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "ColorSensor.h"

static int _s0, _s1, _s2, _s3, _out_pin;

void color_sensor_init(int s0, int s1, int s2, int s3, int out_pin) {
    _s0 = s0;
    _s1 = s1;
    _s2 = s2;
    _s3 = s3;
    _out_pin = out_pin;

    // Configure control pins
    gpio_init(s0);
    gpio_init(s1);
    gpio_init(s2);
    gpio_init(s3);
    gpio_set_dir(s0, GPIO_OUT);
    gpio_set_dir(s1, GPIO_OUT);
    gpio_set_dir(s2, GPIO_OUT);
    gpio_set_dir(s3, GPIO_OUT);

    // Configure output pin
    gpio_init(out_pin);
    gpio_set_dir(out_pin, GPIO_IN);
    gpio_pull_up(out_pin);

    // Set frequency scaling to 20%
    gpio_put(s0, 1);
    gpio_put(s1, 0);
}

int read_color_frequency(int out_pin) {
    uint32_t start_time = to_ms_since_boot(get_absolute_time());
    uint32_t pulse_count = 0;

    // Count pulses in 100ms
    while (to_ms_since_boot(get_absolute_time()) - start_time < 100) {
        while (gpio_get(out_pin) == 0);  // Wait for HIGH
        while (gpio_get(out_pin) == 1);  // Wait for LOW
        pulse_count++;
    }

    return pulse_count * 10;  // Scale to 1 second
}
