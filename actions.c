#include <LUFA/Drivers/USB/USB.h>

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
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(modifiers);
        keys_add_scancode(code);
        break;
    case KEYSTROKE_END:
        keys_delete_scancode(code);
        modifiers_remove_disguise(modifiers);
        break;
    }
}

void actions_modifiers(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t modifiers = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(modifiers);
        modifiers_add(modifiers);
        break;
    case KEYSTROKE_END:
        modifiers_delete(modifiers);
        modifiers_remove_disguise(modifiers);
        break;
    }
}

void actions_scancode(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(0);
        keys_add_scancode(code);
        break;
    case KEYSTROKE_END:
        keys_delete_scancode(code);
        break;
    }
}

void actions_layers_goto(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t layer;

    if (keystroke->execution_mode == KEYSTROKE_BEGIN) {
        layer = *(const __flash uint8_t *)source_action->data;
        layers_set_primary_layer(layer);
    }
}

void actions_layers_visit(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t layer = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        layers_activate_secondary_layer(layer);
        break;
    case KEYSTROKE_END:
        layers_deactivate_secondary_layer(layer);
        break;
    }
}

void actions_reset(struct keystroke *keystroke, const __flash struct action *source_action)
{
    if (keystroke->execution_mode == KEYSTROKE_BEGIN)
        Jump_To_Bootloader();
}

void actions_sequential_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_sequential_actions_data *data = source_action->data;

    if (keystroke->execution_mode == KEYSTROKE_BEGIN)
        for (uint8_t i = 0; i < data->action_count; ++i) {
            data->actions[i].fcn(keystroke, &data->actions[i]);
            keystroke->execution_mode = KEYSTROKE_END;
            data->actions[i].fcn(keystroke, &data->actions[i]);
            keystroke->execution_mode = KEYSTROKE_BEGIN;
        }
}

void actions_nested_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_nested_actions_data *data = source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        for (uint8_t i = 0; i < data->action_count; ++i)
            data->actions[i].fcn(keystroke, &data->actions[i]);
        break;
    case KEYSTROKE_END:
        for (uint8_t i = data->action_count; i--;)
            data->actions[i].fcn(keystroke, &data->actions[i]);
        break;
    }
}

void actions_none(struct keystroke *keystroke, const __flash struct action *source_action)
{
}

void actions_tap_dance_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    static const __flash struct actions_tap_dance_actions_data *data;
    const __flash struct action *action;
    static uint16_t timestamp;
    static struct keystroke saved_keystroke;
    static uint8_t old_layer;
    static struct irq irq;
    static bool tap_dance_key_pressed;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        timestamp = timer_read();
        tap_dance_key_pressed = 1;
        if (irq.interrupts) {
            if (layers_get_active_layer() == old_layer) {
                data = source_action->data;
                ++data->storage->tap_count;
                break;
            }
            if (data->storage->tap_count < data->max_taps) {
                action = &data->actions[data->storage->tap_count + data->max_taps];
                action->fcn(&saved_keystroke, action);
                saved_keystroke.execution_mode = KEYSTROKE_END;
                action->fcn(&saved_keystroke, action);
            }
            modifiers_unfreeze();
        }
        data = source_action->data;
        modifiers_freeze();
        data->storage->tap_count = 0;
        data->storage->alive = 1;
        saved_keystroke = *keystroke;
        irq.action = source_action;
        if (irq.interrupts)
            break;
        irq.interrupts = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        keystrokes_add_irq(&irq);
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp > MAX_TAP_DURATION)
            goto finish;
        break;
    case INTERRUPT_KEYSTROKE_BEGIN_EARLY:
        if (keystroke->keyswitch != saved_keystroke.keyswitch)
            goto finish;
        break;
    case KEYSTROKE_END:
        data = source_action->data;
        if (data->storage->alive) {
            timestamp = timer_read();
            old_layer = layers_get_active_layer();
            tap_dance_key_pressed = 0;
        } else {
            action = &data->actions[data->storage->tap_count];
            action->fcn(keystroke, action);
        }
        break;
    finish:
        data = source_action->data;
        irq.interrupts = 0;
        data->storage->alive = 0;
        if (data->storage->tap_count < data->max_taps) {
            if (tap_dance_key_pressed)
                action = &data->actions[data->storage->tap_count];
            else
                action = &data->actions[data->storage->tap_count + data->max_taps];
            action->fcn(&saved_keystroke, action);
            if (!tap_dance_key_pressed) {
                saved_keystroke.execution_mode = KEYSTROKE_END;
                action->fcn(&saved_keystroke, action);
            }
        }
        modifiers_unfreeze();
    }
}

