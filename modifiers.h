#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <stdint.h>
#include "matrix.h"

void modifiers_add(uint8_t modifiers);
void modifiers_delete(uint8_t modifiers);
uint8_t modifiers_get_disguised_modifiers(void);
uint8_t modifiers_get_frozen_modifiers(void);
void modifiers_set_disguise(uint16_t disguise);
void modifiers_remove_disguise(uint16_t disguise);
void modifiers_freeze(void);
void modifiers_unfreeze(void);

#endif
