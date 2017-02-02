#ifndef PINS_H
#define PINS_H

#include <stdint.h>
#include <avr/io.h>

#define PIN(port, pin) { &PIN ## port, 1 << pin }
#define PIN_MASK(pin) (pin.mask)
#define PIN_PINx(pin) (pin.addr[0])
#define PIN_DDRx(pin) (pin.addr[1])
#define PIN_PORTx(pin) (pin.addr[2])

typedef struct {
    volatile uint8_t *addr;
    uint8_t mask;
} pin_t;

#endif
