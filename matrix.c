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

typedef struct {
#if KEYSWITCH_BOUNCE_TIME
    uint8_t timestamp;
#endif
    uint8_t state;
} keyswitch_state_t;

enum {
    KEYSWITCH_IS_CLOSED = 1,
    KEYSWITCH_IS_BOUNCING = 1 << 1
};

static keyswitch_state_t keyswitch_states[ROWS][COLUMNS];
static const __flash pin_t output_pins[OUTPUTS] = OUTPUT_PINS;
static const __flash pin_t input_pins[INPUTS] = INPUT_PINS;

__attribute__((weak))
void matrix_init_output(uint8_t output)
{
    pin_t pin = output_pins[output];

    PIN_DDR(pin) |= PIN_MASK(pin);
    PIN_PORT(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
void matrix_init_input(uint8_t input)
{
    pin_t pin = input_pins[input];

    PIN_PORT(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
void matrix_activate_output(uint8_t output)
{
    pin_t pin = output_pins[output];

    PIN_PORT(pin) &= ~PIN_MASK(pin);
}

__attribute__((weak))
void matrix_deactivate_output(uint8_t output, bool keystroke_detected)
{
    pin_t pin = output_pins[output];

    PIN_PORT(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
bool matrix_read_input(uint8_t input, uint8_t output)
{
    pin_t pin = input_pins[input];

    return PIN_PIN(pin) & PIN_MASK(pin);
}

__attribute__((weak))
void matrix_init(void)
{
    for (uint8_t i = OUTPUTS; i--;)
        matrix_init_output(i);
    for (uint8_t i = INPUTS; i--;)
        matrix_init_input(i);
}

keystroke_t *matrix_scan(void)
{
    static keystroke_t keystroke;
    keyswitch_state_t *keyswitch_state;
    bool keyswitch_is_open;
    uint8_t timer_count = timer_read();

    for (uint8_t i = OUTPUTS; i--;) {
        matrix_activate_output(i);
        for (uint8_t j = INPUTS; j--;) {
#ifdef BACKWARDS_DIODES
            keyswitch_state = &keyswitch_states[j][i];
#else
            keyswitch_state = &keyswitch_states[i][j];
#endif
#if KEYSWITCH_BOUNCE_TIME
            if (keyswitch_state->state & KEYSWITCH_IS_BOUNCING) {
                if ((uint8_t)(timer_count - keyswitch_state->timestamp) > KEYSWITCH_BOUNCE_TIME)
                    keyswitch_state->state &= ~KEYSWITCH_IS_BOUNCING;
                else
                    continue;
            }
#endif
            keyswitch_is_open = matrix_read_input(j, i);
            if (!(keyswitch_state->state & KEYSWITCH_IS_CLOSED) == keyswitch_is_open)
                continue;
            matrix_deactivate_output(i, 1);
            keyswitch_state->state = !keyswitch_is_open;
#if KEYSWITCH_BOUNCE_TIME
            keyswitch_state->state |= KEYSWITCH_IS_BOUNCING;
            keyswitch_state->timestamp = timer_count;
#endif
#ifdef BACKWARDS_DIODES
            keystroke.keyswitch = (keyswitch_t){ j, i };
#else
            keystroke.keyswitch = (keyswitch_t){ i, j };
#endif
            keystroke.stage = keyswitch_is_open;
            return &keystroke;
        }
        matrix_deactivate_output(i, 0);
    }
    return 0;
}
