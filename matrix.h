#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#ifndef KEYSWITCH_BOUNCE_TIME
#define KEYSWITCH_BOUNCE_TIME 5
#endif

typedef struct {
    uint8_t keyswitch;
    bool stage;
} keystroke_t;

enum {
    KEYSTROKE_START,
    KEYSTROKE_FINISH
};

void matrix_init_output(uint8_t output);
void matrix_init_input(uint8_t input);
void matrix_activate_output(uint8_t output);
void matrix_deactivate_output(uint8_t output, bool keystroke_detected);
bool matrix_read_input(uint8_t input, uint8_t output);
void matrix_init(void);
keystroke_t *matrix_scan(void);

#endif
