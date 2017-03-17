#include "leader_key.h"
#include "modifiers.h"
#include "layout.h"
#include "timer.h"

static bool leader_key_active;
static struct {
    union {
        uint16_t codes[4];
        uint64_t raw;
    };
    uint8_t index;
} sequence;
static struct keystroke leader_key_keystroke;
static uint16_t leader_key_timestamp;

static void leader_key_end(void)
{
    const __flash struct leader_key_dictionary_entry *entry;

    leader_key_active = 0;
    entry = leader_key_dictionary;
    while (entry->sequence) {
        if (entry->sequence == sequence.raw) {
            entry->action.fcn(&leader_key_keystroke, &entry->action);
            leader_key_keystroke.execution_mode = KEYSTROKE_END;
            entry->action.fcn(&leader_key_keystroke, &entry->action);
            break;
        }
        entry++;
    }
    sequence.raw = 0;
    sequence.index = 0;
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
    if (sequence.index == 4)
        return;
    sequence.codes[sequence.index++] = code | modifiers_get() << 8;
    leader_key_timestamp = timer_read();
}

void leader_key_task(void)
{
    if (leader_key_active)
        if ((uint16_t)timer_read() - leader_key_timestamp > 1000)
            leader_key_end();
}
