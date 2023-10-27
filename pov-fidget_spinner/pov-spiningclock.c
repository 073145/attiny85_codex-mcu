#include <avr/io.h>
#include <util/delay.h>

// Define the LED array and the number of LEDs
#define LED_ARRAY_DDR DDRB
#define LED_ARRAY_PORT PORTB
#define NUM_LEDS 6

// Delay between LED animations (adjust as needed)
#define ANIMATION_DELAY 5

// LED patterns for the spinning animation
uint8_t patterns[NUM_LEDS] = {
    0b10000000,
    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100
};

int main(void) {
    // Set LED array pins as outputs
    LED_ARRAY_DDR = 0xFF;

    while (1) {
        // Perform the spinning animation
        for (int i = 0; i < NUM_LEDS; i++) {
            LED_ARRAY_PORT = patterns[i];
            _delay_ms(ANIMATION_DELAY);
        }

        // Rotate the pattern in the opposite direction (un-spinning)
        for (int i = NUM_LEDS - 2; i >= 0; i--) {
            LED_ARRAY_PORT = patterns[i];
            _delay_ms(ANIMATION_DELAY);
        }
    }

    return 0;
}
