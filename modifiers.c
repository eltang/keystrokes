#include "modifiers.h"
#include "KeyboardMouse.h"

static struct {
    uint8_t modifiers[8];
    uint8_t set;
} permanent_modifiers;

typedef struct {
    keyswitch_t keyswitch;
    uint8_t modifiers;
} temporary_modifier_set_t;

static struct {
    temporary_modifier_set_t sets[ROWS * COLUMNS];
    uint8_t index;
} temporary_modifiers;

void modifiers_add_temporary(uint8_t modifiers, keyswitch_t *keyswitch)
{
    temporary_modifier_set_t new_set = { *keyswitch, modifiers };
    temporary_modifiers.sets[temporary_modifiers.index++] = new_set;
}

void modifiers_delete_temporary(uint8_t modifiers, keyswitch_t *keyswitch)
{
    uint8_t i;

    for (i = temporary_modifiers.index--; i--;) {
        keyswitch_t *set_keyswitch = &temporary_modifiers.sets[i].keyswitch;
        if (keyswitch->column == set_keyswitch->column && keyswitch->row == set_keyswitch->row)
            break;
    }
    for (; i != temporary_modifiers.index; ++i)
        temporary_modifiers.sets[i] = temporary_modifiers.sets[i + 1];
}

void modifiers_add_permanent(uint8_t modifiers)
{
    permanent_modifiers.set |= modifiers;

    for (uint8_t i = 8; i--;)
        if (modifiers & 1 << i)
            ++permanent_modifiers.modifiers[i];
}

void modifiers_delete_permanent(uint8_t modifiers)
{
    for (uint8_t i = 8; i--;) {
        if (modifiers & 1 << i)
            if (!--permanent_modifiers.modifiers[i])
                permanent_modifiers.set &= ~(1 << i);
    }
}

uint8_t modifiers_get(void)
{
    uint8_t modifiers = permanent_modifiers.set;

    if (temporary_modifiers.index)
        modifiers |= temporary_modifiers.sets[temporary_modifiers.index - 1].modifiers;
    return modifiers;
}
