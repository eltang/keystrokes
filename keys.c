#include "keys.h"
#include "leader_key.h"
#include "main.h"

static uint8_t keyboard_codes[6], keyboard_code_activations[6];
static uint8_t generic_desktop_code, generic_desktop_code_activations;
static uint16_t consumer_code;
static uint8_t consumer_code_activations;
static uint8_t extended_keyboard_report_id;

void keys_add_scancode(uint8_t code)
{
    uint8_t empty_slot_index;

    if (!code)
        return;
    if (leader_key_is_active()) {
        leader_key_process(code);
        return;
    }
    empty_slot_index = -1;
	for (uint8_t i = 6; i--;) {
        if (keyboard_codes[i] == code) {
            keyboard_codes[i] = 0;
            SendKeyboardReport();
        }
        if (!keyboard_codes[i]) {
            empty_slot_index = i;
            break;
        }
    }
    if (empty_slot_index == -1)
        return;
    keyboard_codes[empty_slot_index] = code;
    ++keyboard_code_activations[empty_slot_index];
    SendKeyboardReport();
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

void keys_add_generic_desktop(uint8_t code)
{
    if (!code)
        return;
    if (generic_desktop_code == code) {
        generic_desktop_code = 0;
        extended_keyboard_report_id = HID_REPORTID_GenericDesktopReport;
        SendEnhancedKeyboardReport();
    }
    if (!generic_desktop_code) {
        generic_desktop_code = code;
        ++generic_desktop_code_activations;
        extended_keyboard_report_id = HID_REPORTID_GenericDesktopReport;
        SendEnhancedKeyboardReport();
    }
}

void keys_delete_generic_desktop(uint8_t code)
{
    if (!code)
        return;
    if (generic_desktop_code == code)
        if (!--generic_desktop_code_activations) {
            generic_desktop_code = 0;
            extended_keyboard_report_id = HID_REPORTID_GenericDesktopReport;
            SendEnhancedKeyboardReport();
        }
}

uint8_t keys_get_generic_desktop(void)
{
    return generic_desktop_code;
}


void keys_add_consumer(uint16_t code)
{
    if (!code)
        return;
    if (consumer_code == code) {
        consumer_code = 0;
        extended_keyboard_report_id = HID_REPORTID_ConsumerReport;
        SendEnhancedKeyboardReport();
    }
    if (!consumer_code) {
        consumer_code = code;
        ++consumer_code_activations;
        extended_keyboard_report_id = HID_REPORTID_ConsumerReport;
        SendEnhancedKeyboardReport();
    }
}

void keys_delete_consumer(uint16_t code)
{
    if (!code)
        return;
    if (consumer_code == code)
        if (!--consumer_code_activations) {
            consumer_code = 0;
            extended_keyboard_report_id = HID_REPORTID_ConsumerReport;
            SendEnhancedKeyboardReport();
        }
}

uint16_t keys_get_consumer(void)
{
    return consumer_code;
}

uint8_t keys_get_extended_keyboard_report_id(void)
{
    return extended_keyboard_report_id;
}
