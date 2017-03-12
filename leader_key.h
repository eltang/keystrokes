#ifndef LEADER_KEY_H
#define LEADER_KEY_H

#include "actions.h"

struct leader_key_dictionary_entry {
    uint64_t sequence;
    struct action action;
};

void leader_key_start(struct keystroke *keystroke);
bool leader_key_is_active(void);
void leader_key_process(uint8_t code);
void leader_key_task(void);

#endif
