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
};

void callback_task(keystroke_t *keystroke);
void callback_set_action(keyswitch_t *keyswitch, const __flash action_t *action);
void callback_set_mode(keyswitch_t *keyswitch, uint8_t mode);
uint8_t callback_get_mode(keyswitch_t *keyswitch);
void callback_set_timer(keyswitch_t *keyswitch, uint8_t wait);
void callback_tap_count_increment(keyswitch_t *keyswitch);
uint8_t callback_tap_count_get(keyswitch_t *keyswitch);
void callback_tap_count_clear(keyswitch_t *keyswitch);
void callback_cancel(keyswitch_t *keyswitch);
void callback_execute(keyswitch_t *keyswitch);

#endif
