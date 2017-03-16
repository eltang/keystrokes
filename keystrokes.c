#include <LUFA/Drivers/USB/USB.h>

#include "keystrokes.h"
#include "actions.h"
#include "layers.h"
#include "layout.h"
#include "modifiers.h"

static uint8_t keystroke_source_layers[ROWS * COLUMNS];
static struct irq *irqs;

static void keystrokes_fulfill_irqs(uint8_t interrupt, struct keystroke *keystroke)
{
    struct irq **current = &irqs;
    uint8_t saved_keystroke_execution_mode;

    while (*current) {
        if ((*current)->interrupts & interrupt) {
            saved_keystroke_execution_mode = keystroke->execution_mode;
            keystroke->execution_mode = interrupt;
            (*current)->action->fcn(keystroke, (*current)->action);
            keystroke->execution_mode = saved_keystroke_execution_mode;
        }
        if ((*current)->interrupts)
            current = &(*current)->next;
        else
            *current = (*current)->next;
    }
}

void keystrokes_process(struct keystroke *keystroke)
{
    const __flash struct action *action;

    if (keystroke->execution_mode == KEYSTROKE_START) {
        if (USB_DeviceState == DEVICE_STATE_Suspended)
            if (USB_Device_RemoteWakeupEnabled)
                USB_Device_SendRemoteWakeup();
        modifiers_clear_temporary();
        keystrokes_fulfill_irqs(INTERRUPT_KEYSTROKE_START_EARLY, keystroke);
        keystroke_source_layers[keystroke->keyswitch] = layers_get_active_layer();
    } else {
        keystrokes_fulfill_irqs(INTERRUPT_KEYSTROKE_FINISH_EARLY, keystroke);
    }
    action = &layout[keystroke_source_layers[keystroke->keyswitch]][keystroke->keyswitch];
    action->fcn(keystroke, action);
    if (keystroke->execution_mode == KEYSTROKE_START)
        keystrokes_fulfill_irqs(INTERRUPT_KEYSTROKE_START_LATE, keystroke);
    else
        keystrokes_fulfill_irqs(INTERRUPT_KEYSTROKE_FINISH_LATE, keystroke);
}

void keystrokes_task(void)
{
    struct keystroke keystroke;
    keystrokes_fulfill_irqs(INTERRUPT_UNCONDITIONAL, &keystroke);
    matrix_scan();
    leader_key_task();
}

void keystrokes_add_irq(struct irq *irq)
{
    struct irq **current = &irqs;

    while (*current)
        current = &(*current)->next;
    *current = irq;
    irq->next = 0;
}
