#ifndef KEYS_H
#define KEYS_H

#include <stdint.h>
#include "matrix.h"

void keys_add(uint8_t code);
void keys_delete(uint8_t code);
uint8_t *keys_get(void);

#endif
