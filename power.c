#include "power.h"
#include "pins.h"
#include "avr/power.h"

static const __flash struct pin unused_pins[] = UNUSED_PINS;

void power_init(void)
{
    struct pin pin;

    for (uint8_t i = sizeof(unused_pins) / sizeof(unused_pins[0]); i--;) {
        pin = unused_pins[i];

        *pins_addr_to_reg(pin.addr, PORT) |= pin.mask;
    }
    PRR0 = PRR0_VALUE;
    PRR1 = PRR1_VALUE;
}
