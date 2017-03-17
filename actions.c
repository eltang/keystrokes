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
    const __flash struct actions_multiple_actions_data *data = source_action->data;

    if (keystroke->execution_mode == KEYSTROKE_START)
        for (uint8_t i = 0; i < data->action_count; ++i) {
            data->actions[i].fcn(keystroke, &data->actions[i]);
            keystroke->execution_mode = KEYSTROKE_FINISH;
            data->actions[i].fcn(keystroke, &data->actions[i]);
            keystroke->execution_mode = KEYSTROKE_START;
        }
}

void actions_start_action(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct action *action;

    if (keystroke->execution_mode == KEYSTROKE_START) {
        action = source_action->data;
        action->fcn(keystroke, action);
    }
}

void actions_finish_action(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct action *action;

    if (keystroke->execution_mode == KEYSTROKE_START) {
        action = source_action->data;
        keystroke->execution_mode = KEYSTROKE_FINISH;
        action->fcn(keystroke, action);
    }
}

void actions_none(struct keystroke *keystroke, const __flash struct action *source_action)
{
}

void actions_tap_dance_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    static const __flash struct actions_tap_dance_actions_data *data;
    static uint8_t saved_modifiers;
    const __flash struct action *action;
    static uint16_t timestamp;
    static struct keystroke saved_keystroke;
    static uint8_t old_layer;
    static struct irq irq;
    static bool tap_dance_key_pressed;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        timestamp = timer_read();
        tap_dance_key_pressed = 1;
        if (irq.interrupts) {
            if (layers_get_active_layer() == old_layer) {
                data = source_action->data;
                if (data->storage->tap_count < data->action_count)
                    ++data->storage->tap_count;
                break;
            }
            action = &data->actions[data->storage->tap_count];
            modifiers_add_permanent(saved_modifiers);
            action->fcn(&saved_keystroke, action);
            modifiers_delete_permanent(saved_modifiers);
            saved_keystroke.execution_mode = KEYSTROKE_FINISH;
            action->fcn(&saved_keystroke, action);
        }
        data = source_action->data;
        saved_modifiers = modifiers_get_permanent();
        data->storage->tap_count = 0;
        data->storage->alive = 1;
        saved_keystroke = *keystroke;
        irq.action = source_action;
        if (irq.interrupts)
            break;
        irq.interrupts = INTERRUPT_KEYSTROKE_START_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        keystrokes_add_irq(&irq);
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp > MAX_TAP_DURATION)
            goto finish;
        break;
    case INTERRUPT_KEYSTROKE_START_EARLY:
        if (keystroke->keyswitch != saved_keystroke.keyswitch)
            goto finish;
        break;
    case KEYSTROKE_FINISH:
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
        action = &data->actions[data->storage->tap_count];
        modifiers_add_permanent(saved_modifiers);
        action->fcn(&saved_keystroke, action);
        modifiers_delete_permanent(saved_modifiers);
        if (!tap_dance_key_pressed) {
            saved_keystroke.execution_mode = KEYSTROKE_FINISH;
            action->fcn(&saved_keystroke, action);
        }
        irq.interrupts = 0;
        data->storage->alive = 0;
    }
}

void actions_hold_tap_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_hold_tap_actions_data *data = source_action->data;
    const __flash struct action *action = &data->hold_action;
    static uint8_t saved_modifiers;
    static uint16_t timestamp;
    static struct irq irq;
    static uint8_t most_recent_keyswitch;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        saved_modifiers = modifiers_get_permanent();
        action->fcn(keystroke, action);
        irq.interrupts = INTERRUPT_KEYSTROKE_START_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        irq.action = source_action;
        keystrokes_add_irq(&irq);
        timestamp = timer_read();
        most_recent_keyswitch = keystroke->keyswitch;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
    case INTERRUPT_KEYSTROKE_START_EARLY:
        irq.interrupts = 0;
        break;
    case KEYSTROKE_FINISH:
        action->fcn(keystroke, action);
        if (!irq.interrupts || keystroke->keyswitch != most_recent_keyswitch)
            break;
        irq.interrupts = 0;
        action = &data->tap_action;
        modifiers_add_permanent(saved_modifiers);
        keystroke->execution_mode = KEYSTROKE_START;
        action->fcn(keystroke, action);
        modifiers_delete_permanent(saved_modifiers);
        keystroke->execution_mode = KEYSTROKE_FINISH;
        action->fcn(keystroke, action);
        break;
    }
}

