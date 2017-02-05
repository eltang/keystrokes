#include "leader_key.h"
#include "modifiers.h"
#include "layout.h"
#include "callbacks.h"

static bool leader_key_active;
static struct {
    union {
        uint16_t codes[4];
        uint64_t raw;
    };
    uint8_t index;
} sequence;
static keyswitch_t leader_key_keyswitch;
const __flash action_t foo = { leader_key_end };

void leader_key_end(keystroke_t *keystroke, const __flash void *arg)
{
    const __flash leader_key_dictionary_entry_t *entry;
    keystroke_t leader_key_keystroke;

    if (keystroke->stage == KEYSTROKE_FINISH)
        return;
    leader_key_active = 0;
    entry = leader_key_dictionary;
    while (entry->sequence) {
        if (entry->sequence == sequence.raw) {
            leader_key_keystroke.keyswitch = leader_key_keyswitch;
            leader_key_keystroke.stage = KEYSTROKE_START;
            entry->action.fcn(&leader_key_keystroke, entry->action.arg);
            leader_key_keystroke.stage = KEYSTROKE_FINISH;
            entry->action.fcn(&leader_key_keystroke, entry->action.arg);
            break;
        }
        entry++;
    }
    sequence.raw = 0;
    sequence.index = 0;
}

void leader_key_start(keyswitch_t *keyswitch)
{
    leader_key_active = 1;
    leader_key_keyswitch = *keyswitch;
    callbacks_set_mode(keyswitch, CALL_START | CALL_ON_TIMEOUT);
    callbacks_set_action(keyswitch, &foo);
    callbacks_set_timer(keyswitch, 1000);
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
    callbacks_set_timer(&leader_key_keyswitch, 1000);
}
