//////////////////////////_______________RTOS_LIB_NEEDED_______________//////////////////////////
#include "pico/stdlib.h"
#include "conveyor_belt.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "fsr.h"
#include <stdio.h>

// Pins definitions
#define IR_SENSOR_PIN 6
#define SERVO1_PIN 17
#define SERVO2_PIN 16
#define BUTTON_PIN 25
#define MOTOR1_IN1_PIN 18
#define MOTOR1_IN2_PIN 19
#define MOTOR1_ENABLE_PIN 20
#define MOTOR2_IN3_PIN 21
#define MOTOR2_IN4_PIN 5
#define MOTOR2_ENABLE_PIN 7
#define S0_PIN 26
#define S1_PIN 27
#define S2_PIN 28
#define S3_PIN 4
#define OUT_PIN 12
#define FSR_PIN 29

// Task priorities
#define MOTOR_CONTROL_TASK_PRIORITY 2 
#define CONVEYOR_TASK_PRIORITY 2
#define SENSOR_TASK_PRIORITY 2
#define SERVO_TASK_PRIORITY 1
#define COLOR_TASK_PRIORITY 1

TaskHandle_t motorControlTaskHandle = NULL;
TaskHandle_t conveyorTaskHandle = NULL;
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t servoTaskHandle = NULL;
TaskHandle_t colorTaskHandle = NULL;


// Function prototypes
void init_hardware();
void motor_control_task(void *pvParameters);
void conveyor_belt_task(void *pvParameters);
void sensor_task(void *pvParameters);
void color_sensor_task(void *pvParameters);

void init_hardware() {
    motor_init(
        MOTOR1_IN1_PIN, MOTOR1_IN2_PIN, MOTOR1_ENABLE_PIN,
        MOTOR2_IN3_PIN, MOTOR2_IN4_PIN, MOTOR2_ENABLE_PIN
    );

    conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);
    color_sensor_init(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);
    fsr_init(FSR_PIN);
}

// Motor control task function with PWM
void motor_control_task(void *pvParameters) {
    while (1) {
        // Motor 1: Forward at 100% speed
        motor_set_direction(1, true);  // Forward
        motor_set_speed(1, 1.0f);      // 100% speed

        // Motor 2: Backward at 100% speed
        motor_set_direction(2, false); // Backward
        motor_set_speed(2, 1.0f);      // 100% speed

        vTaskDelay(pdMS_TO_TICKS(5000)); // Run for 5 seconds

        // Stop motors
        motor_stop();

        // Pause for 2 seconds
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Reverse motor directions
        motor_set_direction(1, false); // Motor 1: Backward
        motor_set_speed(1, 1.0f);      // 100% speed

        motor_set_direction(2, true);  // Motor 2: Forward
        motor_set_speed(2, 0.6f);      // 60% speed

        vTaskDelay(pdMS_TO_TICKS(5000)); // Run for 5 seconds

        // Stop motors again
        motor_stop();

        vTaskDelay(pdMS_TO_TICKS(2000)); // Pause before next cycle
        
        ///////////////////////////__NO_PWM__/////////////////////////////////

        //  // Move motors forward
        // motor_set_direction(1, true);  // Motor 1 forward
        // motor_set_direction(2, true);  // Motor 2 forward
        // motor_start();
        // vTaskDelay(pdMS_TO_TICKS(2000)); // Run forward for 2000ms

        // // Stop motors
        // motor_stop();
        // vTaskDelay(pdMS_TO_TICKS(500)); // Pause for 500ms

        // // Move motors in reverse
        // motor_set_direction(1, false);  // Motor 1 reverse
        // motor_set_direction(2, false);  // Motor 2 reverse
        // motor_start();
        // vTaskDelay(pdMS_TO_TICKS(2000)); // Run in reverse for 2000ms

        // // Stop motors
        // motor_stop();
        // vTaskDelay(pdMS_TO_TICKS(500)); // Pause for 500ms
    }
}

void conveyor_belt_task(void *pvParameters) {
    while (1) {
        conveyor_belt_run();
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay to prevent task hogging
    }
}

void sensor_task(void *pvParameters) {
    while (1) {
        float weight = fsr_read_weight();
        float voltage = fsr_read_voltage();

        printf("Weight: %.2f\n", weight);
        printf("FSR Voltage: %.2f V\n", voltage);
        printf("-------------------------------------------\n");

        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

void color_sensor_task(void *pvParameters) {
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

        printf("Color: R: %d, G: %d, B: %d\n", red, green, blue);

        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

int main() {
    stdio_init_all();

    init_hardware();

    xTaskCreate(conveyor_belt_task, "ConveyorBeltTask", 256, NULL, CONVEYOR_TASK_PRIORITY, &conveyorTaskHandle);
    xTaskCreate(sensor_task, "SensorTask", 256, NULL, SENSOR_TASK_PRIORITY, &sensorTaskHandle);
    xTaskCreate(color_sensor_task, "ColorSensorTask", 256, NULL, COLOR_TASK_PRIORITY, &colorTaskHandle);
    xTaskCreate(motor_control_task, "MotorControlTask", 1024, NULL, MOTOR_CONTROL_TASK_PRIORITY, &motorControlTaskHandle);

    vTaskStartScheduler();

    while (1) {
    }

    return 0;
}
