#ifndef ACTIONS_H
#define ACTIONS_H

#include "matrix.h"

typedef struct {
    void (*fcn)(keystroke_t *, const __flash void *);
    const __flash void *arg;
} action_t;

void actions_modifiers_and_scancode(keystroke_t *keystroke, const __flash void *arg);
void actions_modifiers(keystroke_t *keystroke, const __flash void *arg);
void actions_scancode(keystroke_t *keystroke, const __flash void *arg);
void actions_multiple_actions(keystroke_t *keystroke, const __flash void *arg);
void actions_tap_dance(keystroke_t *keystroke, const __flash void *arg);
void actions_hold_tap(keystroke_t *keystroke, const __flash void *arg);
void actions_layers_goto(keystroke_t *keystroke, const __flash void *arg);
void actions_layers_visit(keystroke_t *keystroke, const __flash void *arg);
void actions_reset(keystroke_t *keystroke, const __flash void *arg);

#endif
