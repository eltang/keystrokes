#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

#include "pins.h"

enum {
    SHOW_NUM_LOCK_STATE,
    SHOW_CAPS_LOCK_STATE,
    SHOW_SCROLL_LOCK_STATE,
    SHOW_COMPOSE_STATE,
    SHOW_KANA_STATE,
    SHOW_LAYER_BIT_0,
    SHOW_LAYER_BIT_1,
    SHOW_LAYER_BIT_2,
    SHOW_LAYER_BIT_3,
    SHOW_LAYER_BIT_4,
    SHOW_LAYER_BIT_5,
    SHOW_LAYER_BIT_6,
    SHOW_LAYER_BIT_7
};

struct led_config {
    struct pin pin;
    uint8_t task;
};

void leds_init(void);
void leds_process_layer_change(uint8_t layer);
void leds_process_led_report_change(uint8_t led_report);

#endif
