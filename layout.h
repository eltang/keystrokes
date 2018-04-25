#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>
#include "matrix.h"
#include "actions.h"
#include <LUFA/Drivers/USB/USB.h>
#include "leader_key.h"

 // eliminate the use of keycodes for modifiers; they are utterly useless
 // make them into bitfields only
#ifndef __FLASH
#error "A newer compiler is needed."
#endif

enum {
    KEY_OPAQUE,
    KEY_TRANSPARENT
};

extern const __flash struct action layout[][ROWS * COLUMNS];
__attribute__((weak))
extern const __flash struct leader_key_dictionary_entry leader_key_dictionary[];
__attribute__((weak))
extern const __flash uint8_t leader_key_dictionary_length;

#define US_A HID_KEYBOARD_SC_A
#define US_B HID_KEYBOARD_SC_B
#define US_C HID_KEYBOARD_SC_C
#define US_D HID_KEYBOARD_SC_D
#define US_E HID_KEYBOARD_SC_E
#define US_F HID_KEYBOARD_SC_F
#define US_G HID_KEYBOARD_SC_G
#define US_H HID_KEYBOARD_SC_H
#define US_I HID_KEYBOARD_SC_I
#define US_J HID_KEYBOARD_SC_J
#define US_K HID_KEYBOARD_SC_K
#define US_L HID_KEYBOARD_SC_L
#define US_M HID_KEYBOARD_SC_M
#define US_N HID_KEYBOARD_SC_N
#define US_O HID_KEYBOARD_SC_O
#define US_P HID_KEYBOARD_SC_P
#define US_Q HID_KEYBOARD_SC_Q
#define US_R HID_KEYBOARD_SC_R
#define US_S HID_KEYBOARD_SC_S
#define US_T HID_KEYBOARD_SC_T
#define US_U HID_KEYBOARD_SC_U
#define US_V HID_KEYBOARD_SC_V
#define US_W HID_KEYBOARD_SC_W
#define US_X HID_KEYBOARD_SC_X
#define US_Y HID_KEYBOARD_SC_Y
#define US_Z HID_KEYBOARD_SC_Z
#define US_1 HID_KEYBOARD_SC_1_AND_EXCLAMATION
#define US_2 HID_KEYBOARD_SC_2_AND_AT
#define US_3 HID_KEYBOARD_SC_3_AND_HASHMARK
#define US_4 HID_KEYBOARD_SC_4_AND_DOLLAR
#define US_5 HID_KEYBOARD_SC_5_AND_PERCENTAGE
#define US_6 HID_KEYBOARD_SC_6_AND_CARET
#define US_7 HID_KEYBOARD_SC_7_AND_AMPERSAND
#define US_8 HID_KEYBOARD_SC_8_AND_ASTERISK
#define US_9 HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS
#define US_0 HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS
#define ENTER HID_KEYBOARD_SC_ENTER
#define ESC HID_KEYBOARD_SC_ESCAPE
#define BKSP HID_KEYBOARD_SC_BACKSPACE
#define TAB HID_KEYBOARD_SC_TAB
#define SPACE HID_KEYBOARD_SC_SPACE
#define US_HYPHEN HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE
#define US_EQUAL HID_KEYBOARD_SC_EQUAL_AND_PLUS
#define US_OPENING_BRACKET HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE
#define US_CLOSING_BRACKET HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE
#define US_BACKSLASH HID_KEYBOARD_SC_BACKSLASH_AND_PIPE
#define US_NON_US_HASHMARK_AND_TILDE HID_KEYBOARD_SC_NON_US_HASHMARK_AND_TILDE
#define US_SEMICOLON HID_KEYBOARD_SC_SEMICOLON_AND_COLON
#define US_APOSTROPHE HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE
#define US_GRAVE HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE
#define US_COMMA HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN
#define US_PERIOD HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN
#define US_SLASH HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK
#define CAPS_LOCK HID_KEYBOARD_SC_CAPS_LOCK
#define F1 HID_KEYBOARD_SC_F1
#define F2 HID_KEYBOARD_SC_F2
#define F3 HID_KEYBOARD_SC_F3
#define F4 HID_KEYBOARD_SC_F4
#define F5 HID_KEYBOARD_SC_F5
#define F6 HID_KEYBOARD_SC_F6
#define F7 HID_KEYBOARD_SC_F7
#define F8 HID_KEYBOARD_SC_F8
#define F9 HID_KEYBOARD_SC_F9
#define F10 HID_KEYBOARD_SC_F10
#define F11 HID_KEYBOARD_SC_F11
#define F12 HID_KEYBOARD_SC_F12
#define PRINT_SCREEN HID_KEYBOARD_SC_PRINT_SCREEN
#define SCROLL_LOCK HID_KEYBOARD_SC_SCROLL_LOCK
#define PAUSE HID_KEYBOARD_SC_PAUSE
#define INSERT HID_KEYBOARD_SC_INSERT
#define HOME HID_KEYBOARD_SC_HOME
#define PG_UP HID_KEYBOARD_SC_PAGE_UP
#define DELETE HID_KEYBOARD_SC_DELETE
#define END HID_KEYBOARD_SC_END
#define PG_DN HID_KEYBOARD_SC_PAGE_DOWN
#define RIGHT HID_KEYBOARD_SC_RIGHT_ARROW
#define LEFT HID_KEYBOARD_SC_LEFT_ARROW
#define DOWN HID_KEYBOARD_SC_DOWN_ARROW
#define UP HID_KEYBOARD_SC_UP_ARROW
#define NUM_LOCK HID_KEYBOARD_SC_NUM_LOCK
#define KP_SLASH HID_KEYBOARD_SC_KEYPAD_SLASH
#define KP_ASTERISK HID_KEYBOARD_SC_KEYPAD_ASTERISK
#define KP_MINUS HID_KEYBOARD_SC_KEYPAD_MINUS
#define KP_PLUS HID_KEYBOARD_SC_KEYPAD_PLUS
#define KP_ENTER HID_KEYBOARD_SC_KEYPAD_ENTER
#define KP_1 HID_KEYBOARD_SC_KEYPAD_1_AND_END
#define KP_2 HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW
#define KP_3 HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN
#define KP_4 HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW
#define KP_5 HID_KEYBOARD_SC_KEYPAD_5
#define KP_6 HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW
#define KP_7 HID_KEYBOARD_SC_KEYPAD_7_AND_HOME
#define KP_8 HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW
#define KP_9 HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP
#define KP_0 HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT
#define KP_DOT HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE
#define NON_US_BACKSLASH_AND_PIPE HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE
#define APPLICATION HID_KEYBOARD_SC_APPLICATION
#define POWER HID_KEYBOARD_SC_POWER
#define KP_EQUAL HID_KEYBOARD_SC_KEYPAD_EQUAL_SIGN
#define F13 HID_KEYBOARD_SC_F13
#define F14 HID_KEYBOARD_SC_F14
#define F15 HID_KEYBOARD_SC_F15
#define F16 HID_KEYBOARD_SC_F16
#define F17 HID_KEYBOARD_SC_F17
#define F18 HID_KEYBOARD_SC_F18
#define F19 HID_KEYBOARD_SC_F19
#define F20 HID_KEYBOARD_SC_F20
#define F21 HID_KEYBOARD_SC_F21
#define F22 HID_KEYBOARD_SC_F22
#define F23 HID_KEYBOARD_SC_F23
#define F24 HID_KEYBOARD_SC_F24
#define EXECUTE HID_KEYBOARD_SC_EXECUTE
#define HELP HID_KEYBOARD_SC_HELP
#define MENU HID_KEYBOARD_SC_MENU
#define SELECT HID_KEYBOARD_SC_SELECT
#define STOP HID_KEYBOARD_SC_STOP
#define AGAIN HID_KEYBOARD_SC_AGAIN
#define UNDO HID_KEYBOARD_SC_UNDO
#define CUT HID_KEYBOARD_SC_CUT
#define COPY HID_KEYBOARD_SC_COPY
#define PASTE HID_KEYBOARD_SC_PASTE
#define FIND HID_KEYBOARD_SC_FIND
#define MUTE HID_KEYBOARD_SC_MUTE
#define VOLUME_UP HID_KEYBOARD_SC_VOLUME_UP
#define VOLUME_DOWN HID_KEYBOARD_SC_VOLUME_DOWN
#define LOCKING_CAPS_LOCK HID_KEYBOARD_SC_LOCKING_CAPS_LOCK
#define LOCKING_NUM_LOCK HID_KEYBOARD_SC_LOCKING_NUM_LOCK
#define LOCKING_SCROLL_LOCK HID_KEYBOARD_SC_LOCKING_SCROLL_LOCK
#define KP_COMMA HID_KEYBOARD_SC_KEYPAD_COMMA
#define KP_EQUAL_SIGN_AS400 HID_KEYBOARD_SC_KEYPAD_EQUAL_SIGN_AS400
#define INTERNATIONAL1 HID_KEYBOARD_SC_INTERNATIONAL1
#define INTERNATIONAL2 HID_KEYBOARD_SC_INTERNATIONAL2
#define INTERNATIONAL3 HID_KEYBOARD_SC_INTERNATIONAL3
#define INTERNATIONAL4 HID_KEYBOARD_SC_INTERNATIONAL4
#define INTERNATIONAL5 HID_KEYBOARD_SC_INTERNATIONAL5
#define INTERNATIONAL6 HID_KEYBOARD_SC_INTERNATIONAL6
#define INTERNATIONAL7 HID_KEYBOARD_SC_INTERNATIONAL7
#define INTERNATIONAL8 HID_KEYBOARD_SC_INTERNATIONAL8
#define INTERNATIONAL9 HID_KEYBOARD_SC_INTERNATIONAL9
#define LANG1 HID_KEYBOARD_SC_LANG1
#define LANG2 HID_KEYBOARD_SC_LANG2
#define LANG3 HID_KEYBOARD_SC_LANG3
#define LANG4 HID_KEYBOARD_SC_LANG4
#define LANG5 HID_KEYBOARD_SC_LANG5
#define LANG6 HID_KEYBOARD_SC_LANG6
#define LANG7 HID_KEYBOARD_SC_LANG7
#define LANG8 HID_KEYBOARD_SC_LANG8
#define LANG9 HID_KEYBOARD_SC_LANG9
#define ALTERNATE_ERASE HID_KEYBOARD_SC_ALTERNATE_ERASE
#define SYSREQ HID_KEYBOARD_SC_SYSREQ
#define CANCEL HID_KEYBOARD_SC_CANCEL
#define CLEAR HID_KEYBOARD_SC_CLEAR
#define PRIOR HID_KEYBOARD_SC_PRIOR
#define RETURN HID_KEYBOARD_SC_RETURN
#define SEPARATOR HID_KEYBOARD_SC_SEPARATOR
#define OUT HID_KEYBOARD_SC_OUT
#define OPER HID_KEYBOARD_SC_OPER
#define CLEAR_AND_AGAIN HID_KEYBOARD_SC_CLEAR_AND_AGAIN
#define CRSEL_AND_PROPS HID_KEYBOARD_SC_CRSEL_AND_PROPS
#define EXSEL HID_KEYBOARD_SC_EXSEL
#define KP_00 HID_KEYBOARD_SC_KEYPAD_00
#define KP_000 HID_KEYBOARD_SC_KEYPAD_000
#define THOUSANDS_SEPARATOR HID_KEYBOARD_SC_THOUSANDS_SEPARATOR
#define DECIMAL_SEPARATOR HID_KEYBOARD_SC_DECIMAL_SEPARATOR
#define CURRENCY_UNIT HID_KEYBOARD_SC_CURRENCY_UNIT
#define CURRENCY_SUB_UNIT HID_KEYBOARD_SC_CURRENCY_SUB_UNIT
#define KP_OPENING_PARENTHESIS HID_KEYBOARD_SC_KEYPAD_OPENING_PARENTHESIS
#define KP_CLOSING_PARENTHESIS HID_KEYBOARD_SC_KEYPAD_CLOSING_PARENTHESIS
#define KP_OPENING_BRACE HID_KEYBOARD_SC_KEYPAD_OPENING_BRACE
#define KP_CLOSING_BRACE HID_KEYBOARD_SC_KEYPAD_CLOSING_BRACE
#define KP_TAB HID_KEYBOARD_SC_KEYPAD_TAB
#define KP_BACKSPACE HID_KEYBOARD_SC_KEYPAD_BACKSPACE
#define KP_A HID_KEYBOARD_SC_KEYPAD_A
#define KP_B HID_KEYBOARD_SC_KEYPAD_B
#define KP_C HID_KEYBOARD_SC_KEYPAD_C
#define KP_D HID_KEYBOARD_SC_KEYPAD_D
#define KP_E HID_KEYBOARD_SC_KEYPAD_E
#define KP_F HID_KEYBOARD_SC_KEYPAD_F
#define KP_XOR HID_KEYBOARD_SC_KEYPAD_XOR
#define KP_CARET HID_KEYBOARD_SC_KEYPAD_CARET
#define KP_PERCENTAGE HID_KEYBOARD_SC_KEYPAD_PERCENTAGE
#define KP_LESS_THAN_SIGN HID_KEYBOARD_SC_KEYPAD_LESS_THAN_SIGN
#define KP_GREATER_THAN_SIGN HID_KEYBOARD_SC_KEYPAD_GREATER_THAN_SIGN
#define KP_AMP HID_KEYBOARD_SC_KEYPAD_AMP
#define KP_AMP_AMP HID_KEYBOARD_SC_KEYPAD_AMP_AMP
#define KP_PIPE HID_KEYBOARD_SC_KEYPAD_PIPE
#define KP_PIPE_PIPE HID_KEYBOARD_SC_KEYPAD_PIPE_PIPE
#define KP_COLON HID_KEYBOARD_SC_KEYPAD_COLON
#define KP_HASHMARK HID_KEYBOARD_SC_KEYPAD_HASHMARK
#define KP_SPACE HID_KEYBOARD_SC_KEYPAD_SPACE
#define KP_AT HID_KEYBOARD_SC_KEYPAD_AT
#define KP_EXCLAMATION_SIGN HID_KEYBOARD_SC_KEYPAD_EXCLAMATION_SIGN
#define KP_MEMORY_STORE HID_KEYBOARD_SC_KEYPAD_MEMORY_STORE
#define KP_MEMORY_RECALL HID_KEYBOARD_SC_KEYPAD_MEMORY_RECALL
#define KP_MEMORY_CLEAR HID_KEYBOARD_SC_KEYPAD_MEMORY_CLEAR
#define KP_MEMORY_ADD HID_KEYBOARD_SC_KEYPAD_MEMORY_ADD
#define KP_MEMORY_SUBTRACT HID_KEYBOARD_SC_KEYPAD_MEMORY_SUBTRACT
#define KP_MEMORY_MULTIPLY HID_KEYBOARD_SC_KEYPAD_MEMORY_MULTIPLY
#define KP_MEMORY_DIVIDE HID_KEYBOARD_SC_KEYPAD_MEMORY_DIVIDE
#define KP_PLUS_AND_MINUS HID_KEYBOARD_SC_KEYPAD_PLUS_AND_MINUS
#define KP_CLEAR HID_KEYBOARD_SC_KEYPAD_CLEAR
#define KP_CLEAR_ENTRY HID_KEYBOARD_SC_KEYPAD_CLEAR_ENTRY
#define KP_BINARY HID_KEYBOARD_SC_KEYPAD_BINARY
#define KP_OCTAL HID_KEYBOARD_SC_KEYPAD_OCTAL
#define KP_DECIMAL HID_KEYBOARD_SC_KEYPAD_DECIMAL
#define KP_HEXADECIMAL HID_KEYBOARD_SC_KEYPAD_HEXADECIMAL
#define L_CTRL HID_KEYBOARD_SC_LEFT_CONTROL
#define L_SHIFT HID_KEYBOARD_SC_LEFT_SHIFT
#define L_ALT HID_KEYBOARD_SC_LEFT_ALT
#define L_GUI HID_KEYBOARD_SC_LEFT_GUI
#define R_CTRL HID_KEYBOARD_SC_RIGHT_CONTROL
#define R_SHIFT HID_KEYBOARD_SC_RIGHT_SHIFT
#define R_ALT HID_KEYBOARD_SC_RIGHT_ALT
#define R_GUI HID_KEYBOARD_SC_RIGHT_GUI
#define MEDIA_PLAY HID_KEYBOARD_SC_MEDIA_PLAY
#define MEDIA_STOP HID_KEYBOARD_SC_MEDIA_STOP
#define MEDIA_PREVIOUS_TRACK HID_KEYBOARD_SC_MEDIA_PREVIOUS_TRACK
#define MEDIA_NEXT_TRACK HID_KEYBOARD_SC_MEDIA_NEXT_TRACK
#define MEDIA_EJECT HID_KEYBOARD_SC_MEDIA_EJECT
#define MEDIA_VOLUME_UP HID_KEYBOARD_SC_MEDIA_VOLUME_UP
#define MEDIA_VOLUME_DOWN HID_KEYBOARD_SC_MEDIA_VOLUME_DOWN
#define MEDIA_MUTE HID_KEYBOARD_SC_MEDIA_MUTE
#define MEDIA_WWW HID_KEYBOARD_SC_MEDIA_WWW
#define MEDIA_BACKWARD HID_KEYBOARD_SC_MEDIA_BACKWARD
#define MEDIA_FORWARD HID_KEYBOARD_SC_MEDIA_FORWARD
#define MEDIA_CANCEL HID_KEYBOARD_SC_MEDIA_CANCEL
#define MEDIA_SEARCH HID_KEYBOARD_SC_MEDIA_SEARCH
#define MEDIA_SLEEP HID_KEYBOARD_SC_MEDIA_SLEEP
#define MEDIA_LOCK HID_KEYBOARD_SC_MEDIA_LOCK
#define MEDIA_RELOAD HID_KEYBOARD_SC_MEDIA_RELOAD
#define MEDIA_CALCULATOR HID_KEYBOARD_SC_MEDIA_CALCULATOR

