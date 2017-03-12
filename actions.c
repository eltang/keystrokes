#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"
#include "layers.h"
#include "leader_key.h"
#include "timer.h"

void actions_modifiers_and_scancode(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = ((const __flash uint8_t *)source_action->data)[0];
    uint8_t modifiers = ((const __flash uint8_t *)source_action->data)[1];

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        modifiers_set_temporary(modifiers);
        keys_add_scancode(code);
        break;
    case KEYSTROKE_FINISH:
        modifiers_unset_temporary(modifiers);;
        keys_delete_scancode(code);
        break;
    }
}

void actions_modifiers(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t modifiers = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        modifiers_add_permanent(modifiers);
        break;
    case KEYSTROKE_FINISH:
        modifiers_delete_permanent(modifiers);
        break;
    }
}

void actions_scancode(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        keys_add_scancode(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_scancode(code);
        break;
    }
}

void actions_layers_goto(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t layer;

    if (keystroke->execution_mode == KEYSTROKE_START) {
        layer = *(const __flash uint8_t *)source_action->data;
        layers_set_primary_layer(layer);
    }
}

void actions_layers_visit(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t layer = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        layers_activate_secondary_layer(layer);
        break;
    case KEYSTROKE_FINISH:
        layers_deactivate_secondary_layer(layer);
        break;
    }
}

void actions_reset(struct keystroke *keystroke, const __flash struct action *source_action)
{
    if (keystroke->execution_mode == KEYSTROKE_START)
        Jump_To_Bootloader();
}

void actions_multiple_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct action *action = source_action->data;

    while (action++->fcn)
        action->fcn(keystroke, action);
}

void actions_none(struct keystroke *keystroke, const __flash struct action *source_action)
{
}

void actions_tap_dance(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_tap_dance_data *data = source_action->data;
    static uint8_t tap_action_modifiers;
    const __flash struct action *action;
    static uint16_t timestamp;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        if (data->storage->irq.interrupts) {
            if (data->storage->tap_count < data->action_count)
                ++data->storage->tap_count;
        } else {
            tap_action_modifiers = modifiers_get_permanent();
            data->storage->tap_count = 0;
            data->storage->irq.interrupts = INTERRUPT_MANUAL_KEYSTROKE_START;
            data->storage->irq.interrupts |= INTERRUPT_UNCONDITIONAL;
            data->storage->irq.action = source_action;
            data->storage->irq.keystroke = *keystroke;
            keystrokes_add_irq(&data->storage->irq);
        }
        timestamp = timer_read();
        data->storage->pressed = 1;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
    case INTERRUPT_MANUAL_KEYSTROKE_START:
        action = &data->actions[data->storage->tap_count];
        modifiers_add_permanent(tap_action_modifiers);
        keystroke->execution_mode = KEYSTROKE_START;
        action->fcn(keystroke, action);
        modifiers_delete_permanent(tap_action_modifiers);
        if (!data->storage->pressed) {
            keystroke->execution_mode = KEYSTROKE_FINISH;
            action->fcn(keystroke, action);
        }
        data->storage->irq.interrupts = 0;
        break;
    case KEYSTROKE_FINISH:
        data->storage->pressed = 0;
        if (data->storage->irq.interrupts)
            timestamp = timer_read();
        else {
            action = &data->actions[data->storage->tap_count];
            action->fcn(keystroke, action);
        }
        break;
    }
}

