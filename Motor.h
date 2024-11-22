#ifndef MOTOR_H
#define MOTOR_H

#include <stdbool.h>

void motor_init(int in1_pin_1, int in2_pin_1, int enable_pin_1,int in3_pin_2, int in4_pin_2, int enable_pin_2);

void motor_set_direction(int pin1,int pin2, bool forward);

void motor_start();

void motor_stop();

#endif 
