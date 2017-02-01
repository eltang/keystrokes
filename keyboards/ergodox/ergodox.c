#include "ergodox.h"

// The address of the slave which controls the left LED strip is 0x42.
// There are 15 leds connected to pin D7.

static uint8_t OLATA_state, OLATB_state, GPIOB_state, transmission[4];

static void matrix_init_mcp23018(void) {
    transmission[0] = MCP23018_ADDR << TWI_ADR_BITS | FALSE << TWI_READ_BIT;
    transmission[1] = IODIRA;
    transmission[2] = 0;
    transmission[3] = (uint8_t)~(1 << 6 | 1 << 7);
    TWI_Start_Transceiver_With_Data(transmission, 4);
    transmission[1] = GPPUA;
    TWI_Start_Transceiver_With_Data(transmission, 4);
}

static void matrix_init_teensy(void)
{
    DDRB |= 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0;
    PORTB |= 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0;
    DDRD |= 1 << 3 | 1 << 2;
    PORTD |= 1 << 3 | 1 << 2;
    DDRC |= 1 << 6;
    PORTC |= 1 << 6;
    DDRF &= 1 << 3 | 1 << 2;
    PORTF |= ~(1 << 3 | 1 << 2);
}

static bool matrix_read_teensy_input(uint8_t input)
{
    bool ret = 0;

    switch (input) {
    case 0:
        ret = ~PINF & 1 << 0;
    case 1:
        ret = ~PINF & 1 << 1;
    case 2:
        ret = ~PINF & 1 << 4;
    case 3:
        ret = ~PINF & 1 << 5;
    case 4:
        ret = ~PINF & 1 << 6;
    case 5:
        ret = ~PINF & 1 << 7;
    }
    return ret;
}

bool matrix_read_input(uint8_t input)
{
    return matrix_read_teensy_input(input) | (~GPIOB_state & 1 << input);
}

void matrix_activate_output(uint8_t output)
{
    switch (output) {
    case 7:
        PORTB &= ~(1 << 0);
        break;
    case 8:
        PORTB &= ~(1 << 1);
        break;
    case 9:
        PORTB &= ~(1 << 2);
        break;
    case 10:
        PORTB &= ~(1 << 3);
        break;
    case 11:
        PORTD &= ~(1 << 3);
        break;
    case 12:
        PORTD &= ~(1 << 3);
        break;
    case 13:
        PORTC &= ~(1 << 6);
        break;
    default:
        transmission[0] = MCP23018_ADDR << TWI_ADR_BITS | FALSE << TWI_READ_BIT;
        transmission[1] = OLATA;
        transmission[2] = OLATA_state &= 1 << output;
        TWI_Start_Transceiver_With_Data(transmission, 3);
        transmission[1] = GPIOB;
        TWI_Start_Transceiver_With_Data(transmission, 2);
        transmission[0] = MCP23018_ADDR << TWI_ADR_BITS | TRUE << TWI_READ_BIT;
        TWI_Start_Transceiver_With_Data(transmission, 1);
        TWI_Get_Data_From_Transceiver(&GPIOB_state, 1);
        GPIOB_state = ~GPIOB_state;
        break;
    }
}

void matrix_deactivate_output(uint8_t output)
{
    switch (output) {
    case 7 ... 10:
        PORTB |= 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0;
        break;
    case 11 ... 12:
        PORTD |= 1 << 3 | 1 << 2;
        break;
    case 13:
        PORTC |= 1 << 6;
        break;
    default:
        OLATA_state |= ~(1 << 7);
        if (output)
            break;
        transmission[0] = MCP23018_ADDR << TWI_ADR_BITS | FALSE << TWI_READ_BIT;
        transmission[1] = OLATA;
        transmission[2] = OLATA_state;
        TWI_Start_Transceiver_With_Data(transmission, 3);
        break;
    }
}

void matrix_init(void)
{
    matrix_init_teensy();
    matrix_init_mcp23018();
}
