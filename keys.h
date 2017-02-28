#ifndef KEYS_H
#define KEYS_H

#include <stdint.h>

void keys_add_scancode(uint8_t code);
void keys_delete_scancode(uint8_t code);
uint8_t *keys_get_scancode(void);
void keys_add_generic_desktop(uint8_t code);
void keys_delete_generic_desktop(uint8_t code);
uint8_t keys_get_generic_desktop(void);
void keys_add_consumer(uint16_t code);
void keys_delete_consumer(uint16_t code);
uint16_t keys_get_consumer(void);

#endif
