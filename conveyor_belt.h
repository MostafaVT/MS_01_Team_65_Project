#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

#include <stdbool.h>

void conveyor_belt_init(int ir_sensor_pin, int servo1_pin, int servo2_pin, int button_pin);

void conveyor_belt_run();

#endif // CONVEYOR_BELT_H
