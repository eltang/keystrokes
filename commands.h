#ifndef COMMANDS_H
#define COMMANDS_H

bool commands_append(uint8_t character);
bool commands_set(uint8_t *string);
void commands_execute(void);
void commnands_clear(void);
void commands_erase(void);

#endif
