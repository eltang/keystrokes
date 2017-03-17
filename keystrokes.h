#ifndef KEYSTROKES_H
#define KEYSTROKES_H

#include <stdint.h>
#include <stdbool.h>

struct keystroke {
    uint8_t execution_mode;
    uint8_t keyswitch;
};

struct irq {
    struct irq *next;
    const __flash struct action *action;
    uint8_t interrupts;
};

enum {
    KEYSTROKE_END,
    KEYSTROKE_BEGIN
};

enum {
    INTERRUPT_KEYSTROKE_BEGIN_EARLY = 1 << 1,
    INTERRUPT_KEYSTROKE_BEGIN_LATE = 1 << 2,
    INTERRUPT_KEYSTROKE_END_EARLY = 1 << 3,
    INTERRUPT_KEYSTROKE_END_LATE = 1 << 4,
    INTERRUPT_UNCONDITIONAL = 1 << 5
};

void keystrokes_process(struct keystroke *keystroke);
void keystrokes_task(void);
void keystrokes_add_irq(struct irq *irq);

#endif
