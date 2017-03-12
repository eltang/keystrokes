#ifndef KEYSTROKES_H
#define KEYSTROKES_H

#include <stdint.h>
#include <stdbool.h>

struct keystroke {
    uint8_t execution_mode;
    uint8_t layer;
    uint8_t keyswitch;
};

struct irq {
    struct irq *next;
    const __flash struct action *action;
    struct keystroke keystroke;
    uint8_t interrupts;
};

enum {
    KEYSTROKE_FINISH,
    KEYSTROKE_START
};

enum {
    INTERRUPT_MANUAL_KEYSTROKE_START = 1 << 1,
    INTERRUPT_MANUAL_KEYSTROKE_FINISH = 1 << 2,
    INTERRUPT_UNCONDITIONAL = 1 << 3
};

void keystrokes_process(struct keystroke *keystroke);
void keystrokes_task(void);
void keystrokes_add_irq(struct irq *irq);

#endif
