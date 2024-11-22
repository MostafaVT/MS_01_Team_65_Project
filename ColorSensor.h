#ifndef COLORSENSOR_H
#define COLORSENSOR_H

void color_sensor_init(int s0, int s1, int s2, int s3, int out_pin);
int read_color_frequency(int out_pin);

#endif
