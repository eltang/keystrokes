#include "ergodox.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "twi.h"
#include "layout.h"
#include "matrix.h"

#define MCP23018_ADDR 0b0100000
#define IODIRA_ADDR 0x00
#define IODIRB_ADDR 0x01
#define IPOLA_ADDR 0x02
#define IPOLB_ADDR 0x03
#define GPINTENA_ADDR 0x04
#define GPINTENB_ADDR 0x05
#define DEFVALA_ADDR 0x06
#define DEFVALB_ADDR 0x07
#define INTCONA_ADDR 0x08
#define INTCONB_ADDR 0x09
#define IOCON_ADDR 0x0A
#define GPPUA_ADDR 0x0C
#define GPPUB_ADDR 0x0D
#define INTFA_ADDR 0x0E
#define INTFB_ADDR 0x0F
#define INTCAPA_ADDR 0x10
#define INTCAPB_ADDR 0x11
#define GPIOA_ADDR 0x12
#define GPIOB_ADDR 0x13
#define OLATA_ADDR 0x14
#define OLATB_ADDR 0x15

#define LEFT_LED_1 7 // MCP23018 Port B
#define LEFT_LED_2 6 // MCP23018 Port B
#define LEFT_LED_3 7 // MCP23018 Port A
// The address of the slave which controls the left LED strip is 0x42.
// There are 15 leds connected to pin D7.

static uint8_t GPIOB_state = 0xFF;

void matrix_init(void)
{
    uint8_t transmission[3];

    PORTF |= ~(1 << 3 | 1 << 2);
    transmission[0] = IODIRA_ADDR;
    transmission[1] = (uint8_t)~(1 << 7);
    transmission[2] = (uint8_t)~(1 << 6 | 1 << 7);
    i2cMasterTransmit(MCP23018_ADDR, transmission, 3, 0, 0);
    while (TWCR & 1 << TWIE)
        ;
    transmission[0] = GPPUB_ADDR;
    transmission[1] = (uint8_t)~(1 << 6 | 1 << 7);
    i2cMasterTransmit(MCP23018_ADDR, transmission, 2, 0, 0);
    while (TWCR & 1 << TWIE)
        ;
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
    return GPIOB_state & 1 << input;
}

void matrix_activate_output(uint8_t output)
{
    uint8_t transmission[2];

    switch (output) {
    case 7:
        DDRB |= 1;
        break;
    case 8:
        DDRB |= 1 << 1;
        break;
    case 9:
        DDRB |= 1 << 2;
        break;
    case 10:
        DDRB |= 1 << 3;
        break;
    case 11:
        DDRD |= 1 << 2;
        break;
    case 12:
        DDRD |= 1 << 3;
        break;
    case 13:
        DDRC |= 1 << 6;
        break;
    default:
        transmission[0] = IODIRA_ADDR;
        transmission[1] = ~(1 << 7 | 1 << output);
        i2cMasterTransmit(MCP23018_ADDR, transmission, 2, 0, 0);
        while (TWCR & 1 << TWIE)
            ;
        transmission[0] = GPIOB_ADDR;
        i2cMasterTransmit(MCP23018_ADDR, transmission, 1, &GPIOB_state, 1);
        while (TWCR & 1 << TWIE)
            ;
        break;
    }
}

void matrix_deactivate_output(uint8_t output)
{
    uint8_t transmission[2];

    switch (output) {
    case 0:
        transmission[0] = IODIRA_ADDR;
        transmission[1] = (uint8_t)~(1 << 7);
        i2cMasterTransmit(MCP23018_ADDR, transmission, 2, 0, 0);
        while (TWCR & 1 << TWIE)
            ;
        break;
    case 7 ... 10:
        DDRB &= ~(1 << 3 | 1 << 2 | 1 << 1 | 1);
        break;
    case 11 ... 12:
        DDRD &= ~(1 << 3 | 1 << 2);
        break;
    case 13:
        DDRC &= ~(1 << 6);
        break;
    }
}
