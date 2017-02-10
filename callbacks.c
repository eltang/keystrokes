#include "callbacks.h"
#include "timer.h"

enum {
    CALLBACK_SOURCE_TIMEOUT,
    CALLBACK_SOURCE_KEYSTROKE
};

static struct {
    const __flash action_t *keystroke_action;
    const __flash action_t *timeout_action;
} callback_actions[ROWS * COLUMNS];
static uint8_t callback_modes[ROWS * COLUMNS];
typedef struct {
    uint16_t timestamp;
    uint16_t wait;
} callback_timer_t;

static callback_timer_t callback_timers[ROWS * COLUMNS];
static uint8_t tap_count[ROWS * COLUMNS];

void callbacks_set_timeout_action(uint8_t keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch].timeout_action = action;
}

void callbacks_set_keystroke_action(uint8_t keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch].keystroke_action = action;
}

void callbacks_set_mode(uint8_t keyswitch, uint8_t mode)
{
    callback_modes[keyswitch] = mode;
}

uint8_t callbacks_get_mode(uint8_t keyswitch)
{
    return callback_modes[keyswitch];
}

void callbacks_set_timer(uint8_t keyswitch, uint16_t wait)
{
    callback_timers[keyswitch].timestamp = timer_read();
    callback_timers[keyswitch].wait = wait;
}

void callbacks_tap_count_increment(uint8_t keyswitch)
{
    ++tap_count[keyswitch];
}

uint8_t callbacks_tap_count_get(uint8_t keyswitch)
{
    return tap_count[keyswitch];
}

void callbacks_tap_count_clear(uint8_t keyswitch)
{
    tap_count[keyswitch] = 0;
}

void callbacks_execute(uint8_t keyswitch)
{
    uint8_t *callback_mode = &callback_modes[keyswitch];
    action_t action;
    keystroke_t keystroke = { .keyswitch = keyswitch };

    if (*callback_mode & CALLED_ON_TIMEOUT)
        action = *callback_actions[keyswitch].timeout_action;
    else
        action = *callback_actions[keyswitch].keystroke_action;
    if (*callback_mode & CALL_START) {
        keystroke.stage = KEYSTROKE_START;
        action.fcn(&keystroke, action.arg);
    }
    if (*callback_mode & CALL_FINISH) {
        keystroke.stage = KEYSTROKE_FINISH;
        action.fcn(&keystroke, action.arg);
    }
    *callback_mode &= ~(CALL_ON_KEYSTROKE_START | CALL_ON_KEYSTROKE_FINISH | CALL_ON_TIMEOUT);
}

void callback_task(keystroke_t *keystroke)
{
    uint8_t *callback_mode;
    callback_timer_t *callback_timer;

    for (uint8_t i = ROWS * COLUMNS; i--;) {
        callback_mode = &callback_modes[i];
        if (keystroke) {
            if (keystroke->stage == KEYSTROKE_START) {
                if (*callback_mode & CALL_ON_KEYSTROKE_START) {
                    *callback_mode |= CALLED_ON_KEYSTROKE_START;
                    goto execute_callback;
                }
            } else
                if (*callback_mode & CALL_ON_KEYSTROKE_FINISH) {
                    *callback_mode |= CALLED_ON_KEYSTROKE_FINISH;
                    goto execute_callback;
                }
        }
        if (*callback_mode & CALL_ON_TIMEOUT) {
            callback_timer = &callback_timers[i];
            if ((uint16_t)timer_read() - callback_timer->timestamp > callback_timer->wait) {
                *callback_mode |= CALLED_ON_TIMEOUT;
                goto execute_callback;
            }
        }
        continue;
    execute_callback:
        callbacks_execute(i);
    }
}
