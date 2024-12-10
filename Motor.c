#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "Motor.h"

static int motor1_in1_pin_1;
static int motor1_in2_pin_1;
static int motor1_enable_pin_1;

static int motor2_in3_pin_2;
static int motor2_in4_pin_2;
static int motor2_enable_pin_2;

// PWM slice numbers
static uint motor1_pwm_slice;
static uint motor2_pwm_slice;

void motor_init(
    int in1_pin_1, int in2_pin_1, int enable_pin_1,
    int in3_pin_2, int in4_pin_2, int enable_pin_2) {

    motor1_in1_pin_1 = in1_pin_1;
    motor1_in2_pin_1 = in2_pin_1;
    motor1_enable_pin_1 = enable_pin_1;

    motor2_in3_pin_2 = in3_pin_2;
    motor2_in4_pin_2 = in4_pin_2;
    motor2_enable_pin_2 = enable_pin_2;

    // Initialize IN1, IN2 pins for both motors
    gpio_init(motor1_in1_pin_1);
    gpio_init(motor1_in2_pin_1);
    gpio_set_dir(motor1_in1_pin_1, GPIO_OUT);
    gpio_set_dir(motor1_in2_pin_1, GPIO_OUT);

    gpio_init(motor2_in3_pin_2);
    gpio_init(motor2_in4_pin_2);
    gpio_set_dir(motor2_in3_pin_2, GPIO_OUT);
    gpio_set_dir(motor2_in4_pin_2, GPIO_OUT);

    // Configure ENABLE pins as PWM
    gpio_set_function(motor1_enable_pin_1, GPIO_FUNC_PWM);
    gpio_set_function(motor2_enable_pin_2, GPIO_FUNC_PWM);

    motor1_pwm_slice = pwm_gpio_to_slice_num(motor1_enable_pin_1);
    motor2_pwm_slice = pwm_gpio_to_slice_num(motor2_enable_pin_2);

    // Configure PWM for both motors
    pwm_config config = pwm_get_default_config();

    // Set the top value for 16-bit resolution
    uint16_t top = 65535;
    pwm_set_wrap(motor1_pwm_slice, top);
    pwm_set_wrap(motor2_pwm_slice, top);

    // Calculate clock divider for 1 kHz
    float clk_divider = (float)clock_get_hz(clk_sys) / (1250 * top);
    pwm_config_set_clkdiv(&config, clk_divider);

    // Initialize PWM slices with configuration
    pwm_init(motor1_pwm_slice, &config, true);
    pwm_init(motor2_pwm_slice, &config, true);

    // Set initial PWM level to 0 (motors off)
    pwm_set_gpio_level(motor1_enable_pin_1, 0);
    pwm_set_gpio_level(motor2_enable_pin_2, 0);

    motor_stop();
}


void motor_set_speed(int motor_num, float speed) {
    // Clamp speed between 0.0 (0%) and 1.0 (100%)
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;

    uint16_t pwm_level = (uint16_t)(speed * 65535.0f); // Scale to 16-bit PWM level

    if (motor_num == 1) {
        pwm_set_gpio_level(motor1_enable_pin_1, pwm_level);
    } else if (motor_num == 2) {
        pwm_set_gpio_level(motor2_enable_pin_2, pwm_level);
    }
}

void motor_set_direction(int motor_num, bool forward) {
    if (motor_num == 1) {
        gpio_put(motor1_in1_pin_1, forward ? 1 : 0);
        gpio_put(motor1_in2_pin_1, forward ? 0 : 1);
    } else if (motor_num == 2) {
        gpio_put(motor2_in3_pin_2, forward ? 1 : 0);
        gpio_put(motor2_in4_pin_2, forward ? 0 : 1);
    }
}

void motor_start() {
    motor_set_speed(1, 1.0f); // Full speed for motor 1
    motor_set_speed(2, 1.0f); // Full speed for motor 2
}

void motor_stop() {
    // Stop motor 1
    gpio_put(motor1_in1_pin_1, 0);
    gpio_put(motor1_in2_pin_1, 0);
    pwm_set_gpio_level(motor1_enable_pin_1, 0);

    // Stop motor 2
    gpio_put(motor2_in3_pin_2, 0);
    gpio_put(motor2_in4_pin_2, 0);
    pwm_set_gpio_level(motor2_enable_pin_2, 0);
}


// // Motor GPIO pins
// static int motor1_in1_pin_1;
// static int motor1_in2_pin_1;
// static int motor1_enable_pin_1;

// static int motor2_in3_pin_2;
// static int motor2_in4_pin_2;
// static int motor2_enable_pin_2;

// void motor_init(
//     int in1_pin_1, int in2_pin_1, int enable_pin_1,
//     int in3_pin_2, int in4_pin_2, int enable_pin_2) {

//     motor1_in1_pin_1 = in1_pin_1;
//     motor1_in2_pin_1 = in2_pin_1;
//     motor1_enable_pin_1 = enable_pin_1;

//     motor2_in3_pin_2 = in3_pin_2;
//     motor2_in4_pin_2 = in4_pin_2;
//     motor2_enable_pin_2 = enable_pin_2;

//     // Initialize all motor control pins as outputs
//     gpio_init(motor1_in1_pin_1);
//     gpio_init(motor1_in2_pin_1);
//     gpio_init(motor1_enable_pin_1);
//     gpio_set_dir(motor1_in1_pin_1, GPIO_OUT);
//     gpio_set_dir(motor1_in2_pin_1, GPIO_OUT);
//     gpio_set_dir(motor1_enable_pin_1, GPIO_OUT);

//     gpio_init(motor2_in3_pin_2);
//     gpio_init(motor2_in4_pin_2);
//     gpio_init(motor2_enable_pin_2);
//     gpio_set_dir(motor2_in3_pin_2, GPIO_OUT);
//     gpio_set_dir(motor2_in4_pin_2, GPIO_OUT);
//     gpio_set_dir(motor2_enable_pin_2, GPIO_OUT);

//     motor_stop();
// }

// void motor_set_direction(int motor_num, bool forward) {
//     if (motor_num == 1) {
//         gpio_put(motor1_in1_pin_1, forward ? 1 : 0);
//         gpio_put(motor1_in2_pin_1, forward ? 0 : 1);
//     } else if (motor_num == 2) {
//         gpio_put(motor2_in3_pin_2, forward ? 1 : 0);
//         gpio_put(motor2_in4_pin_2, forward ? 0 : 1);
//     }
// }

// void motor_start() {
//     // Enable both motors (constant HIGH)
//     gpio_put(motor1_enable_pin_1, 1);
//     gpio_put(motor2_enable_pin_2, 1);
// }

// void motor_stop() {
//     // Stop motor 1
//     gpio_put(motor1_in1_pin_1, 0);
//     gpio_put(motor1_in2_pin_1, 0);
//     gpio_put(motor1_enable_pin_1, 0);

//     // Stop motor 2
//     gpio_put(motor2_in3_pin_2, 0);
//     gpio_put(motor2_in4_pin_2, 0);
//     gpio_put(motor2_enable_pin_2, 0);
// }