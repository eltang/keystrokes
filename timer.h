#ifndef TIMER_H
#define TIMER_H

#include "power.h"

void timer_init(void);
uint32_t timer_read(void);
void timer_increment(void);

#endif
