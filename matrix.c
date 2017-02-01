#include "matrix.h"

#define INPUTS COLUMNS
#define OUTPUTS ROWS
#define INPUT_PINS COLUMN_PINS
#define OUTPUT_PINS ROW_PINS


static const __flash pin_t output_pins[OUTPUTS] = OUTPUT_PINS;
static const __flash pin_t input_pins[INPUTS] = INPUT_PINS;
volatile uint8_t matrix_keyswitch_states[ROWS][COLUMNS] = { 0 };

__attribute__((weak))
void matrix_init_output(uint8_t output)
{
    pin_t pin = output_pins[output];

    PIN_DDRx(pin) |= PIN_MASK(pin);
    PIN_PORTx(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
void matrix_init_input(uint8_t input)
{
    pin_t pin = input_pins[input];

    PIN_DDRx(pin) &= ~PIN_MASK(pin);
    PIN_PORTx(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
void matrix_activate_output(uint8_t output)
{
    pin_t pin = output_pins[output];

    PIN_PORTx(pin) &= ~PIN_MASK(pin);
}

__attribute__((weak))
void matrix_deactivate_output(uint8_t output)
{
    pin_t pin = output_pins[output];

    PIN_PORTx(pin) |= PIN_MASK(pin);
}

__attribute__((weak))
bool matrix_read_input(uint8_t input)
{
    pin_t pin = input_pins[input];

    return PIN_PINx(pin) & PIN_MASK(pin);
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
    uint8_t keyswitch_state;
    bool keyswitch_is_open;
    uint8_t new_keyswitch_state;

    for (uint8_t i = OUTPUTS; i--;) {
        matrix_activate_output(i);
        for (uint8_t j = INPUTS; j--;) {
            keyswitch_state = matrix_keyswitch_states[i][j];
            keyswitch_is_open = matrix_read_input(j);
            if (!(keyswitch_state & 0x80) == keyswitch_is_open || keyswitch_state & 0x7F)
                continue;
            matrix_deactivate_output(i);
            if (KEYSWITCH_BOUNCE_TIME)
                new_keyswitch_state = KEYSWITCH_BOUNCE_TIME + 1;
            if (!keyswitch_is_open)
                new_keyswitch_state |= 0x80;
            matrix_keyswitch_states[i][j] = new_keyswitch_state;
            keystroke.keyswitch = (keyswitch_t){ i, j };
            keystroke.stage = keyswitch_is_open;
            return &keystroke;
        }
        matrix_deactivate_output(i);
    }
    return 0;
}
