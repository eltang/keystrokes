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
    usb_send_keyboard_report();
}

void modifiers_clear_temporary(void)
{
    temporary_modifiers = 0;
    usb_send_keyboard_report();
}

void modifiers_add_permanent(uint8_t modifiers)
{
    permanent_modifiers.set |= modifiers;

    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++permanent_modifiers.modifiers[i];
    usb_send_keyboard_report();
}

void modifiers_delete_permanent(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;) {
        if (modifiers & 1 << i)
            if (!--permanent_modifiers.modifiers[i])
                permanent_modifiers.set &= ~(1 << i);
    }
    usb_send_keyboard_report();
}

uint8_t modifiers_get(void)
{
    return permanent_modifiers.set | temporary_modifiers;
}
