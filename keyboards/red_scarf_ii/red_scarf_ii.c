#include "matrix.h"

void matrix_init(void)
{
    DDRB |= 1 << 2 | 1 << 1 | 1;
    PORTB |= 1 << 2 | 1 << 1 | 1;
    PORTF |= 1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 1 | 1 << 0;
    PORTD |= 1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1 | 1;
    PORTB |= 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3;
}

bool matrix_read_input(uint8_t input, uint8_t output)
{
    switch (input) {
    case 0:
        return PINF & 1 << 4;
    case 1:
        return PINF & 1 << 1;
    case 2:
        return PINF & 1 << 0;
    case 3:
        return PINB & 1 << 3;
    case 4:
        return PIND & 1 << 0;
    case 5:
        return PIND & 1 << 1;
    case 6:
        return PIND & 1 << 4;
    case 7:
        return PIND & 1 << 5;
    case 8:
        return PIND & 1 << 6;
    case 9:
        return PIND & 1 << 7;
    case 10:
        return PINF & 1 << 7;
    case 11:
        return PINF & 1 << 6;
    case 12:
        return PIND & 1 << 2;
    case 13:
        return PIND & 1 << 3;
    case 14:
        return PINB & 1 << 6;
    case 15:
        return PINB & 1 << 5;
    case 16:
        return PINB & 1 << 4;
    default:
        return PINF & 1 << 5;
    }
}

void matrix_activate_output(uint8_t output)
{
    uint8_t temp = 0xFF;

    if (!(output & 1 << 0))
        temp &= ~(1 << 2);
    if (!(output & 1 << 1))
        temp &= ~(1 << 1);
    if (!(output & 1 << 2))
        temp &= ~1;
    PORTB &= temp;
}

void matrix_deactivate_output(uint8_t output)
{
    PORTB |= 1 << 2 | 1 << 1 | 1;
}
