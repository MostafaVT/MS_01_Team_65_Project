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
// #define S3_PIN 29
#define S3_PIN 4
#define OUT_PIN 12
// FSR PIN
// #define FSR_PIN 13  // ADC5
/* CANT WORK WITH COLOR SENSOR DUE TO PIN CONFLICT [for now ....]*/
#define FSR_PIN 29  // ADC3 


// int main() {
//     stdio_init_all();

//     // Motor test

//     // motor_init(
//     //     MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, MOTOR1_ENABLE_PIN,
//     //     MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, MOTOR2_ENABLE_PIN);
    
//     // motor_start();

//     // while (1) {
//     //     motor_set_direction(MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, true);
//     //     motor_set_direction(MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, true);
//     // } 

//     ///////////////////////////////////////////////////////////////////////////

//     //IR Sensor test AND SERVO test

//     conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);

//     // while (1) {
//     //     conveyor_belt_run();
//     // }

//     ///////////////////////////////////////////////////////////////////////////
    
//     // Color sensor test with FSR sensor and 

//     color_sensor_init(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

//     fsr_init(FSR_PIN);


//     while (1) {
//         conveyor_belt_run();

//         float weight = fsr_read_weight();
//         printf("Weight: %.2f \n", weight);

//         float voltage = fsr_read_voltage();
//         printf("FSR Voltage: %.2f V\n", voltage);

//         printf("-------------------------------------------\n");      
//         sleep_ms(1000);


//         // Select RED filter
//         gpio_put(S2_PIN, 0);
//         gpio_put(S3_PIN, 0);
//         int red = read_color_frequency(OUT_PIN);

//         // Select GREEN filter
//         gpio_put(S2_PIN, 1);
//         gpio_put(S3_PIN, 1);
//         int green = read_color_frequency(OUT_PIN);

//         // Select BLUE filter
//         gpio_put(S2_PIN, 0);
//         gpio_put(S3_PIN, 1);
//         int blue = read_color_frequency(OUT_PIN);

//         printf("Color: ");
//         printf("R: %d, G: %d, B: %d\n", red, green, blue);
//         sleep_ms(1000);

//     }

//     ///////////////////////////////////////////////////////////////////////////    
    
//     // // Force Sensitive Resistor test

//     // fsr_init(FSR_PIN);

//     // while (true) {
//         // float weight = fsr_read_weight();
//         // printf("Weight: %.2f \n", weight);

//         // float voltage = fsr_read_voltage();
//         // printf("FSR Voltage: %.2f V\n", voltage);

//         // printf("-------------------------------------------\n");      
//         // sleep_ms(500);
//     // }

//     return 0;
// }

int main() {
    stdio_init_all();

    motor_init(
        MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, MOTOR1_ENABLE_PIN,
        MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, MOTOR2_ENABLE_PIN);

    // conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);


    // color_sensor_init(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);


    // fsr_init(FSR_PIN);


    while (1) {

        // conveyor_belt_run();

        // // Motor 1: Forward at 50% speed
        // motor_set_direction(1, true);  // Forward
        // motor_set_speed(1, 1.0f);      // 50% speed

        // // // Motor 2: Backward at 75% speed
        // motor_set_direction(2, false); // Backward
        // motor_set_speed(2, 1.0f);     // 75% speed

        // sleep_ms(5000); // Run for 5 seconds

        // // Stop motors
        // motor_stop();

        // // Pause for 2 seconds
        // sleep_ms(2000);

        // // Reverse motor directions
        // motor_set_direction(1, false); // Motor 1: Backward
        // motor_set_speed(1, 1.0f);      // 30% speed

        // motor_set_direction(2, true);  // Motor 2: Forward
        // motor_set_speed(2, 0.6f);      // 60% speed

        // sleep_ms(5000); // Run for 5 seconds

        // // Stop motors again
        // motor_stop();

        // sleep_ms(2000); // Pause before next cycle
//////////////////////////////////////////////////////////
        // Move motors forward
        motor_set_direction(1, true);  // Motor 1 forward
        motor_set_direction(2, true);  // Motor 2 forward
        motor_start();
        sleep_ms(2000);

        // Stop motors
        motor_stop();
        sleep_ms(500);

        // Move motors in reverse
        motor_set_direction(1, false);  // Motor 1 reverse
        motor_set_direction(2, false);  // Motor 2 reverse
        motor_start();
        sleep_ms(2000);

        // Stop motors
        motor_stop();
        sleep_ms(500);
//////////////////////////////////////////////////////////
        // float weight = fsr_read_weight();
        // printf("Weight: %.2f \n", weight);

        // float voltage = fsr_read_voltage();
        // printf("FSR Voltage: %.2f V\n", voltage);

        // printf("-------------------------------------------\n");      
        // sleep_ms(1000);

        // // Select RED filter
        // gpio_put(S2_PIN, 0);
        // gpio_put(S3_PIN, 0);
        // int red = read_color_frequency(OUT_PIN);

        // // Select GREEN filter
        // gpio_put(S2_PIN, 1);
        // gpio_put(S3_PIN, 1);
        // int green = read_color_frequency(OUT_PIN);

        // // Select BLUE filter
        // gpio_put(S2_PIN, 0);
        // gpio_put(S3_PIN, 1);
        // int blue = read_color_frequency(OUT_PIN);

        // printf("Color: ");
        // printf("R: %d, G: %d, B: %d\n", red, green, blue);
        // sleep_ms(1000);

    }

    return 0;
}
///////////////////////////______RTOS_______////////////////////////////////////////////////////
// #include "pico/stdlib.h"
// #include "conveyor_belt.h"
// #include "Motor.h"
// #include "ColorSensor.h"
// #include "FreeRTOS.h"
// #include "task.h"
// #include "semphr.h"
// #include "fsr.h"
// #include <stdio.h>

