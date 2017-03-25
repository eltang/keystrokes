#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <stdint.h>
#include "matrix.h"

void modifiers_add(uint8_t modifiers);
void modifiers_delete(uint8_t modifiers);
uint8_t modifiers_get(void);
void modifiers_set_temporary(uint8_t modifiers, const __flash struct action *action);
void modifiers_unset_temporary(const __flash struct action *action);

#endif
