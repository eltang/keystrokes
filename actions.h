#ifndef ACTIONS_H
#define ACTIONS_H

#include "matrix.h"

typedef struct {
    void (*fcn)(keystroke_t, const __flash void *);
    const __flash void *arg;
} action_t;

void actions_modifier_and_scancode_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_modifiers_and_scancode(keystroke_t keystroke, uint8_t key, uint8_t modifiers);
void actions_modifiers_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_modifiers(uint8_t modifiers, keystroke_t keystroke);
void actions_scancode_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_scancode(keystroke_t keystroke, uint8_t key);
void actions_multiple_actions(keystroke_t keystroke, const __flash void *arg);
void actions_tap_dance(keystroke_t keystroke, const __flash void *arg);
void actions_hold_tap(keystroke_t keystroke, const __flash void *arg);
void actions_layer_visit_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_layer_toggle_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_layer_goto_wrapper(keystroke_t keystroke, const __flash void *arg);
void actions_reset(keystroke_t keystroke, const __flash void *arg);


#endif
