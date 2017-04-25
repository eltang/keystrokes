#include "modifiers.h"
#include "main.h"

static uint8_t raw_modifiers[8], frozen_modifiers, disguised_modifiers;
static uint8_t modifiers_disguised, modifiers_frozen;
static uint16_t active_disguise;

void modifiers_update_disguised_modifiers(void)
{
    disguised_modifiers = frozen_modifiers;
    if (modifiers_disguised) {
        disguised_modifiers &= ~(active_disguise >> 8);
        disguised_modifiers |= active_disguise & 0xFF;
    }
    SendKeyboardReport();
}
void modifiers_add(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++raw_modifiers[i];
    if (modifiers_frozen)
        return;
    frozen_modifiers |= modifiers;
    modifiers_update_disguised_modifiers();
}

void modifiers_delete(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            if (!--raw_modifiers[i] && !modifiers_frozen)
                frozen_modifiers &= ~(1 << i);
    if (modifiers_frozen)
        return;
    modifiers_update_disguised_modifiers();
}

uint8_t modifiers_get_disguised_modifiers(void)
{
    return disguised_modifiers;
}

uint8_t modifiers_get_frozen_modifiers(void)
{
    return frozen_modifiers;
}

void modifiers_set_disguise(uint16_t disguise)
{
    if (active_disguise != disguise) {
        modifiers_disguised = 0;
        active_disguise = disguise;
    }
    ++modifiers_disguised;
    modifiers_update_disguised_modifiers();
}

void modifiers_remove_disguise(uint16_t disguise)
{
    if (active_disguise == disguise && modifiers_disguised)
        if (!--modifiers_disguised)
            modifiers_update_disguised_modifiers();
}

void modifiers_freeze(void)
{
    ++modifiers_frozen;
}

void modifiers_unfreeze(void)
{
    --modifiers_frozen;
    frozen_modifiers = 0;
    for (uint8_t i = 8; i--;)
        if (raw_modifiers[i])
            frozen_modifiers |= 1 << i;
    modifiers_update_disguised_modifiers();
}
