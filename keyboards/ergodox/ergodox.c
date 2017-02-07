#include "ergodox.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "i2cmaster/i2cmaster.h"
#include "layout.h"
#include "matrix.h"

#define MCP23018_ADDR 0b0100000
#define IODIRA 0x00
#define IODIRB 0x01
#define IPOLA 0x02
#define IPOLB 0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA 0x06
#define DEFVALB 0x07
#define INTCONA 0x08
#define INTCONB 0x09
#define IOCON 0x0A
#define GPPUA 0x0C
#define GPPUB 0x0D
#define INTFA 0x0E
#define INTFB 0x0F
#define INTCAPA 0x10
#define INTCAPB 0x11
#define GPIOA 0x12
#define GPIOB 0x13
#define OLATA 0x14
#define OLATB 0x15

#define LEFT_LED_1_SHIFT        7       // in MCP23018 port B
#define LEFT_LED_2_SHIFT        6       // in MCP23018 port B
#define LEFT_LED_3_SHIFT        7       // in MCP23018 port A
// The address of the slave which controls the left LED strip is 0x42.
// There are 15 leds connected to pin D7.

static uint8_t OLATA_state = 0xFF, OLATB_state, GPIOB_state = 0xFF;

void matrix_init(void)
{
    DDRB |= 1 << 3 | 1 << 2 | 1 << 1 | 1;
    PORTB |= 1 << 3 | 1 << 2 | 1 << 1 | 1;
    DDRD |= 1 << 3 | 1 << 2;
    PORTD |= 1 << 3 | 1 << 2;
    DDRC |= 1 << 6;
    PORTC |= 1 << 6;
    PORTF |= ~(1 << 3 | 1 << 2);
    i2c_start(MCP23018_ADDR << 1 | I2C_WRITE);
    i2c_write(IODIRA);
    i2c_write(0);
    i2c_write((uint8_t)~(1 << 6 | 1 << 7));
    i2c_stop();
    i2c_start(MCP23018_ADDR << 1 | I2C_WRITE);
    i2c_write(GPPUB);
    i2c_write((uint8_t)~(1 << 6 | 1 << 7));
    i2c_stop();
}

bool matrix_read_input(uint8_t input, uint8_t output)
{
    if (output > 6)
        switch (input) {
        case 0:
            return PINF & 1;
        case 1:
            return PINF & 1 << 1;
        case 2:
            return PINF & 1 << 4;
        case 3:
            return PINF & 1 << 5;
        case 4:
            return PINF & 1 << 6;
        case 5:
            return PINF & 1 << 7;
        }
    i2c_start(MCP23018_ADDR << 1 | I2C_WRITE);
    i2c_write(GPIOB);
    i2c_start(MCP23018_ADDR << 1 | I2C_READ);
    GPIOB_state = i2c_readNak();
    i2c_stop();
    return GPIOB_state & 1 << input;
}

void matrix_activate_output(uint8_t output)
{
    switch (output) {
    case 7:
        PORTB &= ~1;
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
        PORTD &= ~(1 << 2);
        break;
    case 12:
        PORTD &= ~(1 << 3);
        break;
    case 13:
        PORTC &= ~(1 << 6);
        break;
    default:
        i2c_start(MCP23018_ADDR << 1 | I2C_WRITE);
        i2c_write(OLATA);
        i2c_write(OLATA_state &= ~(1 << output));
        i2c_stop();
        break;
    }
}

void matrix_deactivate_output(uint8_t output)
{
    switch (output) {
    case 7 ... 10:
        PORTB |= 1 << 3 | 1 << 2 | 1 << 1 | 1;
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
        i2c_start(MCP23018_ADDR << 1 | I2C_WRITE);
        i2c_write(OLATA);
        i2c_write(OLATA_state);
        i2c_stop();
        break;
    }
}
