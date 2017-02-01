#include "modifiers.h"
#include "KeyboardMouse.h"

static union {
    uint8_t modifiers[8];
    uint64_t raw;
} permanent_modifiers;

typedef struct {
    keyswitch_t keyswitch;
    uint8_t modifiers;
} temporary_modifier_set_t;

static struct {
    temporary_modifier_set_t sets[ROWS * COLUMNS];
    uint8_t index;
} temporary_modifiers;

void modifiers_add_temporary(uint8_t modifiers, keyswitch_t keyswitch)
{
    temporary_modifier_set_t new_set = { keyswitch, modifiers };
    temporary_modifiers.sets[temporary_modifiers.index++] = new_set;
    usb_wait_until_keyboard_report_sent();
}

void modifiers_delete_temporary(uint8_t modifiers, keyswitch_t keyswitch)
{
    uint8_t i;

    for (i = temporary_modifiers.index--; i--;) {
        keyswitch_t set_keyswitch = temporary_modifiers.sets[i].keyswitch;
        if (keyswitch.column == set_keyswitch.column && keyswitch.row == set_keyswitch.row)
            break;
    }
    for (; i != temporary_modifiers.index; ++i)
        temporary_modifiers.sets[i] = temporary_modifiers.sets[i + 1];
    usb_wait_until_keyboard_report_sent();
}

void modifiers_add_permanent(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;)
        permanent_modifiers.modifiers[i] += !!(modifiers & 1 << i);
    usb_wait_until_keyboard_report_sent();
}

void modifiers_delete_permanent(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;) {
        bool temp = permanent_modifiers.modifiers[i] && modifiers & 1 << i;
        permanent_modifiers.modifiers[i] -= temp;
    }
    usb_wait_until_keyboard_report_sent();
}

void modifiers_create_report(uint8_t *buffer)
{
    if (temporary_modifiers.index)
        *buffer = temporary_modifiers.sets[temporary_modifiers.index - 1].modifiers;
    for (uint8_t i = 8; i--;) {
        if (permanent_modifiers.modifiers[i])
            *buffer |= 1 << i;
    }
}
