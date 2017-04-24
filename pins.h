#ifndef PINS_H
#define PINS_H

#include <stdint.h>
#include <avr/io.h>

#define PIN(letter, number) { PORT_IO_REGISTERS(letter), 1 << number }

#define PORT_IO_REGISTERS(letter) \
(letter == A ? port_a_io_registers : \
letter == B ? port_b_io_registers : \
letter == C ? port_c_io_registers : \
letter == D ? port_d_io_registers : \
letter == E ? port_e_io_registers : \
letter == F ? port_f_io_registers : \
letter == G ? port_f_io_registers : \
letter == H ? port_f_io_registers : \
letter == I ? port_f_io_registers : \
letter == J ? port_f_io_registers : \
letter == K ? port_f_io_registers : \
letter == L ? port_f_io_registers : 0)

enum {
    PIN,
    DDR,
    PORT
};

enum {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L
};

struct pin {
    volatile uint8_t *const __flash *registers;
    uint8_t mask;
};

extern volatile uint8_t *const __flash port_a_io_registers[3];
extern volatile uint8_t *const __flash port_b_io_registers[3];
extern volatile uint8_t *const __flash port_c_io_registers[3];
extern volatile uint8_t *const __flash port_d_io_registers[3];
extern volatile uint8_t *const __flash port_e_io_registers[3];
extern volatile uint8_t *const __flash port_f_io_registers[3];
extern volatile uint8_t *const __flash port_g_io_registers[3];
extern volatile uint8_t *const __flash port_h_io_registers[3];
extern volatile uint8_t *const __flash port_i_io_registers[3];
extern volatile uint8_t *const __flash port_j_io_registers[3];
extern volatile uint8_t *const __flash port_k_io_registers[3];
extern volatile uint8_t *const __flash port_l_io_registers[3];

#endif
