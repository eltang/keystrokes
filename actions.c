#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"
#include "layers.h"
#include "leader_key.h"

void actions_modifiers_and_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t key = ((const __flash uint8_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[1];

    switch (keystroke->state) {
    case KEYSTROKE_START:
        modifiers_add_temporary(modifiers, keystroke->keyswitch);
        keys_add(key);
        break;
    case KEYSTROKE_FINISH:
        keys_delete(key);
        modifiers_delete_temporary(modifiers, keystroke->keyswitch);
        break;
    }
}

void actions_modifiers(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t modifiers = *(const __flash uint8_t *)arg;

    if (keystroke->state == KEYSTROKE_START)
        modifiers_add_permanent(modifiers);
    else
        modifiers_delete_permanent(modifiers);
}

void actions_scancode(keystroke_t *keystroke, const __flash void *arg)
{
    uint8_t key = *(const __flash uint8_t *)arg;

    switch (keystroke->state) {
    case KEYSTROKE_START:
        modifiers_add_temporary(0, keystroke->keyswitch);
        keys_add(key);
        break;
    case KEYSTROKE_FINISH:
        keys_delete(key);
        modifiers_delete_temporary(0, keystroke->keyswitch);
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
//     uint8_t tap_count = callbacks_tap_count_get(keystroke->keyswitch);
//     switch (keystroke->state) {
//     case KEYSTROKE_START:
//         if (tap_count <= action_count) {
//             callbacks_set_action(keystroke->keyswitch, &actions[tap_count]);
//             callbacks_set_mode(keystroke->keyswitch, CALL_START | CALL_ON_KEYSTROKE | CALL_ON_TIMEOUT);
//             callbacks_set_timer(keystroke->keyswitch, MAX_TAP_DURATION);
//         } else {
//             callbacks_cancel(keystroke->keyswitch);
//         }
//         break;
//     case KEYSTROKE_FINISH:
//         if (callback_called_on_timeout(keystroke->keyswitch)) {
//             actions[tap_count].fcn(keystroke, actions[tap_count].arg);
//             callbacks_tap_count_clear(keystroke->keyswitch);
//         } else {
//             callbacks_tap_count_increment(keystroke->keyswitch);
//             callbacks_set_mode(keystroke->keyswitch, CALL_FINISH);
//         }
//         break;
//     }
//     //on every press set the down action of the corresponding action to start after the timeout or when another key is pressed
//     //if on the release the action has been triggered, send the up event of the action and start everything over
//     //if on the release the action has not been triggered, set the action to start as well as finish with the same conditions
// }

// void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg)
// {
//     const __flash action_t *actions = arg;
//     uint8_t callback_mode;
//     action_t action = actions[0];
//
//     switch (keystroke->state) {
//     case KEYSTROKE_START:
//         action.fcn(keystroke, action.arg);
//         callbacks_set_mode(keystroke->keyswitch, CALL_ON_TIMEOUT | CALL_ON_KEYSTROKE_START);
//         callbacks_set_timer(keystroke->keyswitch, MAX_TAP_DURATION);
//         break;
//     case KEYSTROKE_FINISH:
//         action.fcn(keystroke, action.arg);
//         callback_mode = callbacks_get_mode(keystroke->keyswitch);
//         if (callback_mode & (CALLED_ON_KEYSTROKE_START | CALLED_ON_TIMEOUT))
//             return;
//         callbacks_set_mode(keystroke->keyswitch, 0);
//         action = actions[1];
//         keystroke->state = KEYSTROKE_START;
//         action.fcn(keystroke, action.arg);
//         keystroke->state = KEYSTROKE_FINISH;
//         action.fcn(keystroke, action.arg);
//         break;
//     }
// }

// void actions_tap_hold(keystroke_t *keystroke, const __flash void *arg)
// {
//     const __flash action_t *actions = arg;
//     uint8_t callback_mode;
//     action_t action;
//
//     switch (keystroke->state) {
//     case KEYSTROKE_START:
//         callbacks_set_keystroke_action(keystroke->keyswitch, actions);
//         callbacks_set_timeout_action(keystroke->keyswitch, &actions[1]);
//         callbacks_set_mode(keystroke->keyswitch, CALL_START | CALL_ON_KEYSTROKE_START | CALL_ON_TIMEOUT);
//         callbacks_set_timer(keystroke->keyswitch, MAX_TAP_DURATION);
//         break;
//     case KEYSTROKE_FINISH:
//         action = actions[0];
//         callback_mode = callbacks_get_mode(keystroke->keyswitch);
//         switch (callback_mode & (CALLED_ON_KEYSTROKE_START | CALLED_ON_TIMEOUT)) {
//             case CALLED_ON_KEYSTROKE_START:
//                 action.fcn(keystroke, action.arg);
//                 break;
//             case 0:
//                 callbacks_set_mode(keystroke->keyswitch, 0);
//                 keystroke->state = KEYSTROKE_START;
//                 action.fcn(keystroke, action.arg);
//                 keystroke->state = KEYSTROKE_FINISH;
//                 action.fcn(keystroke, action.arg);
//                 break;
//             case CALLED_ON_TIMEOUT:
//                 action = actions[1];
//                 action.fcn(keystroke, action.arg);
//                 break;
//         }
//         break;
//     }
// }

void actions_leader_key_start(keystroke_t *keystroke, const __flash void *arg)
{
    if (keystroke->state == KEYSTROKE_START)
        leader_key_start(keystroke->keyswitch);
}
