#include "power.h"
#include "pins.h"
#include "avr/power.h"

static const __flash struct pin unused_pins[] = UNUSED_PINS;

void power_init(void)
{
    struct pin pin;
    uint8_t temp = 0;

    for (uint8_t i = sizeof(unused_pins) / sizeof(unused_pins[0]); i--;) {
        pin = unused_pins[i];

        pin.port->ddr |= pin.mask;
    }
#ifndef USING_TWI
    temp |= 1 << PRTWI;
#endif
#ifndef USING_BACKLIGHT
    temp |= 1 << PRTIM1;
#endif
    temp |= 1 << PRSPI;
    temp |= 1 << PRADC;
    PRR0 = temp;
    temp = 0;
    temp |= 1 << 4; // PRTIM4
    temp |= 1 << PRTIM3;
    temp |= 1 << PRUSART1;
    PRR1 = temp;
}
