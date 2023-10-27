#include <avr/io.h>
#include <util/delay.h>

// Define pins for the IR sensor
#define IR_SENSOR_PIN PB0

// Threshold value for proximity detection (adjust as needed)
#define PROXIMITY_THRESHOLD 300

void initADC() {
    // Set the reference voltage to internal 2.56V
    ADMUX = (1 << REFS1) | (1 << REFS0);

    // Enable ADC and set prescaler to 64
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

    // Enable digital input for the IR sensor pin
    DIDR0 |= (1 << ADC0D);
}

uint16_t readIRSensor() {
    // Select the ADC channel for the IR sensor
    ADMUX = (ADMUX & 0xF8) | (IR_SENSOR_PIN & 0x07);

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Return the ADC value
    return ADC;
}

int main(void) {
    // Initialize the ADC for reading the IR sensor
    initADC();

    // Set the IR sensor pin as an input
    DDRB &= ~(1 << IR_SENSOR_PIN);

    while (1) {
        // Read the IR sensor value
        uint16_t irValue = readIRSensor();

        // Check if the IR sensor reading indicates proximity
        if (irValue < PROXIMITY_THRESHOLD) {
            // Proximity detected - take action (e.g., turn on an LED)
            // Replace the following line with your desired action.
            // Example: PORTB |= (1 << LED_PIN);
        } else {
            // No proximity detected - take action (e.g., turn off an LED)
            // Replace the following line with your desired action.
            // Example: PORTB &= ~(1 << LED_PIN);
        }

        _delay_ms(100); // Adjust the delay as needed for your application
    }

    return 0;
}
