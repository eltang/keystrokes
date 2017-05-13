#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "timer.h"

static volatile uint32_t count;

uint32_t timer_read(void)
{
    uint32_t ret;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ret = count;
    }
    return ret;
}

void timer_increment(void)
{
    ++count;
}
