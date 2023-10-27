#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define the USB HID key codes
#define KEY_MODIFIER_NONE 0
#define KEYCODE_ENTER 40

// USB HID Keyboard report structure
typedef struct
{
    uint8_t modifier;
    uint8_t reserved;
    uint8_t keycode[6];
} KeyboardReport;

int main(void)
{
    // Set up the clock prescaler (divide by 8)
    CLKPR = (1 << CLKPCE);
    CLKPR = (1 << CLKPS1);

    // Initialize the USB stack
    usb_init();

    // Set up the LED as an output
    DDRB |= (1 << PB0);

    // Create a keyboard report structure
    KeyboardReport report;

    // Delay for a few seconds to allow the host to recognize the device
    _delay_ms(2000);

    // Main loop
    while (1)
    {
        // Press Enter key
        report.modifier = KEY_MODIFIER_NONE;
        report.reserved = 0;
        report.keycode[0] = KEYCODE_ENTER;
        for (int i = 1; i < 6; i++)
        {
            report.keycode[i] = 0;
        }

        // Send the keyboard report
        usb_keyboard_send(&report);

        // Release the Enter key
        report.modifier = KEY_MODIFIER_NONE;
        report.reserved = 0;
        for (int i = 0; i < 6; i++)
        {
            report.keycode[i] = 0;
        }

        // Send the keyboard report
        usb_keyboard_send(&report);

        // Toggle the LED
        PORTB ^= (1 << PB0);

        // Delay for a few seconds
        _delay_ms(2000);
    }

    return 0;
}
