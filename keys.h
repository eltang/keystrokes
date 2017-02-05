#ifndef KEYS_H
#define KEYS_H

#include <stdint.h>
#include "matrix.h"

void keys_add(uint8_t code, keyswitch_t *keyswitch);
void keys_delete(uint8_t code, keyswitch_t *keyswitch);
void keys_create_report(uint8_t *buffer);

#endif
