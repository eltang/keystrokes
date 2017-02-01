#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include <avr/io.h>

#ifndef KEYSWITCH_BOUNCE_TIME
#define KEYSWITCH_BOUNCE_TIME 5
#endif

#ifdef __AVR__

#define PIN(port, pin) { &PIN ## port, 1 << pin }
#define PIN_MASK(pin) (pin.mask)
#define PIN_PINx(pin) (pin.addr[0])
#define PIN_DDRx(pin) (pin.addr[1])
#define PIN_PORTx(pin) (pin.addr[2])

typedef struct {
    volatile uint8_t *addr;
    uint8_t mask;
} pin_t;

#elif defined(PROTOCOL_CHIBIOS)

#define PIN(port, pin) PAL_LINE(GPIO ## port, pin)

typedef ioline_t pin_t;

#endif

typedef struct {
    uint8_t row;
    uint8_t column;
} keyswitch_t;

typedef struct {
    keyswitch_t keyswitch;
    bool stage;
} keystroke_t;

enum {
    KEYSTROKE_START,
    KEYSTROKE_FINISH
};

extern volatile uint8_t matrix_keyswitch_states[ROWS][COLUMNS];

void matrix_init_output(uint8_t output);
void matrix_init_input(uint8_t input);
void matrix_activate_output(uint8_t output);
void matrix_deactivate_output(uint8_t output);
bool matrix_read_input(uint8_t input);
void matrix_init(void);
keystroke_t *matrix_scan(void);

#endif
