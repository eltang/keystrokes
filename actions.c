#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"
#include "layers.h"

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
