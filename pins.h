#ifndef PINS_H
#define PINS_H

#include <stdint.h>
#include <avr/io.h>

#define PIN(port, pin) { (port_t *)&PIN ## port, 1 << pin }

typedef struct {
    volatile uint8_t pin;
    volatile uint8_t ddr;
    volatile uint8_t port;
} port_t;

typedef struct {
    port_t *port;
    uint8_t mask;
} pin_t;

#endif
