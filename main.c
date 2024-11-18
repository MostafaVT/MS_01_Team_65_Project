#include "pico/stdlib.h"
#include "conveyor_belt.h"

#define IR_SENSOR_PIN 2
#define SERVO1_PIN 15
#define SERVO2_PIN 16
#define BUTTON_PIN 3

int main() {
    stdio_init_all();

    conveyor_belt_init(IR_SENSOR_PIN, SERVO1_PIN, SERVO2_PIN, BUTTON_PIN);

    while (1) {
        conveyor_belt_run();
    }

    return 0;
}