#define MUTE       0xE2
#define VOL_UP     0xE9
#define VOL_DOWN   0xEA
#define NEXT_TRACK 0xB5
#define PREV_TRACK 0xB6
#define STOP       0xB7
#define STOP_EJECT 0xCC
#define PLAY_PAUSE 0xCD

#define POWER_DOWN 0x81
#define SLEEP      0x82
#define WAKE_UP    0x83

#define NO_ACTION { actions_none }
#define LAYOUT(...) \
const __flash struct action layout[][ROWS * COLUMNS] = { __VA_ARGS__ }
#define LEADER_KEY { actions_leader_key }
#define TRANSPARENT { uint8_transparent }

#define OSA(action) \
{ \
    actions_oneshot_action, \
    &(const __flash struct actions_oneshot_action_data){ \
        action, \
        &(struct actions_oneshot_action_storage){ { 0 } } \
    } \
}

#define LEADER_KEY_DICTIONARY(...) \
const __flash uint8_t leader_key_dictionary_length = sizeof (struct leader_key_dictionary_entry []){ __VA_ARGS__ } / sizeof(struct leader_key_dictionary_entry); \
 \
const __flash struct leader_key_dictionary_entry leader_key_dictionary[] = { \
    __VA_ARGS__, \
}

#define LEADER_KEY_DICTIONARY_ENTRY(sequence, action) \
{ \
    action, \
    (const __flash uint16_t [])sequence, \
    sizeof (uint16_t [])sequence / sizeof(uint16_t), \
}

