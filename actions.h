#ifndef ACTIONS_H
#define ACTIONS_H

#include "keystrokes.h"

struct action {
    void (*fcn)(struct keystroke *, const __flash struct action *);
    const __flash void *data;
};

struct actions_hold_tap_actions_data {
    struct action hold_action;
    struct action tap_action;
};

struct actions_tap_hold_actions_storage {
    uint8_t last_interrupt;
};

struct actions_tap_hold_actions_data {
    struct action tap_action;
    struct action hold_action;
    struct actions_tap_hold_actions_storage *storage;
};

struct actions_tap_dance_actions_storage {
    bool alive;
    uint8_t tap_count;
};

struct actions_tap_dance_actions_data {
    const __flash struct action *actions;
    struct actions_tap_dance_actions_storage *storage;
    uint8_t max_taps;
};

struct actions_oneshot_action_storage {
    struct irq irq;
    struct keystroke keystroke;
    uint8_t oneshot_keystroke_keyswitch;
    uint8_t oneshot_layer;
    uint8_t state;
};

struct actions_oneshot_action_data {
    struct action action;
    struct actions_oneshot_action_storage *storage;
};

struct actions_sequential_actions_data {
    const __flash struct action *actions;
    uint8_t action_count;
};

struct actions_nested_actions_data {
    const __flash struct action *actions;
    uint8_t action_count;
};

struct actions_shift_switch_actions_storage {
    bool switched;
};

struct actions_shift_switch_actions_data {
    struct action primary_action, secondary_action;
    struct actions_shift_switch_actions_storage *storage;
};

void actions_modifiers_and_scancode(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_scancode(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_sequential_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_nested_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_tap_dance_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_hold_tap_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_layers_goto(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_layers_visit(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_reset(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_none(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_tap_hold_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_leader_key(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers_and_power_management(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_power_management(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers_and_multimedia(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_multimedia(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_oneshot_action(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_shift_switch_actions(struct keystroke *keystroke, const __flash struct action *source_action);

#endif
