#include "matrix.h"
#include "timer.h"
#include "pins.h"

#ifdef BACKWARDS_DIODES

#define INPUTS ROWS
#define OUTPUTS COLUMNS
#define INPUT_PINS ROW_PINS
#define OUTPUT_PINS COLUMN_PINS

#else

#define INPUTS COLUMNS
#define OUTPUTS ROWS
#define INPUT_PINS COLUMN_PINS
#define OUTPUT_PINS ROW_PINS

#endif

struct keyswitch_state {
    uint8_t timestamp;
    uint8_t state;
};

enum {
    KEYSWITCH_IS_CLOSED = 1,
    KEYSWITCH_WAS_CLOSED = 1 << 1,
    KEYSWITCH_HAS_BEEN_CLOSED = 1 << 2
};

static struct keyswitch_state keyswitch_states[OUTPUTS][INPUTS];
static const __flash struct pin output_pins[OUTPUTS] = OUTPUT_PINS;
static const __flash struct pin input_pins[INPUTS] = INPUT_PINS;

__attribute__((weak))
void matrix_init_output(uint8_t output)
{
}

__attribute__((weak))
void matrix_init_input(uint8_t input)
{
    struct pin pin = input_pins[input];

    pin.port->port |= pin.mask;
}

__attribute__((weak))
void matrix_activate_output(uint8_t output)
{
    struct pin pin = output_pins[output];

    pin.port->ddr |= pin.mask;
}

__attribute__((weak))
void matrix_deactivate_output(uint8_t output)
{
    struct pin pin = output_pins[output];

    pin.port->ddr &= ~pin.mask;
}

__attribute__((weak))
bool matrix_read_input(uint8_t input, uint8_t output)
{
    struct pin pin = input_pins[input];

    return pin.port->pin & pin.mask;
}

__attribute__((weak))
void matrix_init(void)
{
    for (uint8_t i = OUTPUTS; i--;)
        matrix_init_output(i);
    for (uint8_t i = INPUTS; i--;)
        matrix_init_input(i);
}

void matrix_scan(void)
{
    struct keystroke keystroke;
    struct keyswitch_state *keyswitch_state;

    for (uint8_t i = OUTPUTS; i--;) {
        matrix_activate_output(i);
        for (uint8_t j = INPUTS; j--;)
            keyswitch_states[i][j].state |= !matrix_read_input(j, i);
        matrix_deactivate_output(i);
    }
    for (uint8_t i = OUTPUTS; i--;)
        for (uint8_t j = INPUTS; j--;) {
            keyswitch_state = &keyswitch_states[i][j];
            switch (keyswitch_state->state & (KEYSWITCH_WAS_CLOSED | KEYSWITCH_IS_CLOSED)) {
            case KEYSWITCH_IS_CLOSED:
            case KEYSWITCH_WAS_CLOSED:
                keyswitch_state->state ^= KEYSWITCH_WAS_CLOSED;
                keyswitch_state->timestamp = timer_read();
                break;
            default:
                switch (keyswitch_state->state & (KEYSWITCH_HAS_BEEN_CLOSED | KEYSWITCH_WAS_CLOSED)) {
                case KEYSWITCH_WAS_CLOSED:
                case KEYSWITCH_HAS_BEEN_CLOSED:
                    if ((uint8_t)(timer_read() - keyswitch_state->timestamp) <= KEYSWITCH_BOUNCE_TIME)
                        break;
                    keyswitch_state->state ^= KEYSWITCH_HAS_BEEN_CLOSED;
#ifdef BACKWARDS_DIODES
                    keystroke.keyswitch = j * COLUMNS + i;
#else
                    keystroke.keyswitch = i * COLUMNS + j;
#endif
                    keystroke.execution_mode = !!(keyswitch_state->state & KEYSWITCH_HAS_BEEN_CLOSED);
                    keystrokes_process(&keystroke);
                    break;
                }
                break;
            }
            keyswitch_state->state &= ~KEYSWITCH_IS_CLOSED;
        }
}
