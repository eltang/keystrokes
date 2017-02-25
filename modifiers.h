#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <stdint.h>
#include "matrix.h"

void modifiers_set_temporary(uint8_t modifiers);
void modifiers_unset_temporary(uint8_t modifiers);
void modifiers_clear_temporary(void);
void modifiers_add_permanent(uint8_t modifiers);
void modifiers_delete_permanent(uint8_t modifiers);
uint8_t modifiers_get(void);
uint8_t modifiers_get_permanent(void);

#endif
