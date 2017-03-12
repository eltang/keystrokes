#ifndef PINS_H
#define PINS_H

#include <stdint.h>
#include <avr/io.h>

#define PIN(letter, number) { (struct port *)&PIN ## letter, 1 << number }

struct port {
    volatile uint8_t pin;
    volatile uint8_t ddr;
    volatile uint8_t port;
};

struct pin {
    struct port *port;
    uint8_t mask;
};

#endif