void actions_tap_hold_actions(struct keystroke *keystroke, const __flash struct action *source_action)
{
    const __flash struct actions_tap_hold_actions_data *data = source_action->data;
    const __flash struct action *action;
    static uint8_t saved_modifiers;
    static uint16_t timestamp;
    static struct keystroke saved_keystroke;
    static struct irq irq;

    switch (keystroke->execution_mode) {
    case KEYSTROKE_START:
        timestamp = timer_read();
        saved_modifiers = modifiers_get_permanent();
        irq.interrupts = INTERRUPT_KEYSTROKE_START_EARLY;
        irq.interrupts |= INTERRUPT_UNCONDITIONAL;
        irq.action = source_action;
        data->storage->last_interrupt = 0;
        keystrokes_add_irq(&irq);
        saved_keystroke = *keystroke;
        break;
    case INTERRUPT_KEYSTROKE_START_EARLY:
        action = &data->tap_action;
        action->fcn(&saved_keystroke, action);
        irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_KEYSTROKE_START_EARLY;
        break;
    case INTERRUPT_UNCONDITIONAL:
        if ((uint16_t)timer_read() - timestamp <= MAX_TAP_DURATION)
            break;
        action = &data->hold_action;
        action->fcn(&saved_keystroke, action);
        irq.interrupts = 0;
        data->storage->last_interrupt = INTERRUPT_UNCONDITIONAL;
        break;
    case KEYSTROKE_FINISH:
        switch (data->storage->last_interrupt) {
        case INTERRUPT_KEYSTROKE_START_EARLY:
            action = &data->tap_action;
            action->fcn(keystroke, action);
            break;
        case 0:
            action = &data->tap_action;
            modifiers_add_permanent(saved_modifiers);
            keystroke->execution_mode = KEYSTROKE_START;
            action->fcn(keystroke, action);
            modifiers_delete_permanent(saved_modifiers);
            keystroke->execution_mode = KEYSTROKE_FINISH;
            action->fcn(keystroke, action);
            irq.interrupts = 0;
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
    case INTERRUPT_KEYSTROKE_START_EARLY:
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
    case KEYSTROKE_START:
        switch (data->storage->state) {
        case ONESHOT_NONE:
            data->storage->irq.interrupts = INTERRUPT_KEYSTROKE_START_EARLY;
            data->storage->irq.interrupts |= INTERRUPT_KEYSTROKE_START_LATE;
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
    case INTERRUPT_KEYSTROKE_START_LATE:
        if (data->storage->state != ONESHOT_INTERRUPTED)
            break;
        if (data->storage->oneshot_keystroke_keyswitch == oneshot_keystroke_keyswitch)
            if (data->storage->oneshot_layer == oneshot_layer) {
                data->storage->irq.interrupts = INTERRUPT_KEYSTROKE_START_EARLY;
                data->storage->irq.interrupts |= INTERRUPT_KEYSTROKE_FINISH_EARLY;
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
    case INTERRUPT_KEYSTROKE_FINISH_EARLY:
        if (keystroke->keyswitch == interrupting_keystroke_keyswitch)
            goto finish;
        break;
    finish:
        data->storage->keystroke.execution_mode = KEYSTROKE_FINISH;
        data->action.fcn(&data->storage->keystroke, &data->action);
        data->storage->state = ONESHOT_NONE;
        data->storage->irq.interrupts = 0;
    }
}
