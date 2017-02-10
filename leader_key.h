#ifndef LEADER_KEY_H
#define LEADER_KEY_H

#include "actions.h"

typedef struct {
    uint64_t sequence;
    action_t action;
} leader_key_dictionary_entry_t;

void leader_key_start(uint8_t keyswitch);
void leader_key_end(keystroke_t *keystroke, const __flash void *arg);
bool leader_key_is_active(void);
void leader_key_process(uint8_t code);

#endif
