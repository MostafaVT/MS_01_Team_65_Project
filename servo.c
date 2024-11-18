#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo.h"

void servo_init(int pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 20000);  // Period for a 50Hz servo signal
    pwm_set_enabled(slice_num, true);
}

void servo_set_angle(int pin, int angle) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint level = (angle * 10) + 500;  // Map angle to 500-2500 microseconds
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), level);
}
