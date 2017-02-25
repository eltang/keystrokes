#include "modifiers.h"
#include "main.h"

static struct {
    uint8_t modifiers[8];
    uint8_t set;
} permanent_modifiers;

static uint8_t temporary_modifiers;

void modifiers_set_temporary(uint8_t modifiers)
{
    temporary_modifiers = modifiers;
    SendKeyboardReport();
}

void modifiers_unset_temporary(uint8_t modifiers)
{
    if (temporary_modifiers != modifiers)
        return;
    modifiers_clear_temporary();
}

void modifiers_clear_temporary(void)
{
    temporary_modifiers = 0;
    SendKeyboardReport();
}

void modifiers_add_permanent(uint8_t modifiers)
{
    permanent_modifiers.set |= modifiers;

    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++permanent_modifiers.modifiers[i];
    SendKeyboardReport();
}

void modifiers_delete_permanent(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;) {
        if (modifiers & 1 << i)
            if (!--permanent_modifiers.modifiers[i])
                permanent_modifiers.set &= ~(1 << i);
    }
    SendKeyboardReport();
}

uint8_t modifiers_get(void)
{
    return permanent_modifiers.set | temporary_modifiers;
}

uint8_t modifiers_get_permanent(void)
{
    return permanent_modifiers.set;
}
