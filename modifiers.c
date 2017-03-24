#include "modifiers.h"
#include "main.h"

static uint8_t current_modifier_quantities[8];
static uint8_t stashed_modifier_quantities[8], stashed_modifiers;

void modifiers_add(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++current_modifier_quantities[i];
    SendKeyboardReport();
}

void modifiers_delete(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            --current_modifier_quantities[i];
    SendKeyboardReport();
}

uint8_t modifiers_get(void)
{
    uint8_t modifiers = 0;

    for (uint8_t i = 8; i--;)
        if (current_modifier_quantities[i])
            modifiers |= 1 << i;
    return modifiers;
}

void modifiers_stash(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i) {
            stashed_modifier_quantities[i] = current_modifier_quantities[i];
            current_modifier_quantities[i] = 0;
        }
    stashed_modifiers = modifiers;
    SendKeyboardReport();
}

void modifiers_pop_stash(void)
{
    for (uint8_t i = 8; i--;)
        if (stashed_modifiers & 1 << i)
            current_modifier_quantities[i] = stashed_modifier_quantities[i];
    SendKeyboardReport();
}
