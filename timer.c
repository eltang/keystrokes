#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "timer.h"

static volatile uint32_t count;

void timer_init(void)
{
    TCCR0A |= 1 << WGM01;
    TCCR0B |= 1 << CS01 | 1 << CS00;
    TIMSK0 |= 1 << OCIE0A;
    OCR0A = 249;
}

uint32_t timer_read(void)
{
    uint32_t ret;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ret = count;
    }
    return ret;
}

ISR(TIMER0_COMPA_vect)
{
    ++count;
}
