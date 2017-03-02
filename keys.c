#include "keys.h"
#include "leader_key.h"
#include "main.h"

static uint8_t keyboard_codes[6], keyboard_code_activations[6];
static uint8_t power_management_code, power_management_code_activations;
static uint16_t multimedia_code;
static uint8_t multimedia_code_activations;

void keys_add_scancode(uint8_t code)
{
    if (!code)
        return;
    if (leader_key_is_active()) {
        leader_key_process(code);
        return;
    }
	for (uint8_t i = 6; i--;) {
        if (keyboard_codes[i] == code) {
            keyboard_codes[i] = 0;
            SendKeyboardReport();
        }
        if (!keyboard_codes[i]) {
            keyboard_codes[i] = code;
            ++keyboard_code_activations[i];
            SendKeyboardReport();
            break;
        }
    }
}

void keys_delete_scancode(uint8_t code)
{
    if (!code) {
        return;
    }
	for (uint8_t i = 6; i--;)
        if (keyboard_codes[i] == code && !--keyboard_code_activations[i]) {
            keyboard_codes[i] = 0;
            SendKeyboardReport();
            break;
        }
}

uint8_t *keys_get_scancode(void)
{
    return keyboard_codes;
}

void keys_add_power_management(uint8_t code)
{
    if (!code)
        return;
    if (power_management_code == code) {
        power_management_code = 0;
        SendEnhancedKeyboardReport();
    }
    if (!power_management_code) {
        power_management_code = code;
        ++power_management_code_activations;
        SendEnhancedKeyboardReport();
    }
}

void keys_delete_power_management(uint8_t code)
{
    if (!code)
        return;
    if (power_management_code == code && !--power_management_code_activations) {
        power_management_code = 0;
        SendEnhancedKeyboardReport();
    }
}

uint8_t keys_get_power_management(void)
{
    return power_management_code;
}


void keys_add_multimedia(uint16_t code)
{
    if (!code)
        return;
    if (multimedia_code == code) {
        multimedia_code = 0;
        SendEnhancedKeyboardReport();
    }
    if (!multimedia_code) {
        multimedia_code = code;
        ++multimedia_code_activations;
        SendEnhancedKeyboardReport();
    }
}

void keys_delete_multimedia(uint16_t code)
{
    if (!code)
        return;
    if (multimedia_code == code && !--multimedia_code_activations) {
        multimedia_code = 0;
        SendEnhancedKeyboardReport();
    }
}

uint16_t keys_get_multimedia(void)
{
    return multimedia_code;
}
