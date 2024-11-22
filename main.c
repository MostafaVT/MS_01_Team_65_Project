#include "pico/stdlib.h"
#include "conveyor_belt.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "fsr.h"
#include <stdio.h>

// IR SENSOR PIN
#define IR_SENSOR_PIN 6
// SERVO PINS
#define SERVO1_PIN 17
#define SERVO2_PIN 16
// BUTTON PIN
#define BUTTON_PIN 25
// MOTOR 1 PINS
#define MOTOR1_IN1_PIN 18
#define MOTOR1_IN2_PIN 19
#define MOTOR1_ENABLE_PIN 20
// MOTOR 2 PINS
#define MOTOR2_IN3_PIN 21
#define MOTOR2_IN4_PIN 5
#define MOTOR2_ENABLE_PIN 7
// COLOR SENSOR PINS
#define S0_PIN 26
#define S1_PIN 27
#define S2_PIN 28
#define S3_PIN 29
#define OUT_PIN 12
// FSR PIN
// #define FSR_PIN 13  // ADC5
/* CANT WORK WITH COLOR SENSOR DUE TO PIN CONFLICT [for now ....]*/
#define FSR_PIN 29  // ADC3 


int main() {
    stdio_init_all();

    // // Motor test

    // motor_init(
    //     MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, MOTOR1_ENABLE_PIN,
    //     MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, MOTOR2_ENABLE_PIN);
    
    // motor_start();

    // while (1) {
    //     motor_set_direction(MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, true);
    //     motor_set_direction(MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, true);
    // }

    ///////////////////////////////////////////////////////////////////////////

    // //IR Sensor test AND SERVO test

    // conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);

    // while (1) {
    //     conveyor_belt_run();
    // }

    ///////////////////////////////////////////////////////////////////////////
    
    // Color sensor test

    color_sensor_init(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

    while (1) {
        // Select RED filter
        gpio_put(S2_PIN, 0);
        gpio_put(S3_PIN, 0);
        int red = read_color_frequency(OUT_PIN);

        // Select GREEN filter
        gpio_put(S2_PIN, 1);
        gpio_put(S3_PIN, 1);
        int green = read_color_frequency(OUT_PIN);

        // Select BLUE filter
        gpio_put(S2_PIN, 0);
        gpio_put(S3_PIN, 1);
        int blue = read_color_frequency(OUT_PIN);

        printf("Color: ");
        printf("R: %d, G: %d, B: %d\n", red, green, blue);
        sleep_ms(1000);

    }

    ///////////////////////////////////////////////////////////////////////////    
    
    // // Force Sensitive Resistor test

    // fsr_init(FSR_PIN);

    // while (true) {
    //     float weight = fsr_read_weight();
    //     printf("Weight: %.2f \n", weight);

    //     float voltage = fsr_read_voltage();
    //     printf("FSR Voltage: %.2f V\n", voltage);

    //     printf("-------------------------------------------\n");      
    //     sleep_ms(500);
    // }

    return 0;
}