#define LEADER_KEY_SEQUENCE(...) { __VA_ARGS__ }

#define TDA(...) \
{ \
    actions_tap_dance_actions, \
    &(const __flash struct actions_tap_dance_actions_data){ \
        (const __flash struct action []){ __VA_ARGS__, __VA_ARGS__ }, \
        &(struct actions_tap_dance_actions_storage){ 0 }, \
        sizeof (struct action []){ __VA_ARGS__ } / sizeof(struct action), \
    } \
}

#define ATDA(...) \
{ \
    actions_tap_dance_actions, \
    &(const __flash struct actions_tap_dance_actions_data){ \
        (const __flash struct action []){ __VA_ARGS__ }, \
        &(struct actions_tap_dance_actions_storage){ 0 }, \
        sizeof (struct action []){ __VA_ARGS__ } / 2 / sizeof(struct action), \
    } \
}

#define HTA(hold_action, tap_action) \
{ \
    actions_hold_tap_actions, \
    &(const __flash struct actions_hold_tap_actions_data){ \
        hold_action, \
        tap_action, \
    } \
}

#define THA(tap_action, hold_action) \
{ \
    actions_tap_hold_actions, \
    &(const __flash struct actions_tap_hold_actions_data){ \
        tap_action, \
        hold_action, \
        &(struct actions_tap_hold_actions_storage){ 0 } \
    } \
}

