#include <LUFA/Drivers/USB/USB.h>

#include "keystrokes.h"
#include "actions.h"
#include "layers.h"
#include "timer.h"
#include "layout.h"
#include "modifiers.h"

static uint8_t keystroke_states[ROWS * COLUMNS];
static uint8_t previous_keystroke_states[ROWS * COLUMNS];
static uint16_t keystroke_timestamps[ROWS * COLUMNS];
static uint8_t keystroke_interruptions[ROWS * COLUMNS];

static void keystrokes_execute(uint8_t keyswitch, uint8_t previous_state)
{
    action_t action;
    keystroke_t keystroke;
    uint8_t layer;
    bool new_keystroke = keystroke_states[keyswitch] == KEYSTROKE_START;

    layer = layers_get_source_layer(keyswitch, new_keystroke);
    action = layout[layer][keyswitch];
    keystroke.keyswitch = keyswitch;
    keystroke.interruptions = keystroke_interruptions[keyswitch];
    keystroke.state = keystroke_states[keyswitch];
    keystroke.previous_state = previous_state;
    if (action.fcn)
        action.fcn(&keystroke, action.arg);
}

void keystrokes_process(raw_keystroke_t *raw_keystroke)
{
    uint16_t timer_count = timer_read();
    uint8_t *keystroke_state, previous_keystroke_state;
    bool keystroke_in_progress, keystroke_is_not_tap;
    bool keystroke_interrupted = raw_keystroke && raw_keystroke->state == KEYSTROKE_START;

    if (keystroke_interrupted) {
        if (USB_DeviceState == DEVICE_STATE_Suspended)
            if (USB_Device_RemoteWakeupEnabled)
                USB_Device_SendRemoteWakeup();
        modifiers_clear_temporary();
    }
    for (uint8_t i = ROWS * COLUMNS; i--;) {
        if (raw_keystroke && raw_keystroke->keyswitch == i)
            continue;
        keystroke_state = &keystroke_states[i];
        keystroke_in_progress = *keystroke_state & KEYSTROKE_START;
        keystroke_is_not_tap = *keystroke_state & KEYSTROKE_IS_NOT_TAP;
        if (keystroke_interrupted) {
            if (keystroke_in_progress || !keystroke_is_not_tap) {
                ++keystroke_interruptions[i];
                *keystroke_state |= KEYSTROKE_INTERRUPTED;
                goto execute_keystroke;
            }
        } else {
            if (!keystroke_is_not_tap)
                if (timer_count - keystroke_timestamps[i] > MAX_TAP_DURATION) {
                    *keystroke_state |= KEYSTROKE_TIMED_OUT;
                    goto execute_keystroke;
                }
        }
        continue;
execute_keystroke:
        previous_keystroke_state = *keystroke_state;
        keystrokes_execute(i, previous_keystroke_state);
    }
    if (raw_keystroke) {
        previous_keystroke_state = keystroke_states[raw_keystroke->keyswitch];
        keystroke_states[raw_keystroke->keyswitch] = raw_keystroke->state;
        keystroke_interruptions[raw_keystroke->keyswitch] = 0;
        keystroke_timestamps[raw_keystroke->keyswitch] = timer_count;
        keystrokes_execute(raw_keystroke->keyswitch, previous_keystroke_state);
    }
}

void keystrokes_task(void)
{
    leader_key_task();
}