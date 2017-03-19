#ifndef LEADER_KEY_H
#define LEADER_KEY_H

#include "actions.h"

struct leader_key_dictionary_entry {
    struct action action;
    const __flash uint16_t *sequence;
    uint8_t sequence_length;
};

void leader_key_start(struct keystroke *keystroke);
bool leader_key_is_active(void);
void leader_key_process(uint8_t code);
void leader_key_task(void);

#endif
