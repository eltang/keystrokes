#ifndef TIMER_H
#define TIMER_H

#include "power.h"

void timer_init(void);
uint32_t timer_read(void);
void timer_increment(void);
__attribute__((always_inline))
static inline void timer_disable(void);
__attribute__((always_inline))
static inline void timer_enable(void);

static inline void timer_disable(void)
{
    PRR0 = PRR0_VALUE | 1 << PRTIM0;
}

static inline void timer_enable(void)
{
    PRR0 = PRR0_VALUE & ~(1 << PRTIM0);
}

#endif
