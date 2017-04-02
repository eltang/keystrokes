#include "modifiers.h"
#include "main.h"

static uint8_t regular_modifiers[8], all_regular_modifiers, temporary_modifiers;
static const __flash struct action *temporary_modifiers_action;

void modifiers_add(uint8_t modifiers)
{
    all_regular_modifiers |= modifiers;
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++regular_modifiers[i];
    SendKeyboardReport();
}

void modifiers_delete(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            if (!--regular_modifiers[i])
                all_regular_modifiers &= ~(1 << i);
    SendKeyboardReport();
}

uint8_t modifiers_get(void)
{
    return all_regular_modifiers | temporary_modifiers;
}

void modifiers_set_temporary(uint8_t modifiers, const __flash struct action *action)
{
    temporary_modifiers_action = action;
    temporary_modifiers = modifiers;
    SendKeyboardReport();
}

void modifiers_unset_temporary(const __flash struct action *action)
{
    if (temporary_modifiers_action != action)
        return;
    temporary_modifiers = 0;
    SendKeyboardReport();
}
