#include "power.h"
#include "pins.h"
#include "avr/power.h"

static const __flash pin_t unused_pins[] = UNUSED_PINS;

void power_init(void)
{
    pin_t pin;

    for (uint8_t i = sizeof(unused_pins) / sizeof(unused_pins[0]); i--;) {
        pin = unused_pins[i];

        PIN_DDR(pin) |= PIN_MASK(pin);
    }
#ifndef USING_TWI
    PRR0 |= 1 << PRTWI;
#endif
#ifndef USING_BACKLIGHT
    PPR0 |= 1 << PRTIM1;
}
