#include <avr/pgmspace.h>

#include "leader_key.h"
#include "modifiers.h"
#include "layout.h"
#include "timer.h"

#ifndef MAX_LEADER_KEY_SEQUENCE_LENGTH
#define MAX_LEADER_KEY_SEQUENCE_LENGTH 8
#endif

static bool leader_key_active;
static uint16_t sequence[MAX_LEADER_KEY_SEQUENCE_LENGTH];
static uint8_t sequence_index;
static struct keystroke leader_key_keystroke;
static uint16_t leader_key_timestamp;

static void leader_key_end(void)
{
    leader_key_active = 0;
    for (uint8_t i = leader_key_dictionary_length; i--;)
        if (sequence_index == leader_key_dictionary[i].sequence_length)
            if (!memcmp_P(sequence, leader_key_dictionary[i].sequence, 2 * sequence_index)) {
                leader_key_dictionary[i].action.fcn(&leader_key_keystroke, &leader_key_dictionary[i].action);
                leader_key_keystroke.execution_mode = KEYSTROKE_END;
                leader_key_dictionary[i].action.fcn(&leader_key_keystroke, &leader_key_dictionary[i].action);
                break;
            }
    while (sequence_index)
        sequence[--sequence_index] = 0;
}

void leader_key_start(struct keystroke *keystroke)
{
    if (leader_key_active)
        return;
    leader_key_active = 1;
    leader_key_keystroke = *keystroke;
    leader_key_timestamp = timer_read();
}

bool leader_key_is_active(void)
{
    return leader_key_active;
}

void leader_key_process(uint8_t code)
{
    if (sequence_index == MAX_LEADER_KEY_SEQUENCE_LENGTH)
        return;
    sequence[sequence_index++] = code;
    leader_key_timestamp = timer_read();
}

void leader_key_task(void)
{
    if (leader_key_active)
        if ((uint16_t)timer_read() - leader_key_timestamp > 1000)
            leader_key_end();
}
