#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h>

void fsr_init(int fsr_pin) {
    adc_init();
    adc_gpio_init(fsr_pin);  
    // adc_select_input(5);
    /* CANT WORK WITH COLOR SENSOR DUE TO PIN CONFLICT */     
    adc_select_input(3);     
}

uint16_t fsr_read_raw() {
    return adc_read();
    printf("Raw value: %d\n", adc_read());
}

float fsr_read_weight() {
    uint16_t raw_value = fsr_read_raw();  // Reads ADC value (0-4095)
    
    float voltage = (raw_value * 3.3) / 4095.0;  // Convert to voltage (0-3.3V) where ADC register is 12-bit

    // mapping for max voltage corresponds to 5kg
    float weight = (voltage / 3.3) * 5.0;  // Scale to 0-5kg

    return weight;
}

float fsr_read_voltage() {
    uint16_t raw = fsr_read_raw();
    return (raw * 3.3f) / 4095.0f;
}
