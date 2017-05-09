#ifndef PINS_H
#define PINS_H

#include <stdint.h>
#include <avr/io.h>

#define PIN(letter, number) { &PIN ## letter, 1 << number }

enum {
    PIN,
    DDR,
    PORT
};

struct pin {
    volatile uint8_t *addr;
    uint8_t mask;
};
__attribute__((always_inline))
static inline volatile uint8_t *pins_addr_to_reg(volatile uint8_t *addr, uint8_t reg);

static inline volatile uint8_t *pins_addr_to_reg(volatile uint8_t *addr, uint8_t reg)
{
#ifdef __AVR_ATmega128__
    if (addr == &PINF && reg != PIN)
        return &DDRF - 1 + reg;
#endif
    return addr + reg;
}

#endif
