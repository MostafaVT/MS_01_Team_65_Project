#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "Motor.h"

static int motor1_in1_pin_1;
static int motor1_in2_pin_1;
static int motor1_enable_pin_1;

static int motor2_in3_pin_2;
static int motor2_in4_pin_2;
static int motor2_enable_pin_2;

void motor_init(
    int in1_pin_1, int in2_pin_1, int enable_pin_1
    ,int in3_pin_2, int in4_pin_2, int enable_pin_2) {

    motor1_in1_pin_1 = in1_pin_1;
    motor1_in2_pin_1 = in2_pin_1;
    motor1_enable_pin_1 = enable_pin_1;

    motor2_in3_pin_2 = in3_pin_2;
    motor2_in4_pin_2 = in4_pin_2;
    motor2_enable_pin_2 = enable_pin_2;

    gpio_init(motor1_in1_pin_1);
    gpio_init(motor1_in2_pin_1);
    gpio_init(motor1_enable_pin_1);
    gpio_set_dir(motor1_in1_pin_1, GPIO_OUT);
    gpio_set_dir(motor1_in2_pin_1, GPIO_OUT);
    gpio_set_dir(motor1_enable_pin_1, GPIO_OUT);

    gpio_init(motor2_in3_pin_2);
    gpio_init(motor2_in4_pin_2);
    gpio_init(motor2_enable_pin_2);
    gpio_set_dir(motor2_in3_pin_2, GPIO_OUT);
    gpio_set_dir(motor2_in4_pin_2, GPIO_OUT);
    gpio_set_dir(motor2_enable_pin_2, GPIO_OUT);
    

    motor_stop();
}

void motor_start(){
    gpio_put(motor1_enable_pin_1, 1);
    gpio_put(motor2_enable_pin_2, 1);

}

void motor_set_direction(int pin1,int pin2,bool forward) {
    if (forward) {
        gpio_put(pin1, 1);
        gpio_put(pin2, 0);
    } else {
        gpio_put(pin1, 0);
        gpio_put(pin2, 1);
    }
}

void motor_stop() {
    gpio_put(motor1_in1_pin_1, 0);
    gpio_put(motor1_in2_pin_1, 0);

    gpio_put(motor2_in3_pin_2, 0);
    gpio_put(motor2_in4_pin_2, 0);
}
