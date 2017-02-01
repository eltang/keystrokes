#include "timer.h"
#include "matrix.h"
#include "KeyboardMouse.h"

void timer_init(void)
{
    TCCR0A |= 1 << WGM01;
    TCCR0B |= 1 << CS01 | 1 << CS00;
    TIMSK0 |= 1 << OCIE0A;
    OCR0A = 249;
}

ISR(TIMER0_COMPA_vect)
{
    HID_Device_USBTask(&Keyboard_HID_Interface);
    HID_Device_USBTask(&Mouse_HID_Interface);
    USB_USBTask();
    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;) {
            if (matrix_keyswitch_states[i][j] & 0x7F)
                --matrix_keyswitch_states[i][j];
        }
}
