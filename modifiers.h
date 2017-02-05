#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <stdint.h>
#include "matrix.h"

void modifiers_add_temporary(uint8_t modifiers, keyswitch_t *keyswitch);
void modifiers_delete_temporary(uint8_t modifiers, keyswitch_t *keyswitch);
void modifiers_add_permanent(uint8_t modifiers);
void modifiers_delete_permanent(uint8_t modifiers);
uint8_t modifiers_get(void);

#endif
