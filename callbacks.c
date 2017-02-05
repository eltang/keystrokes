#include "callbacks.h"
#include "timer.h"

const __flash action_t *callback_actions[ROWS][COLUMNS];
static uint8_t callback_modes[ROWS][COLUMNS];
typedef struct {
    uint16_t timestamp;
    uint16_t wait;
} callback_timer_t;

static callback_timer_t callback_timers[ROWS][COLUMNS];
static uint8_t tap_count[ROWS][COLUMNS];

void callback_set_action(keyswitch_t *keyswitch, const __flash action_t *action)
{
    callback_actions[keyswitch->row][keyswitch->column] = action;
}

void callback_set_mode(keyswitch_t *keyswitch, uint8_t mode)
{
    callback_modes[keyswitch->row][keyswitch->column] = mode;
}

uint8_t callback_get_mode(keyswitch_t *keyswitch)
{
    return callback_modes[keyswitch->row][keyswitch->column];
}

void callback_set_timer(keyswitch_t *keyswitch, uint8_t wait)
{
    callback_timers[keyswitch->row][keyswitch->column].timestamp = timer_read();
    callback_timers[keyswitch->row][keyswitch->column].wait = wait;
}

void callback_tap_count_increment(keyswitch_t *keyswitch)
{
    ++tap_count[keyswitch->row][keyswitch->column];
}

uint8_t callback_tap_count_get(keyswitch_t *keyswitch)
{
    return tap_count[keyswitch->row][keyswitch->column];
}

void callback_tap_count_clear(keyswitch_t *keyswitch)
{
    tap_count[keyswitch->row][keyswitch->column] = 0;
}

void callback_cancel(keyswitch_t *keyswitch)
{
    callback_modes[keyswitch->row][keyswitch->column] = 0;
}

void callback_execute(keyswitch_t *keyswitch)
{
    uint8_t callback_mode = callback_modes[keyswitch->row][keyswitch->column];
    action_t action = *callback_actions[keyswitch->row][keyswitch->column];
    keystroke_t keystroke = { .keyswitch = *keyswitch };

    if (callback_mode & CALL_START) {
        keystroke.stage = KEYSTROKE_START;
        action.fcn(&keystroke, action.arg);
    }
    if (callback_mode & CALL_FINISH) {
        keystroke.stage = KEYSTROKE_FINISH;
        action.fcn(&keystroke, action.arg);
    }
    callback_cancel(keyswitch);
}

void callback_task(keystroke_t *keystroke)
{
    uint8_t callback_mode;
    callback_timer_t *callback_timer;

    for (uint8_t i = ROWS; i--;)
        for (uint8_t j = COLUMNS; j--;) {
            callback_mode = callback_modes[i][j];

            if (callback_mode & CALL_ON_TIMEOUT) {
                callback_timer = &callback_timers[i][j];
                if (timer_read() - callback_timer->timestamp > callback_timer->wait)
                    goto execute_callback;
            }
            if (!keystroke)
                continue;
            if (callback_mode & CALL_ON_KEYSTROKE_START && keystroke->stage == KEYSTROKE_START)
                goto execute_callback;
            if (callback_mode & KEYSTROKE_FINISH && keystroke->stage == KEYSTROKE_FINISH)
                goto execute_callback;
            continue;
        execute_callback:
            callback_execute(&(keyswitch_t){ i, j });
        }
}
