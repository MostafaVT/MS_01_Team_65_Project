#include "pico/stdlib.h"
#include "conveyor_belt.h"
#include "ir_sensor.h"
#include "servo.h"
#include "button.h"
#include <stdio.h>

static int ir_sensor_pin;
static int servo1_pin;
static int servo2_pin;
static int button_pin;

static int object_count = 0;

void conveyor_belt_init(int ir_pin, int servo1, int servo2, int button) {

    ir_sensor_pin = ir_pin;

    servo1_pin = servo1;
    servo2_pin = servo2;

    button_pin = button;

    ir_sensor_init(ir_sensor_pin);

    servo_init(servo1_pin);
    servo_init(servo2_pin);

    button_init(button_pin);

    servo_set_angle(servo1_pin, 0);
    servo_set_angle(servo2_pin, 0);
}

void conveyor_belt_run() {

    if (ir_sensor_detect()) {
        
        object_count++;
        printf("Objects Count: %d\n", object_count);

        printf("Opening servos...\n");
        servo_set_angle(servo1_pin, 90);
        servo_set_angle(servo2_pin, 90);
        sleep_ms(3000);

        printf("Closing servos...\n");
        servo_set_angle(servo1_pin, 0);
        servo_set_angle(servo2_pin, 0);
        
    }
}
