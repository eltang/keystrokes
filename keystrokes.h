#ifndef KEYSTROKES_H
#define KEYSTROKES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t keyswitch;
    uint8_t state;
    uint8_t interruptions;
    uint8_t taps;
} keystroke_t;

enum {
    KEYSTROKE_FINISH,
    KEYSTROKE_START
};

void keystrokes_process(uint8_t *keyswitch);

#endif
