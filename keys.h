#ifndef KEYS_H
#define KEYS_H

#include <stdint.h>

void keys_add_scancode(uint8_t code);
void keys_delete_scancode(uint8_t code);
uint8_t *keys_get_scancode(void);
void keys_add_power_management(uint8_t code);
void keys_delete_power_management(uint8_t code);
uint8_t keys_get_power_management(void);
void keys_add_multimedia(uint16_t code);
void keys_delete_multimedia(uint16_t code);
uint16_t keys_get_multimedia(void);

#endif
