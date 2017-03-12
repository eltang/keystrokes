#include <LUFA/Drivers/USB/USB.h>

#include "keystrokes.h"
#include "actions.h"
#include "layers.h"
#include "layout.h"
#include "modifiers.h"

static uint8_t keystroke_source_layers[ROWS * COLUMNS];
static struct irq *irq_list_head;

static void keystrokes_fulfill_irqs(uint8_t interrupt, struct keystroke *keystroke)
{
    struct irq **irq = &irq_list_head;

    while (*irq) {
        if ((*irq)->interrupts & interrupt) {
            if (!keystroke || keystroke->keyswitch != (*irq)->keystroke.keyswitch || keystroke->layer != (*irq)->keystroke.layer) {
                (*irq)->keystroke.execution_mode = interrupt;
                (*irq)->action->fcn(&(*irq)->keystroke, (*irq)->action);
            }
        }
        if ((*irq)->interrupts)
            irq = &(*irq)->next;
        else
            *irq = (*irq)->next;
    }
}

void keystrokes_process(struct keystroke *keystroke)
{
    const __flash struct action *action;
    
    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        if (USB_DeviceState == DEVICE_STATE_Suspended)
            if (USB_Device_RemoteWakeupEnabled)
                USB_Device_SendRemoteWakeup();
        modifiers_clear_temporary();
        keystroke_source_layers[keystroke->keyswitch] = layers_get_active_layer();
        keystroke->layer = keystroke_source_layers[keystroke->keyswitch];
        keystrokes_fulfill_irqs(INTERRUPT_MANUAL_KEYSTROKE_START, keystroke);
        break;
    case KEYSTROKE_FINISH:
        keystroke->layer = keystroke_source_layers[keystroke->keyswitch];
        keystrokes_fulfill_irqs(INTERRUPT_MANUAL_KEYSTROKE_FINISH, keystroke);
        break;
    }
    action = &layout[keystroke_source_layers[keystroke->keyswitch]][keystroke->keyswitch];
    action->fcn(keystroke, action);
}

void keystrokes_task(void)
{
    keystrokes_fulfill_irqs(INTERRUPT_UNCONDITIONAL, 0);
    matrix_scan();
    leader_key_task();
}

void keystrokes_add_irq(struct irq *irq)
{
    irq->next = irq_list_head;
    irq_list_head = irq;
}
