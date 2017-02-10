#include "callbacks.h"
#include "timer.h"

enum {
    CALLBACK_SOURCE_TIMEOUT,
    CALLBACK_SOURCE_KEYSTROKE
};

static struct {
    const __flash action_t *keystroke_action;
    const __flash action_t *timeout_action;
} callback_actions[ROWS][COLUMNS];
static uint8_t callback_modes[ROWS][COLUMNS];
typedef struct {
    uint16_t timestamp;
    uint16_t wait;
} callback_timer_t;

static callback_timer_t callback_timers[ROWS][COLUMNS];
static uint8_t tap_count[ROWS][COLUMNS];

void callbacks_set_timeout_action(keyswitch_t *keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch->row][keyswitch->column].timeout_action = action;
}

void callbacks_set_keystroke_action(keyswitch_t *keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch->row][keyswitch->column].keystroke_action = action;
}

void callbacks_set_mode(keyswitch_t *keyswitch, uint8_t mode)
{
    callback_modes[keyswitch->row][keyswitch->column] = mode;
}

uint8_t callbacks_get_mode(keyswitch_t *keyswitch)
{
    return callback_modes[keyswitch->row][keyswitch->column];
}

void callbacks_set_timer(keyswitch_t *keyswitch, uint16_t wait)
{
    callback_timers[keyswitch->row][keyswitch->column].timestamp = timer_read();
    callback_timers[keyswitch->row][keyswitch->column].wait = wait;
}

void callbacks_tap_count_increment(keyswitch_t *keyswitch)
{
    ++tap_count[keyswitch->row][keyswitch->column];
}

uint8_t callbacks_tap_count_get(keyswitch_t *keyswitch)
{
    return tap_count[keyswitch->row][keyswitch->column];
}

void callbacks_tap_count_clear(keyswitch_t *keyswitch)
{
    tap_count[keyswitch->row][keyswitch->column] = 0;
}

void callbacks_execute(keyswitch_t *keyswitch)
{
    uint8_t *callback_mode = &callback_modes[keyswitch->row][keyswitch->column];
    action_t action;
    keystroke_t keystroke = { .keyswitch = *keyswitch };

    if (*callback_mode & CALLED_ON_TIMEOUT)
        action = *callback_actions[keyswitch->row][keyswitch->column].timeout_action;
    else
        action = *callback_actions[keyswitch->row][keyswitch->column].keystroke_action;
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

    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;) {
            callback_mode = &callback_modes[i][j];
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
                callback_timer = &callback_timers[i][j];
                if ((uint16_t)timer_read() - callback_timer->timestamp > callback_timer->wait) {
                    *callback_mode |= CALLED_ON_TIMEOUT;
                    goto execute_callback;
                }
            }
            continue;
        execute_callback:
            callbacks_execute(&(keyswitch_t){ i, j });
        }
}