void actions_hold_tap_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_hold_tap_actions_data *data = source_action->data;
    const __flash struct action *action = &data->hold_action;
    static uint16_t timestamp;
    static struct irq irq;
    static uint8_t most_recent_keyswitch;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_freeze();
        action->fcn(keystroke, action);
        irq.interrupts = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        irq.action = source_action;
        keystrokes_add_irq(&irq);
        timestamp = timer_read();
        most_recent_keyswitch = keystroke->keyswitch;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
    case INTERRUPT_KEYSTROKE_BEGIN_EARLY:
        irq.interrupts = 0;
        modifiers_unfreeze();
        break;
    case KEYSTROKE_END:
        action->fcn(keystroke, action);
        if (!irq.interrupts || keystroke->keyswitch != most_recent_keyswitch)
            break;
        irq.interrupts = 0;
        action = &data->tap_action;
        keystroke->execution_mode = KEYSTROKE_BEGIN;
        action->fcn(keystroke, action);
        modifiers_unfreeze();
        keystroke->execution_mode = KEYSTROKE_END;
        action->fcn(keystroke, action);
        break;
    }
}

void actions_tap_hold_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_tap_hold_actions_data *data = source_action->data;
    const __flash struct action *action;
    static uint16_t timestamp;
    static struct keystroke saved_keystroke;
    static struct irq irq;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        timestamp = timer_read();
        modifiers_freeze();
        irq.interrupts = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        irq.action = source_action;
        data->storage->last_interrupt = 0;
        keystrokes_add_irq(&irq);
        saved_keystroke = *keystroke;
        break;
    case INTERRUPT_KEYSTROKE_BEGIN_EARLY:
        action = &data->tap_action;
        action->fcn(&saved_keystroke, action);
        irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
        modifiers_unfreeze();
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
        action = &data->hold_action;
        action->fcn(&saved_keystroke, action);
        irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_UNCONDITIONAL;
        modifiers_unfreeze();
        break;
    case KEYSTROKE_END:
        switch (data->storage->last_interrupt) {
        case INTERRUPT_KEYSTROKE_BEGIN_EARLY:
            action = &data->tap_action;
            action->fcn(keystroke, action);
            break;
        case 0:
            action = &data->tap_action;
            keystroke->execution_mode = KEYSTROKE_BEGIN;
            action->fcn(keystroke, action);
            keystroke->execution_mode = KEYSTROKE_END;
            action->fcn(keystroke, action);
            irq.interrupts = 0;
            modifiers_unfreeze();
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
    if (keystroke->execution_mode == KEYSTROKE_BEGIN)
        leader_key_start(keystroke);
}

void actions_modifiers_and_power_management(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = ((const __flash uint8_t *)source_action->data)[0];
    uint8_t modifiers = ((const __flash uint8_t *)source_action->data)[1];

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(modifiers);
        keys_add_power_management(code);
        break;
    case KEYSTROKE_END:
        keys_delete_power_management(code);
        modifiers_remove_disguise(modifiers);;
        break;
    }
}

void actions_power_management(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint8_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(0);
        keys_add_power_management(code);
        break;
    case KEYSTROKE_END:
        keys_delete_power_management(code);
        break;
    }
}

void actions_modifiers_and_multimedia(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = ((const __flash uint16_t *)source_action->data)[0];
    uint8_t modifiers = ((const __flash uint8_t *)source_action->data)[2];

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(modifiers);
        keys_add_multimedia(code);
        break;
    case KEYSTROKE_END:
        keys_delete_multimedia(code);
        modifiers_remove_disguise(modifiers);
        break;
    }
}

void actions_multimedia(struct keystroke *keystroke, const __flash struct action *source_action)
{
    uint8_t code = *(const __flash uint16_t *)source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        modifiers_set_disguise(0);
        keys_add_multimedia(code);
        break;
    case KEYSTROKE_END:
        keys_delete_multimedia(code);
        break;
    }
}

