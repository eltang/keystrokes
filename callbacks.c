#include "callbacks.h"

const __flash action_t *callback_actions[ROWS][COLUMNS];
static uint8_t callback_modes[ROWS][COLUMNS];
volatile int16_t callback_timers[ROWS][COLUMNS];
static uint8_t tap_count[ROWS][COLUMNS] = { 0 };

void callback_set_action(keyswitch_t keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch->row][keyswitch->column] = action;
}

void callback_set_mode(keyswitch_t keyswitch, uint8_t mode)
{
    callback_modes[keyswitch->row][keyswitch->column] |= mode;
}

void callback_set_timer(keyswitch_t keyswitch, uint8_t time)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        callback_timers[keyswitch->row][keyswitch->column] = time + 1;
    }
}

void callback_tap_count_increment(keyswitch_t keyswitch)
{
    ++tap_count[keyswitch->row][keyswitch->column];
}

uint8_t callback_tap_count_get(keyswitch_t keyswitch)
{
    return tap_count[keyswitch->row][keyswitch->column];
}

void callback_tap_count_clear(keyswitch_t keyswitch)
{
    tap_count[keyswitch->row][keyswitch->column] = 0;
}

void callback_cancel(keyswitch_t keyswitch)
{
    callback_modes[keyswitch->row][keyswitch->column] = 0;
}

void callback_keystroke_handler(keystroke_t *keystroke)
{
    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;) {
            uint8_t callback_mode = callback_modes[i][j];

            if (!(callback_mode & CALL_ON_KEYSTROKE_START && keystroke->stage))
                if (!(callback_mode & CALL_ON_KEYSTROKE_FINISH && !keystroke->stage))
                    continue;
            callback_execute((keyswitch_t){ i, j });
        }
}

void callback_execute(keyswitch_t keyswitch)
{
    uint8_t callback_mode = callback_modes[keyswitch->row][keyswitch->column];
    action_t action = *callback_actions[keyswitch->row][keyswitch->column];
    keystroke_t keystroke = { .keyswitch = keyswitch };

    if (callback_mode & CALL_START) {
        keystroke->stage = KEYSTROKE_START;
        action.fcn(keystroke, action.arg);
    }
    if (callback_mode & CALL_FINISH) {
        keystroke->stage = KEYSTROKE_FINISH;
        action.fcn(keystroke, action.arg);
    }
    callback_set_mode(keyswitch, 0);
}

void callback_task(void)
{
    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;)
            if (callback_modes[i][j] & CALL_ON_TIMEOUT) {
                bool execute_callback;

                ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                    execute_callback = !callback_timers[i][j];
                }
                if (execute_callback) {
                    callback_execute((keyswitch_t){ i, j });
                    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                        --callback_timers[i][j];
                    }
                }
            }
}

bool callback_called_on_timeout(keyswitch_t keyswitch)
{
    bool yes;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        yes = (callback_timers[keyswitch->row][keyswitch->column] = -1);
    }
    return yes;
}
