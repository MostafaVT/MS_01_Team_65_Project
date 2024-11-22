#include "pico/stdlib.h"
#include "led.h"

// Define the GPIO pins for the RGB LED
#define RED_LED_PIN 25 
#define GREEN_LED_PIN 15
#define BLUE_LED_PIN 16

void led_init() {
    // Initialize the LED pins as output
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
}

// for Common Cathode
void led_on(int pin) {
    gpio_put(pin, 1); 
}

void led_off(int pin) {
    gpio_put(pin, 0);
}

void led_sequence() {

    while (1) {

        // Start with all LEDs off for 5 seconds
        led_off(RED_LED_PIN);
        led_off(GREEN_LED_PIN);
        led_off(BLUE_LED_PIN);
        sleep_ms(5000);

        // First sequence: Turn on Red LED, then Green, then Blue
        led_on(RED_LED_PIN);
        sleep_ms(1000);
        led_off(RED_LED_PIN);

        led_on(GREEN_LED_PIN);
        sleep_ms(1000);
        led_off(GREEN_LED_PIN);

        led_on(BLUE_LED_PIN);
        sleep_ms(1000);
        led_off(BLUE_LED_PIN);

        // Turn on all LEDs together for 2 seconds (White)
        led_on(RED_LED_PIN);
        led_on(GREEN_LED_PIN);
        led_on(BLUE_LED_PIN);
        sleep_ms(2000);

        // Turn off all LEDs
        led_off(RED_LED_PIN);
        led_off(GREEN_LED_PIN);
        led_off(BLUE_LED_PIN);
    }
}
