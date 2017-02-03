#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "timer.h"
#include "matrix.h"
#include "KeyboardMouse.h"

static volatile uint32_t count;

void timer_init(void)
{
    TCCR0A |= 1 << WGM01;
    TCCR0B |= 1 << CS01 | 1 << CS00;
    TIMSK0 |= 1 << OCIE0A;
    OCR0A = 249;
}

uint32_t timer_read(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        return count;
    }
}

ISR(TIMER0_COMPA_vect)
{
    ++count;
    HID_Device_USBTask(&Keyboard_HID_Interface);
    HID_Device_USBTask(&Mouse_HID_Interface);
    USB_USBTask();
    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;) {
            if (matrix_keyswitch_states[i][j] & 0x7F)
                --matrix_keyswitch_states[i][j];
        }
}
