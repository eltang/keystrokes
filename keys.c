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
#include "KeyboardMouse.h"

static uint8_t keys[6];
static keyswitch_t keyswitches[6];

void keys_add(uint8_t code, keyswitch_t keyswitch)
{
    uint8_t empty_slot_index = -1;

	for (uint8_t i = 6; i--;) {
        if (keys[i] == code) {
            keys[i] = 0;
            usb_wait_until_keyboard_report_sent();
        }
        if (!keys[i]) {
            empty_slot_index = i;
            break;
        }
    }
    if (empty_slot_index == -1)
        return;
    keys[empty_slot_index] = code;
    keyswitches[empty_slot_index] = keyswitch;
    usb_wait_until_keyboard_report_sent();
}

void keys_delete(uint8_t code, keyswitch_t keyswitch)
{
	for (uint8_t i = 6; i--;)
        if (keys[i] == code)
            if (keyswitches[i].column == keyswitch.column)
                if (keyswitches[i].row == keyswitch.row) {
                    keys[i] = 0;
                    usb_wait_until_keyboard_report_sent();
                    break;
                }
}

void keys_create_report(uint8_t *buffer)
{
    memcpy(buffer, keys, 6);
}