#define SA(...) \
{ \
    actions_sequential_actions, \
    &(const __flash struct actions_sequential_actions_data){ \
        (const __flash struct action []){ __VA_ARGS__ }, \
        sizeof (struct action []){ __VA_ARGS__ } / sizeof(struct action), \
    } \
}

#define NA(...) \
{ \
    actions_nested_actions, \
    &(const __flash struct actions_nested_actions_data){ \
        (const __flash struct action []){ __VA_ARGS__ }, \
        sizeof (struct action []){ __VA_ARGS__ } / sizeof(struct action), \
    } \
}

#define SSA(primary_action, secondary_action) \
{ \
    actions_shift_switch_actions, \
    &(const __flash struct actions_shift_switch_actions_data){ \
        primary_action, \
        secondary_action, \
        &(struct actions_shift_switch_actions_storage){ 0 } \
    } \
}

enum layer_operations {
    VISIT,
    GOTO
};

#define L_CREATE_FCN(operation) \
(operation == VISIT ? actions_layers_visit : \
operation == GOTO ? actions_layers_goto : 0)

#define L(operation, layer) \
{ \
    L_CREATE_FCN(operation), \
    (const __flash uint8_t []){ layer } \
}

#define RESET \
{ \
    actions_reset \
}

#define K_CREATE_FCN(code) \
((code) >> 8 && (code) & 0xFF ? actions_modifiers_and_scancode : \
(code) & 0xFF ? actions_scancode : \
(code) >> 8 ? actions_modifiers : 0)

