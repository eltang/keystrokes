#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"
#include "layers.h"
#include "callbacks.h"
#include "leader_key.h"

void actions_modifiers_and_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t key = ((const __flash uint8_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[1];

    if (keystroke->stage == KEYSTROKE_START) {
        modifiers_add_temporary(modifiers, &keystroke->keyswitch);
        keys_add(key, &keystroke->keyswitch);
    } else {
        keys_delete(key, &keystroke->keyswitch);
        modifiers_delete_temporary(modifiers, &keystroke->keyswitch);
    }
}

void actions_modifiers(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t modifiers = *(const __flash uint8_t *)arg;

    if (keystroke->stage == KEYSTROKE_START)
        modifiers_add_permanent(modifiers);
    else
        modifiers_delete_permanent(modifiers);
}

void actions_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t key = *(const __flash uint8_t *)arg;

    if (keystroke->stage == KEYSTROKE_START) {
        modifiers_add_temporary(0, &keystroke->keyswitch);
        keys_add(key, &keystroke->keyswitch);
    } else {
        keys_delete(key, &keystroke->keyswitch);
        modifiers_delete_temporary(0, &keystroke->keyswitch);
    }
}

void actions_layers_goto(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t layer;

    if (keystroke->stage == KEYSTROKE_FINISH)
        return;
    layer = *(const __flash uint8_t *)arg;
    layers_set_primary_layer(layer);
}

void actions_layers_visit(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t layer = *(const __flash uint8_t *)arg;

    if (keystroke->stage == KEYSTROKE_START)
        layers_activate_secondary_layer(layer);
    else
        layers_deactivate_secondary_layer(layer);
}

void actions_reset(keystroke_t *keystroke, const __flash void *arg)
{
    reset();
}

void actions_multiple_actions(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *action = arg;

    while (action++->fcn)
        action->fcn(keystroke, action->arg);
}

// void actions_tap_dance(keystroke_t *keystroke, const __flash void *arg)
// {
//     const __flash action_t *actions = arg;
//     uint8_t action_count = 0;
//
//     while (actions[action_count].fcn) {
//         ++action_count;
//     }
//     uint8_t tap_count = callbacks_tap_count_get(&keystroke->keyswitch);
//     switch (keystroke->stage) {
//     case KEYSTROKE_START:
//         if (tap_count <= action_count) {
//             callbacks_set_action(&keystroke->keyswitch, &actions[tap_count]);
//             callbacks_set_mode(&keystroke->keyswitch, CALL_START | CALL_ON_KEYSTROKE | CALL_ON_TIMEOUT);
//             callbacks_set_timer(&keystroke->keyswitch, MAX_TAP_DURATION);
//         } else {
//             callbacks_cancel(&keystroke->keyswitch);
//         }
//         break;
//     case KEYSTROKE_FINISH:
//         if (callback_called_on_timeout(&keystroke->keyswitch)) {
//             actions[tap_count].fcn(keystroke, actions[tap_count].arg);
//             callbacks_tap_count_clear(&keystroke->keyswitch);
//         } else {
//             callbacks_tap_count_increment(&keystroke->keyswitch);
//             callbacks_set_mode(&keystroke->keyswitch, CALL_FINISH);
//         }
//         break;
//     }
//     //on every press set the down action of the corresponding action to start after the timeout or when another key is pressed
//     //if on the release the action has been triggered, send the up event of the action and start everything over
//     //if on the release the action has not been triggered, set the action to start as well as finish with the same conditions
// }

void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *actions = arg;

    switch (keystroke->stage) {
    case KEYSTROKE_START:
        actions[0].fcn(keystroke, actions[0].arg);
        callbacks_set_mode(&keystroke->keyswitch, CALL_ON_TIMEOUT | CALL_ON_KEYSTROKE_START);
        callbacks_set_timer(&keystroke->keyswitch, MAX_TAP_DURATION);
        break;
    case KEYSTROKE_FINISH:
        actions[0].fcn(keystroke, actions[0].arg);
        if (!callbacks_get_mode(&keystroke->keyswitch))
            return;
        callbacks_cancel(&keystroke->keyswitch);
        keystroke->stage = KEYSTROKE_START;
        actions[1].fcn(keystroke, actions[1].arg);
        keystroke->stage = KEYSTROKE_FINISH;
        actions[1].fcn(keystroke, actions[1].arg);
        break;
    }
}

void actions_tap_hold(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash action_t *actions = arg;

    switch (keystroke->stage) {
    case KEYSTROKE_START:
        callbacks_set_action(&keystroke->keyswitch, &actions[1]);
        callbacks_set_mode(&keystroke->keyswitch, CALL_START | CALL_ON_TIMEOUT);
        callbacks_set_timer(&keystroke->keyswitch, MAX_TAP_DURATION);
        break;
    case KEYSTROKE_FINISH:
        if (callbacks_get_mode(&keystroke->keyswitch)) {
            callbacks_cancel(&keystroke->keyswitch);
            keystroke->stage = KEYSTROKE_START;
            actions[0].fcn(keystroke, actions[0].arg);
            keystroke->stage = KEYSTROKE_FINISH;
            actions[0].fcn(keystroke, actions[0].arg);
        } else
            actions[1].fcn(keystroke, actions[1].arg);
        break;
    }
}

void actions_leader_key_start(keystroke_t *keystroke, const __flash void *arg)
{
    if (keystroke->stage == KEYSTROKE_FINISH)
        return;
    leader_key_start(&keystroke->keyswitch);
}