void actions_oneshot_action(struct keystroke *keystroke, const __flash struct action *source_action)
{
    enum {
        ONESHOT_NONE,
        ONESHOT_STARTED,
        ONESHOT_CHAINED,
        ONESHOT_APPLIED,
        ONESHOT_LOCKED,
        ONESHOT_INTERRUPTED
    };

    const __flash struct actions_oneshot_action_data *data = source_action->data;
    static uint16_t timestamp;
    static uint8_t interrupting_keystroke_keyswitch, oneshot_keystroke_keyswitch;
    static uint8_t oneshot_layer;

    switch (keystroke->execution_mode) {
    case INTERRUPT_KEYSTROKE_BEGIN_EARLY:
        switch (data->storage->state) {
        case ONESHOT_STARTED:
            if (keystroke->keyswitch == oneshot_keystroke_keyswitch)
                break;
        case ONESHOT_CHAINED:
            data->storage->state = ONESHOT_INTERRUPTED;
            break;
        case ONESHOT_APPLIED:
            goto finish;
            break;
        }
        break;
    case KEYSTROKE_BEGIN:
        switch (data->storage->state) {
        case ONESHOT_NONE:
            data->storage->irq.interrupts = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
            data->storage->irq.interrupts |= INTERRUPT_KEYSTROKE_BEGIN_LATE;
            data->storage->irq.interrupts |= INTERRUPT_UNCONDITIONAL;
            data->storage->irq.action = source_action;
            keystrokes_add_irq(&data->storage->irq);
            data->action.fcn(keystroke, &data->action);
            data->storage->keystroke = *keystroke;
        case ONESHOT_INTERRUPTED:
            data->storage->state = ONESHOT_STARTED;
            timestamp = timer_read();
            oneshot_keystroke_keyswitch = keystroke->keyswitch;
            data->storage->oneshot_keystroke_keyswitch = oneshot_keystroke_keyswitch;
            oneshot_layer = layers_get_active_layer();
            data->storage->oneshot_layer = oneshot_layer;
            break;
        case ONESHOT_STARTED:
            data->storage->state = ONESHOT_LOCKED;
            data->storage->irq.interrupts = 0;
            break;
        case ONESHOT_LOCKED:
            goto finish;
            break;
        }
        break;
    case INTERRUPT_KEYSTROKE_BEGIN_LATE:
        if (data->storage->state != ONESHOT_INTERRUPTED)
            break;
        if (data->storage->oneshot_keystroke_keyswitch == oneshot_keystroke_keyswitch)
            if (data->storage->oneshot_layer == oneshot_layer) {
                data->storage->irq.interrupts = INTERRUPT_KEYSTROKE_BEGIN_EARLY;
                data->storage->irq.interrupts |= INTERRUPT_KEYSTROKE_END_EARLY;
                interrupting_keystroke_keyswitch = keystroke->keyswitch;
                data->storage->state = ONESHOT_APPLIED;
                break;
            }
        data->storage->state = ONESHOT_CHAINED;
        data->storage->oneshot_layer = oneshot_layer;
        data->storage->oneshot_keystroke_keyswitch = oneshot_keystroke_keyswitch;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp > MAX_TAP_DURATION)
            goto finish;
        break;
    case INTERRUPT_KEYSTROKE_END_EARLY:
        if (keystroke->keyswitch == interrupting_keystroke_keyswitch)
            goto finish;
        break;
    finish:
        data->storage->keystroke.execution_mode = KEYSTROKE_END;
        data->action.fcn(&data->storage->keystroke, &data->action);
        data->storage->state = ONESHOT_NONE;
        data->storage->irq.interrupts = 0;
    }
}

void actions_shift_switch_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_shift_switch_actions_data *data = source_action->data;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_BEGIN:
        data->storage->switched = modifiers_get_frozen_modifiers() & (HID_KEYBOARD_MODIFIER_LEFTSHIFT | HID_KEYBOARD_MODIFIER_RIGHTSHIFT);
        if (data->storage->switched)
            data->secondary_action.fcn(keystroke, &data->secondary_action);
        else
            data->primary_action.fcn(keystroke, &data->primary_action);
        break;
    case KEYSTROKE_END:
        if (data->storage->switched)
            data->secondary_action.fcn(keystroke, &data->secondary_action);
        else
            data->primary_action.fcn(keystroke, &data->primary_action);
        break;
    }
}