#define PM_CREATE_FCN(code) \
((code) & 0xFF00 ? actions_modifiers_and_power_management : \
actions_power_management)

#define M_CREATE_FCN(code) \
((code) & 0xFF0000 ? actions_modifiers_and_multimedia : actions_multimedia)

#define K_CREATE_ARG(code) \
((code) & 0xFF00 && (code) & 0xFF ? (const __flash uint8_t *)&(const __flash uint16_t){ (code) } : \
(code) & 0xFF ? &(const __flash uint8_t){ (code) & 0xFF } : &(const __flash uint8_t){ (code) >> 8 })

#define PM_CREATE_ARG(code) \
((code) & 0xFF00 && (code) & 0xFF ? (const __flash uint8_t *)&(const __flash uint16_t){ (code) & 0xFFFF } : \
&(const __flash uint8_t){ (code) & 0xFF })

#define M_CREATE_ARG(code) \
((code) & 0xFF0000 && (code) & 0xFFFF ? (const __flash uint8_t []){ (code) & 0xFF, (code) >> 8 & 0xFF, (code) >> 16 & 0xFF } : \
(const __flash uint8_t *)&(const __flash uint16_t){ (code) & 0xFFFF })

#define K(code) \
{ \
    K_CREATE_FCN(code), \
    K_CREATE_ARG(code) \
}

#define PM(code) \
{ \
    PM_CREATE_FCN((code) & 0xFF), \
    PM_CREATE_ARG((code) & 0xFF) \
}

#define M(code) \
{ \
    M_CREATE_FCN((code) & 0xFFFF), \
    M_CREATE_ARG((code) & 0xFFFF) \
}

#endif
