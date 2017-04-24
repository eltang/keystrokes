#include "pins.h"

#ifdef PINA
volatile uint8_t *const __flash port_a_io_registers[3] = {
    &PINA,
    &DDRA,
    &PORTA
};
#endif

#ifdef PINB
volatile uint8_t *const __flash port_b_io_registers[3] = {
    &PINB,
    &DDRB,
    &PORTB
};
#endif

#ifdef PINC
volatile uint8_t *const __flash port_c_io_registers[3] = {
    &PINC,
    &DDRC,
    &PORTC
};
#endif

#ifdef PIND
volatile uint8_t *const __flash port_d_io_registers[3] = {
    &PIND,
    &DDRD,
    &PORTD
};
#endif

#ifdef PINE
volatile uint8_t *const __flash port_e_io_registers[3] = {
    &PINE,
    &DDRE,
    &PORTE
};
#endif

#ifdef PINF
volatile uint8_t *const __flash port_f_io_registers[3] = {
    &PINF,
    &DDRF,
    &PORTF
};
#endif

#ifdef PING
volatile uint8_t *const __flash port_g_io_registers[3] = {
    &PING,
    &DDRG,
    &PORTG
};
#endif

#ifdef PINH
volatile uint8_t *const __flash port_h_io_registers[3] = {
    &PINH,
    &DDRH,
    &PORTH
};
#endif

#ifdef PINI
volatile uint8_t *const __flash port_i_io_registers[3] = {
    &PINI
    &DDRI
    &PORTI
};
#endif

#ifdef PINJ
volatile uint8_t *const __flash port_j_io_registers[3] = {
    &PINJ,
    &DDRJ,
    &PORTJ
};
#endif

#ifdef PINK
volatile uint8_t *const __flash port_k_io_registers[3] = {
    &PINK,
    &DDRK,
    &PORTK
};
#endif

#ifdef PINL
volatile uint8_t *const __flash port_l_io_registers[3] = {
    &PINL,
    &DDRL,
    &PORTL
};
#endif

