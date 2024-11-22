#ifndef FSR_H
#define FSR_H

void fsr_init(int fsr_pin);
uint16_t fsr_read_raw();
float fsr_read_weight();
float fsr_read_voltage();

#endif
