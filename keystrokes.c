#include <LUFA/Drivers/USB/USB.h>

#include "keystrokes.h"
#include "actions.h"
#include "layers.h"
#include "timer.h"
#include "layout.h"
#include "modifiers.h"

static uint8_t keystroke_states[ROWS * COLUMNS];
static uint16_t keystroke_timestamps[ROWS * COLUMNS];
static uint8_t keystroke_source_layers[ROWS * COLUMNS];

static void keystrokes_execute(uint8_t keyswitch)
{
    action_t action;
    keystroke_t keystroke;

    action = layout[keystroke_source_layers[keyswitch]][keyswitch];
    keystroke.keyswitch = keyswitch;
    keystroke.state = keystroke_states[keyswitch];
    action.fcn(&keystroke, action.arg);
}

void keystrokes_process(keystroke_t *keystroke)
{
    uint8_t new_source_layer;

    if (keystroke->state == KEYSTROKE_START) {
        if (USB_DeviceState == DEVICE_STATE_Suspended)
            if (USB_Device_RemoteWakeupEnabled)
                USB_Device_SendRemoteWakeup();
        new_source_layer = layers_get_active_layer();
        for (uint8_t i = ROWS * COLUMNS; i--;) {
            if (keystroke->keyswitch == i)
                if (new_source_layer == keystroke_source_layers[i])
                    continue;
            if (!(keystroke_states[i] & KEYSTROKE_TIMED_OUT)) {
                keystroke_states[i] |= KEYSTROKE_INTERRUPTED;
                keystrokes_execute(i);
            }
        }
        modifiers_clear_temporary();
        keystroke_source_layers[keystroke->keyswitch] = new_source_layer;
    }
    keystroke_states[keystroke->keyswitch] = keystroke->state;
    keystroke_timestamps[keystroke->keyswitch] = timer_read();
    keystrokes_execute(keystroke->keyswitch);
}

void keystrokes_task(void)
{
    uint16_t timer_count = timer_read();
    
    for (uint8_t i = ROWS * COLUMNS; i--;) {
        if (!(keystroke_states[i] & KEYSTROKE_IS_NOT_TAP))
            if (timer_count - keystroke_timestamps[i] > MAX_TAP_DURATION) {
                keystroke_states[i] |= KEYSTROKE_TIMED_OUT;
                keystrokes_execute(i);
            }
    }
    matrix_scan();
    leader_key_task();
}