void actions_hold_tap(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_hold_tap_data *data = source_action->data;
    const __flash struct action *action = &data->hold_action;
    static uint8_t tap_action_modifiers;
    static uint16_t timestamp;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        tap_action_modifiers = modifiers_get_permanent();
        action->fcn(keystroke, action);
        data->storage->irq.interrupts = INTERRUPT_MANUAL_KEYSTROKE_START;
        data->storage->irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        data->storage->irq.action = source_action;
        data->storage->irq.keystroke = *keystroke;
        keystrokes_add_irq(&data->storage->irq);
        timestamp = timer_read();
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
    case INTERRUPT_MANUAL_KEYSTROKE_START:
        data->storage->irq.interrupts = 0;
        break;
    case KEYSTROKE_FINISH:
        action->fcn(keystroke, action);
        if (!data->storage->irq.interrupts)
            break;
        data->storage->irq.interrupts = 0;
        action = &data->tap_action;
        modifiers_add_permanent(tap_action_modifiers);
        keystroke->execution_mode = KEYSTROKE_START;
        action->fcn(keystroke, action);
        modifiers_delete_permanent(tap_action_modifiers);
        keystroke->execution_mode = KEYSTROKE_FINISH;
        action->fcn(keystroke, action);
        break;
    }
}

void actions_tap_hold(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_tap_hold_data *data = source_action->data;
    const __flash struct action *action;
    static uint8_t tap_action_modifiers;
    static uint16_t timestamp;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        timestamp = timer_read();
        tap_action_modifiers = modifiers_get_permanent();
        data->storage->irq.interrupts = INTERRUPT_MANUAL_KEYSTROKE_START;
        data->storage->irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        data->storage->irq.action = source_action;
        data->storage->irq.keystroke = *keystroke;
        data->storage->last_interrupt = 0;
        keystrokes_add_irq(&data->storage->irq);
        break;
    case INTERRUPT_MANUAL_KEYSTROKE_START:
        action = &data->tap_action;
        keystroke->execution_mode = KEYSTROKE_START;
        action->fcn(keystroke, action);
        data->storage->irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_MANUAL_KEYSTROKE_START;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
        action = &data->hold_action;
        keystroke->execution_mode = KEYSTROKE_START;
        action->fcn(keystroke, action);
        data->storage->irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_UNCONDITIONAL;
        break;
    case KEYSTROKE_FINISH:
        switch (data->storage->last_interrupt) {
        case INTERRUPT_MANUAL_KEYSTROKE_START:
            action = &data->tap_action;
            action->fcn(keystroke, action);
            break;
        case 0:
            action = &data->tap_action;
            modifiers_add_permanent(tap_action_modifiers);
            keystroke->execution_mode = KEYSTROKE_START;
            action->fcn(keystroke, action);
            modifiers_delete_permanent(tap_action_modifiers);
            keystroke->execution_mode = KEYSTROKE_FINISH;
            action->fcn(keystroke, action);
            data->storage->irq.interrupts = 0;
            break;
        case INTERRUPT_UNCONDITIONAL:
            action = &data->hold_action;
            action->fcn(keystroke, action);
            break;
        }
        break;
    }
}

void actions_leader_key(struct keystroke *keystroke, const __flash struct action *source_action)
{
    if (keystroke->execution_mode == KEYSTROKE_START)
        leader_key_start(keystroke);
}

void actions_modifiers_and_power_management(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = ((const __flash uint8_t *)source_action->data)[0];
    uint8_t modifiers = ((const __flash uint8_t *)source_action->data)[1];

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        modifiers_set_temporary(modifiers);
        keys_add_power_management(code);
        break;
    case KEYSTROKE_FINISH:
        modifiers_unset_temporary(modifiers);;
        keys_delete_power_management(code);
        break;
    }
}

void actions_power_management(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        keys_add_power_management(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_power_management(code);
        break;
    }
}

void actions_modifiers_and_multimedia(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = ((const __flash uint16_t *)source_action->data)[0];
    uint8_t modifiers = ((const __flash uint8_t *)source_action->data)[2];

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        modifiers_set_temporary(modifiers);
        keys_add_multimedia(code);
        break;
    case KEYSTROKE_FINISH:
        modifiers_unset_temporary(modifiers);;
        keys_delete_multimedia(code);
        break;
    }
}

void actions_multimedia(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint16_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        keys_add_multimedia(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_multimedia(code);
        break;
    }
}
