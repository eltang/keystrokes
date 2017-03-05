#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"
#include "layers.h"
#include "leader_key.h"

void actions_modifiers_and_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = ((const __flash uint8_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[1];

    switch (keystroke->state) {
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

void actions_modifiers(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t modifiers = *(const __flash uint8_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        modifiers_add_permanent(modifiers);
        break;
    case KEYSTROKE_FINISH:
        modifiers_delete_permanent(modifiers);
        break;
    }
}

void actions_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = *(const __flash uint8_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        keys_add_scancode(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_scancode(code);
        break;
    }
}

void actions_layers_goto(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t layer;

    if (keystroke->state == KEYSTROKE_START) {
        layer = *(const __flash uint8_t *)arg;
        layers_set_primary_layer(layer);
    }
}

void actions_layers_visit(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t layer = *(const __flash uint8_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        layers_activate_secondary_layer(layer);
        break;
    case KEYSTROKE_FINISH:
        layers_deactivate_secondary_layer(layer);
        break;
    }
}

void actions_reset(keystroke_t *keystroke, const __flash void *arg)
{
    if (keystroke->state == KEYSTROKE_START)
        Jump_To_Bootloader();
}

void actions_multiple_actions(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *action = arg;

    while (action++->fcn)
        action->fcn(keystroke, action->arg);
}

void actions_none(keystroke_t *keystroke, const __flash void *arg)
{
}

void actions_tap_dance(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *actions = arg;
    static uint8_t action_count, tap_count, tap_action_modifiers;
    action_t action;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        if (!action_count) {
            tap_action_modifiers = modifiers_get_permanent();
            do
                ++action_count;
            while (actions[action_count].fcn != actions_none);
        } else if (keystroke->previous_state == KEYSTROKE_FINISH)
            if (tap_count < action_count)
                ++tap_count;
        break;
    case KEYSTROKE_START | KEYSTROKE_TIMED_OUT:
    case KEYSTROKE_START | KEYSTROKE_INTERRUPTED:
    case KEYSTROKE_FINISH | KEYSTROKE_INTERRUPTED:
    case KEYSTROKE_FINISH | KEYSTROKE_TIMED_OUT:
        if (action_count) {
            action = actions[tap_count];
            keystroke->state = KEYSTROKE_START;
            modifiers_add_permanent(tap_action_modifiers);
            action.fcn(keystroke, action.arg);
            modifiers_delete_permanent(tap_action_modifiers);
            keystroke->state = KEYSTROKE_FINISH;
            action.fcn(keystroke, action.arg);
            action_count = 0;
            tap_count = 0;
        }
        break;
    }
}

void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *actions = arg;
    action_t action = actions[0];
    static uint8_t tap_action_modifiers;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        tap_action_modifiers = modifiers_get_permanent();
        action.fcn(keystroke, action.arg);
        break;
    case KEYSTROKE_FINISH:
        action.fcn(keystroke, action.arg);
        if (keystroke->previous_state != KEYSTROKE_START)
            return;
        action = actions[1];
        keystroke->state = KEYSTROKE_START;
        modifiers_add_permanent(tap_action_modifiers);
        action.fcn(keystroke, action.arg);
        modifiers_delete_permanent(tap_action_modifiers);
        keystroke->state = KEYSTROKE_FINISH;
        action.fcn(keystroke, action.arg);
        break;
    }
}

void actions_tap_hold(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *actions = arg;
    action_t action;
    static uint8_t tap_action_modifiers;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        tap_action_modifiers = modifiers_get_permanent();
        break;
    case KEYSTROKE_START | KEYSTROKE_TIMED_OUT:
        action = actions[1];
        keystroke->state = KEYSTROKE_START;
        action.fcn(keystroke, action.arg);
        break;
    case KEYSTROKE_START | KEYSTROKE_INTERRUPTED:
        if (keystroke->interruptions == 1) {
            action = actions[0];
            keystroke->state = KEYSTROKE_START;
            action.fcn(keystroke, action.arg);
        }
        break;
    case KEYSTROKE_FINISH:
        action = actions[0];
        keystroke->state = KEYSTROKE_FINISH;
        switch (keystroke->previous_state) {
            case KEYSTROKE_START | KEYSTROKE_INTERRUPTED:
                action.fcn(keystroke, action.arg);
                break;
            case KEYSTROKE_START:
                keystroke->state = KEYSTROKE_START;
                modifiers_add_permanent(tap_action_modifiers);
                action.fcn(keystroke, action.arg);
                modifiers_delete_permanent(tap_action_modifiers);
                keystroke->state = KEYSTROKE_FINISH;
                action.fcn(keystroke, action.arg);
                break;
            case KEYSTROKE_START | KEYSTROKE_TIMED_OUT | KEYSTROKE_INTERRUPTED:
            case KEYSTROKE_START | KEYSTROKE_TIMED_OUT:
                action = actions[1];
                action.fcn(keystroke, action.arg);
                break;
        }
        break;
    }
}

void actions_leader_key_start(keystroke_t *keystroke, const __flash void *arg)
{
    if (keystroke->state == KEYSTROKE_START)
        leader_key_start(keystroke->keyswitch);
}

void actions_modifiers_and_power_management(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = ((const __flash uint8_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[1];

    switch (keystroke->state) {
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

void actions_power_management(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = *(const __flash uint8_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        keys_add_power_management(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_power_management(code);
        break;
    }
}

void actions_modifiers_and_multimedia(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = ((const __flash uint16_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[2];

    switch (keystroke->state) {
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

void actions_multimedia(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t code = *(const __flash uint16_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        keys_add_multimedia(code);
        break;
    case KEYSTROKE_FINISH:
        keys_delete_multimedia(code);
        break;
    }
}
