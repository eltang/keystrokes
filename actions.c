#include "actions.h"
#include "modifiers.h"
#include "keys.h"
#include "reset.h"

void actions_modifier_and_scancode_wrapper(keystroke_t keystroke, const __flash void *arg)
{
    uint8_t key = ((const __flash uint8_t *)arg)[0];
    uint8_t modifiers = ((const __flash uint8_t *)arg)[1];

    actions_modifiers_and_scancode(keystroke, key, modifiers);
}

void actions_modifiers_and_scancode(keystroke_t keystroke, uint8_t key, uint8_t modifiers)
{
    if (keystroke.stage == KEYSTROKE_START) {
        modifiers_add_temporary(modifiers, keystroke.keyswitch);
        keys_add(key, keystroke.keyswitch);
    } else {
        keys_delete(key, keystroke.keyswitch);
        modifiers_delete_temporary(modifiers, keystroke.keyswitch);
    }
}

void actions_modifiers_wrapper(keystroke_t keystroke, const __flash void *arg)
{
    uint8_t modifiers = *(const __flash uint8_t *)arg;

    actions_modifiers(modifiers, keystroke);
}

void actions_modifiers(uint8_t modifiers, keystroke_t keystroke)
{
    if (keystroke.stage == KEYSTROKE_START)
        modifiers_add_permanent(modifiers);
    else
        modifiers_delete_permanent(modifiers);
}

void actions_scancode_wrapper(keystroke_t keystroke, const __flash void *arg)
{
    uint8_t key = *(const __flash uint8_t *)arg;

    actions_scancode(keystroke, key);
}

void actions_scancode(keystroke_t keystroke, uint8_t key)
{
    if (keystroke.stage == KEYSTROKE_START) {
        modifiers_add_temporary(0, keystroke.keyswitch);
        keys_add(key, keystroke.keyswitch);
    } else {
        keys_delete(key, keystroke.keyswitch);
        modifiers_delete_temporary(0, keystroke.keyswitch);
    }
}

void actions_reset(keystroke_t keystroke, const __flash void *arg)
{
    reset();
}
