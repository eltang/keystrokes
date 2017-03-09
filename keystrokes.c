#include <LUFA/Drivers/USB/USB.h>

#include "keystrokes.h"
#include "actions.h"
#include "layers.h"
#include "timer.h"
#include "layout.h"
#include "modifiers.h"

static uint8_t keystroke_states[ROWS * COLUMNS];
static uint16_t keystroke_timestamps[ROWS * COLUMNS];

static void keystrokes_execute(uint8_t keyswitch)
{
    action_t action;
    keystroke_t keystroke;
    uint8_t layer;

    if (keystroke_states[keyswitch] == KEYSTROKE_START)
        layer = layers_get_new_source_layer(keyswitch);
    else
        layer = layers_get_old_source_layer(keyswitch);
    action = layout[layer][keyswitch];
    keystroke.keyswitch = keyswitch;
    keystroke.state = keystroke_states[keyswitch];
    action.fcn(&keystroke, action.arg);
}

void keystrokes_process(keystroke_t *keystroke)
{
    uint16_t timer_count = timer_read();
    uint8_t *keystroke_state;
    bool keystroke_in_progress, keystroke_is_not_tap;
    bool keystroke_interrupted = keystroke && keystroke->state == KEYSTROKE_START;

    if (keystroke_interrupted) {
        if (USB_DeviceState == DEVICE_STATE_Suspended)
            if (USB_Device_RemoteWakeupEnabled)
                USB_Device_SendRemoteWakeup();
        modifiers_clear_temporary();
    }
    for (uint8_t i = ROWS * COLUMNS; i--;) {
        if (keystroke && keystroke->keyswitch == i)
            continue;
        keystroke_state = &keystroke_states[i];
        keystroke_in_progress = *keystroke_state & KEYSTROKE_START;
        keystroke_is_not_tap = *keystroke_state & KEYSTROKE_IS_NOT_TAP;

        if (keystroke_interrupted) {
            if (keystroke_in_progress || !keystroke_is_not_tap) {
                *keystroke_state |= KEYSTROKE_INTERRUPTED;
                keystrokes_execute(i);
            }
        } else if (!keystroke_is_not_tap)
            if (timer_count - keystroke_timestamps[i] > MAX_TAP_DURATION) {
                *keystroke_state |= KEYSTROKE_TIMED_OUT;
                keystrokes_execute(i);
            }
    }
    if (keystroke) {
        keystroke_states[keystroke->keyswitch] = keystroke->state;
        keystroke_timestamps[keystroke->keyswitch] = timer_count;
        keystrokes_execute(keystroke->keyswitch);
    }
}

void keystrokes_task(void)
{
    leader_key_task();
}
