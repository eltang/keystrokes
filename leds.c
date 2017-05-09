#include "leds.h"

#define LED_COUNT (sizeof(led_config) / sizeof(led_config[0]))

static const __flash struct led_config led_config[] = LED_CONFIG;

static void leds_update_led(const __flash struct pin *pin, bool state)
{
    if (state)
        *pins_addr_to_reg(pin->addr, PORT) |= pin->mask;
    else
        *pins_addr_to_reg(pin->addr, PORT) &= ~pin->mask;
}

void leds_init(void)
{
    struct pin pin;

    for (uint8_t i = LED_COUNT; i--;) {
        pin = led_config[i].pin;
        *pins_addr_to_reg(pin.addr, DDR) |= pin.mask;
    }
}

void leds_process_layer_change(uint8_t layer)
{
    bool state;

    for (uint8_t i = LED_COUNT; i--;) {
        if (led_config[i].task < SHOW_LAYER_BIT_0)
            continue;
        state = layer & 1 << (led_config[i].task - SHOW_LAYER_BIT_0);
        leds_update_led(&led_config[i].pin, state);
    }
}

void leds_process_led_report_change(uint8_t led_report)
{
    bool state;

    for (uint8_t i = LED_COUNT; i--;) {
        if (led_config[i].task > SHOW_KANA_STATE)
            continue;
        state = led_report & 1 << (led_config[i].task - SHOW_NUM_LOCK_STATE);
        leds_update_led(&led_config[i].pin, state);
    }
}
