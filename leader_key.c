#include "leader.h"
#include "medifiers.h"

static bool leader_key_is_active;
static uint8_t index;
static union {
    uint16_t codes[4];
    uint64_t raw;
} sequence;

void leader_key_start(void)
{
    leader_key_active = 1;
}

void leader_key_end(void)
{
    leader_key_is_active = 0;

    sequence.raw = 0;
}

bool leader_key_is_active(void)
{
    return leader_key_is_active;
}

void leader_key_process(uint8_t code)
{
    sequence.codes[index++] = code | modifiers_get() << 8;
}
