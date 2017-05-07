#include "commands.h"

#include <string.h>

#define COMMAND_BUFFER_SIZE 32

static uint8_t command_buffer[COMMAND_BUFFER_SIZE];
static uint8_t command_buffer_index;

bool commands_append(uint8_t character)
{
    if (command_buffer_index >= COMMAND_BUFFER_SIZE)
        return 1;
    command_buffer[command_buffer_index++] = character;
    return 0;
}

bool commands_set(uint8_t *string)
{
    size_t length = strlen(string);

    if (length >= COMMAND_BUFFER_SIZE)
        return 1;
    command_buffer_index = length;
    strcpy(command_buffer, string);
    return 0;
}

void commands_execute(void)
{
    command_buffer[command_buffer_index] = 0;


}

void commnands_clear(void)
{
    command_buffer_index = 0;
}

void commands_erase(void)
{
    --command_buffer_index;
}

