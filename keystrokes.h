#ifndef KEYSTROKES_H
#define KEYSTROKES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t keyswitch;
    bool state;
} raw_keystroke_t;

typedef struct {
    uint8_t keyswitch;
    uint8_t state;
    uint8_t previous_state;
    uint8_t interruptions;
} keystroke_t;

enum {
    KEYSTROKE_FINISH,
    KEYSTROKE_START,
    KEYSTROKE_START_IS_NOT_TAP,
    KEYSTROKE_RELEASE_IS_NOT_TAP
};

void keystrokes_process(raw_keystroke_t *raw_keystroke);

#endif
