#ifndef ACTIONS_H
#define ACTIONS_H

#include "keystrokes.h"

typedef struct {
    void (*fcn)(keystroke_t *, const __flash void *);
    const __flash void *arg;
} action_t;

typedef struct {
    uint8_t previous_keystroke_state;
} actions_hold_tap_storage_t;

typedef struct {
    action_t hold_action;
    action_t tap_action;
    actions_hold_tap_storage_t *storage;
} actions_hold_tap_data_t;

typedef struct {
    uint8_t previous_keystroke_state;
    bool interrupted;
} actions_tap_hold_storage_t;

typedef struct {
    action_t tap_action;
    action_t hold_action;
    actions_tap_hold_storage_t *storage;
} actions_tap_hold_data_t;

typedef struct {
    uint8_t previous_keystroke_state;
    uint8_t tap_count;
    bool alive;
} actions_tap_dance_storage_t;

typedef struct {
    const __flash action_t *actions;
    actions_tap_dance_storage_t *storage;
    uint8_t action_count;
} actions_tap_dance_data_t;

void actions_modifiers_and_scancode(keystroke_t *keystroke, const __flash void *arg);
void actions_modifiers(keystroke_t *keystroke, const __flash void *arg);
void actions_scancode(keystroke_t *keystroke, const __flash void *arg);
void actions_multiple_actions(keystroke_t *keystroke, const __flash void *arg);
void actions_tap_dance(keystroke_t *keystroke, const __flash void *arg);
void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg);
void actions_layers_goto(keystroke_t *keystroke, const __flash void *arg);
void actions_layers_visit(keystroke_t *keystroke, const __flash void *arg);
void actions_reset(keystroke_t *keystroke, const __flash void *arg);
void actions_none(keystroke_t *keystroke, const __flash void *arg);
void actions_multiple_actions(keystroke_t *keystroke, const __flash void *arg);
void actions_tap_dance(keystroke_t *keystroke, const __flash void *arg);
void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg);
void actions_tap_hold(keystroke_t *keystroke, const __flash void *arg);
void actions_leader_key_start(keystroke_t *keystroke, const __flash void *arg);
void actions_modifiers_and_power_management(keystroke_t *keystroke, const __flash void *arg);
void actions_power_management(keystroke_t *keystroke, const __flash void *arg);
void actions_modifiers_and_multimedia(keystroke_t *keystroke, const __flash void *arg);
void actions_multimedia(keystroke_t *keystroke, const __flash void *arg);

#endif
