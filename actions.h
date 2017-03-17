#ifndef ACTIONS_H
#define ACTIONS_H

#include "keystrokes.h"

struct action {
    void (*fcn)(struct keystroke *, const __flash struct action *);
    const __flash void *data;
};

struct actions_hold_tap_data {
    struct action hold_action;
    struct action tap_action;
};

struct actions_tap_hold_storage {
    uint8_t last_interrupt;
};

struct actions_tap_hold_data {
    struct action tap_action;
    struct action hold_action;
    struct actions_tap_hold_storage *storage;
};

struct actions_tap_dance_storage {
    bool alive;
    uint8_t tap_count;
};

struct actions_tap_dance_data {
    const __flash struct action *actions;
    struct actions_tap_dance_storage *storage;
    uint8_t action_count;
};

struct actions_oneshot_storage {
    struct irq irq;
    struct keystroke keystroke;
    uint8_t oneshot_keystroke_keyswitch;
    uint8_t oneshot_layer;
    uint8_t state;
};

struct actions_oneshot_data {
    struct action action;
    struct actions_oneshot_storage *storage;
};

struct actions_multiple_actions_data {
    const __flash struct action *actions;
    uint8_t action_count;
};

void actions_modifiers_and_scancode(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_scancode(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_multiple_actions(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_start_action(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_finish_action(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_tap_dance(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_hold_tap(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_layers_goto(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_layers_visit(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_reset(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_none(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_tap_hold(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_leader_key(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers_and_power_management(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_power_management(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_modifiers_and_multimedia(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_multimedia(struct keystroke *keystroke, const __flash struct action *source_action);
void actions_oneshot(struct keystroke *keystroke, const __flash struct action *source_action);

#endif
