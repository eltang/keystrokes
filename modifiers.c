#include "modifiers.h"
#include "main.h"

static uint8_t current_modifier_quantities[8], current_modifiers;

void modifiers_add(uint8_t modifiers)
{
    current_modifiers |= modifiers;

    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++current_modifier_quantities[i];
    SendKeyboardReport();
}

void modifiers_delete(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;) {
        if (modifiers & 1 << i)
            if (!--current_modifier_quantities[i])
                current_modifiers &= ~(1 << i);
    }
    SendKeyboardReport();
}

uint8_t modifiers_get(void)
{
    return current_modifiers;
}
