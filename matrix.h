#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "keystrokes.h"

#ifndef KEYSWITCH_BOUNCE_TIME
#define KEYSWITCH_BOUNCE_TIME 5
#endif

void matrix_activate_output(uint8_t output);
void matrix_deactivate_output(uint8_t output);
bool matrix_read_input(uint8_t input, uint8_t output);
void matrix_init(void);
bool matrix_scan(void);

#endif