// // Pins definitions
// #define IR_SENSOR_PIN 6
// #define SERVO1_PIN 17
// #define SERVO2_PIN 16
// #define BUTTON_PIN 25
// #define MOTOR1_IN1_PIN 18
// #define MOTOR1_IN2_PIN 19
// #define MOTOR1_ENABLE_PIN 20
// #define MOTOR2_IN3_PIN 21
// #define MOTOR2_IN4_PIN 5
// #define MOTOR2_ENABLE_PIN 7
// #define S0_PIN 26
// #define S1_PIN 27
// #define S2_PIN 28
// #define S3_PIN 4
// #define OUT_PIN 12
// #define FSR_PIN 29

// // Task priorities
// #define CONVEYOR_TASK_PRIORITY 2
// #define SENSOR_TASK_PRIORITY 2
// #define SERVO_TASK_PRIORITY 1
// #define COLOR_TASK_PRIORITY 1

// // Task handles (optional, useful for management)
// TaskHandle_t conveyorTaskHandle = NULL;
// TaskHandle_t sensorTaskHandle = NULL;
// TaskHandle_t servoTaskHandle = NULL;
// TaskHandle_t colorTaskHandle = NULL;

// // Function prototypes
// void conveyor_belt_task(void *pvParameters);
// void sensor_task(void *pvParameters);
// void color_sensor_task(void *pvParameters);

// void init_hardware() {
//     motor_init(
//         MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, MOTOR1_ENABLE_PIN,
//         MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, MOTOR2_ENABLE_PIN
//     );

//     conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);
//     color_sensor_init(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);
//     fsr_init(FSR_PIN);
// }

// int main() {
//     // Initialize standard IO
//     stdio_init_all();

//     // Initialize hardware
//     init_hardware();

//     // Create tasks
//     xTaskCreate(conveyor_belt_task, "ConveyorBeltTask", 256, NULL, CONVEYOR_TASK_PRIORITY, &conveyorTaskHandle);
//     xTaskCreate(sensor_task, "SensorTask", 256, NULL, SENSOR_TASK_PRIORITY, &sensorTaskHandle);
//     xTaskCreate(color_sensor_task, "ColorSensorTask", 256, NULL, COLOR_TASK_PRIORITY, &colorTaskHandle);

//     // Start the scheduler
//     vTaskStartScheduler();

//     // This point will never be reached because the scheduler takes over
//     while (1) {
//     }

//     return 0;
// }

// void conveyor_belt_task(void *pvParameters) {
//     while (1) {
//         conveyor_belt_run();
//         vTaskDelay(pdMS_TO_TICKS(100)); // Delay to prevent task hogging
//     }
// }

// void sensor_task(void *pvParameters) {
//     while (1) {
//         float weight = fsr_read_weight();
//         float voltage = fsr_read_voltage();

//         printf("Weight: %.2f\n", weight);
//         printf("FSR Voltage: %.2f V\n", voltage);
//         printf("-------------------------------------------\n");

//         vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
//     }
// }

// void color_sensor_task(void *pvParameters) {
//     while (1) {
//         // Select RED filter
//         gpio_put(S2_PIN, 0);
//         gpio_put(S3_PIN, 0);
//         int red = read_color_frequency(OUT_PIN);

//         // Select GREEN filter
//         gpio_put(S2_PIN, 1);
//         gpio_put(S3_PIN, 1);
//         int green = read_color_frequency(OUT_PIN);

//         // Select BLUE filter
//         gpio_put(S2_PIN, 0);
//         gpio_put(S3_PIN, 1);
//         int blue = read_color_frequency(OUT_PIN);

//         printf("Color: R: %d, G: %d, B: %d\n", red, green, blue);

//         vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
//     }
// }
