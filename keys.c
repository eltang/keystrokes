/*
 * Easy AVR USB Keyboard Firmware
 * Copyright (C) 2013-2016 David Howland
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keys.h"
#include "leader_key.h"
#include "KeyboardMouse.h"

static uint8_t keys[6];
static uint8_t key_activations[6];

void keys_add(uint8_t code)
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
        if (keys[i] == code) {
            usb_wait_until_previous_keyboard_report_sent();
            keys[i] = 0;
        }
        if (!keys[i]) {
            empty_slot_index = i;
            break;
        }
    }
    if (empty_slot_index == -1)
        return;
    usb_wait_until_previous_keyboard_report_sent();
    keys[empty_slot_index] = code;
    ++key_activations[empty_slot_index];
}

void keys_delete(uint8_t code)
{
    if (!code) {
        return;
    }
	for (uint8_t i = 6; i--;)
        if (keys[i] == code && !--key_activations[i]) {
            usb_wait_until_previous_keyboard_report_sent();
            keys[i] = 0;
            break;
        }
}

uint8_t *keys_get(void)
{
    return keys;
}
