#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdint.h>

#include "matrix.h"
#include "actions.h"

enum {
    CALL_START = 1,
    CALL_FINISH = 1 << 1,
    CALL_BOTH = CALL_START | CALL_FINISH,
    CALL_ON_KEYSTROKE_START = 1 << 2,
    CALL_ON_KEYSTROKE_FINISH = 1 << 3,
    CALL_ON_KEYSTROKE = CALL_ON_KEYSTROKE_START | CALL_ON_KEYSTROKE_FINISH,
    CALL_ON_TIMEOUT = 1 << 4,
    CALLED_ON_KEYSTROKE_START = 1 << 5,
    CALLED_ON_KEYSTROKE_FINISH = 1 << 6,
    CALLED_ON_TIMEOUT = 1 << 7
};

void callback_task(keystroke_t *keystroke);
void callbacks_set_timeout_action(uint8_t keyswitch, const __flash action_t *action);
void callbacks_set_keystroke_action(uint8_t keyswitch, const __flash action_t *action);
void callbacks_set_mode(uint8_t keyswitch, uint8_t mode);
uint8_t callbacks_get_mode(uint8_t keyswitch);
void callbacks_set_timer(uint8_t keyswitch, uint16_t wait);
void callbacks_tap_count_increment(uint8_t keyswitch);
uint8_t callbacks_tap_count_get(uint8_t keyswitch);
void callbacks_tap_count_clear(uint8_t keyswitch);

#endif
