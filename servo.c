#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "servo.h"
#include <stdio.h>

// #define ROTATE_0_SERVO_1_PIN_17 2250
// #define ROTATE_180_SERVO_1_PIN_17 350

// #define ROTATE_0_SERVO_2_PIN_16 2250
// #define ROTATE_180_SERVO_2_PIN_16 350

#define ROTATE_0_SERVO_1_PIN_17 2000
#define ROTATE_180_SERVO_1_PIN_17 350

#define ROTATE_0_SERVO_2_PIN_16 2000
#define ROTATE_180_SERVO_2_PIN_16 350

void servo_init(int pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    uint32_t const SYS_CLK_hz = clock_get_hz(clk_sys);
    uint32_t const PWM_CLK_hz = 1*1000*1000UL;

    float const clk_divider = (float)SYS_CLK_hz / (float)PWM_CLK_hz;

    pwm_set_clkdiv(slice_num, clk_divider);

    /* Set system period to 20 ms. */
    pwm_set_wrap(slice_num, 20000);

    pwm_set_enabled(slice_num, true);
}

void servo_set_angle(int pin, int angle) {
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Map angle (0-180) to pulse width (1ms to 2ms)
    if(pin == 16){
        uint level = (((float)(ROTATE_180_SERVO_2_PIN_16 - ROTATE_0_SERVO_2_PIN_16) / 180.0) * angle) + ROTATE_0_SERVO_2_PIN_16;
        pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), level);

        }
    else if (pin == 17){
        uint level = (((float)(ROTATE_180_SERVO_1_PIN_17 - ROTATE_0_SERVO_1_PIN_17) / 180.0) * angle) + ROTATE_0_SERVO_1_PIN_17;
        pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), level);
    }
}

