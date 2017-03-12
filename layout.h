#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>
#include "matrix.h"
#include "actions.h"
#include <LUFA/Drivers/USB/USB.h>
#include "leader_key.h"


/*
 * NOTE: The compiler code is suboptimal, but it's not really worth it to
 * improve it because it should never be in any of the code that the keyboard
 * itself executes.
 */
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

#define NO_ACTION { actions_none }
#define LAYOUT(...) \
const __flash struct action layout[][ROWS * COLUMNS] = { __VA_ARGS__ }
#define LEADER_KEY { actions_leader_key }
#define TRANSPARENT { uint8_transparent }


#define LEADER_KEY_DICTIONARY(...) \
const __flash struct leader_key_dictionary_entry leader_key_dictionary[] = { \
    __VA_ARGS__, \
    LEADER_KEY_DICTIONARY_ENTRY( \
        LEADER_KEY_SEQUENCE(0, 0, 0, 0), \
        NO_ACTION \
    ) \
}

#define LEADER_KEY_DICTIONARY_ENTRY(sequence, action) \
{ \
    sequence, \
    action \
}

#define LEADER_KEY_SEQUENCE(one, two, three, four) \
((uint64_t)four << 48 | (uint64_t)three << 32 | (uint64_t)two << 16 | one)

#define TD(...) \
{ \
    actions_tap_dance, \
    &(const __flash struct actions_tap_dance_data){ \
        (const __flash struct action []){ __VA_ARGS__, NO_ACTION }, \
        &(struct actions_tap_dance_storage){ { 0 } }, \
        sizeof (struct action []){ __VA_ARGS__ } / sizeof(struct action), \
    } \
}

#define HT(hold_action, tap_action) \
{ \
    actions_hold_tap, \
    &(const __flash struct actions_hold_tap_data){ \
        hold_action, \
        tap_action, \
        &(struct actions_hold_tap_storage){ { 0 } } \
    } \
}

#define TH(tap_action, hold_action) \
{ \
    actions_tap_hold, \
    &(const __flash struct actions_tap_hold_data){ \
        tap_action, \
        hold_action, \
        &(struct actions_tap_hold_storage){ { 0 } } \
    } \
}

#define MA(...) \
{ \
    actions_multiple_actions, \
    (const __flash struct action []){ __VA_ARGS__, { actions_none } } \
}

#define CC(case_number) \
{ \
    actions_custom_code, \
    (const __flash uint8_t){ case_number } \
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

enum {
    SCANCODE_OFFSET = 0,
    CHARACTER_OFFSET = 0,
    MODIFIER_OFFSET = 40,
    DISAMBIGUATION_OFFSET = 48
};

enum {
    NK_VALUE = 1,
    D_VALUE = 1 << 1,
};


#define CODE_GET_DISAMBIGUATION(code) (((uint64_t)(code) >> DISAMBIGUATION_OFFSET) & 0xFF)
#define CODE_GET_MODIFIER(code) (((uint64_t)(code) >> MODIFIER_OFFSET) & 0xFF)
#define CODE_GET_SCANCODE(code) (((uint64_t)(code) >> SCANCODE_OFFSET) & 0xFF)
#define CODE_GET_CHARACTER(code) (((uint64_t)(code) >> CHARACTER_OFFSET) & 0xFFFFFFFF)

#define NK(code) ((code) | ((uint64_t)NK_VALUE << DISAMBIGUATION_OFFSET))
#define D(code) ((code) | ((uint64_t)D_VALUE << DISAMBIGUATION_OFFSET))

#define L_C(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTCTRL << MODIFIER_OFFSET))
#define L_S(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTSHIFT << MODIFIER_OFFSET))
#define L_A(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTALT << MODIFIER_OFFSET))
#define L_G(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTGUI << MODIFIER_OFFSET))
#define R_C(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTCTRL << MODIFIER_OFFSET))
#define R_S(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTSHIFT << MODIFIER_OFFSET))
#define R_A(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTALT << MODIFIER_OFFSET))
#define R_G(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTGUI << MODIFIER_OFFSET))

enum {
    BKSP = 0x100000000,
    ENTER,
    HOME,
    END,
    PG_UP,
    PG_DN,
    INSERT,
    DELETE,
    TAB,
    CAPS_LOCK,
    NUM_LOCK,
    SCROLL_LOCK,
    PRINT_SCREEN,
    L_SHIFT,
    R_SHIFT,
    L_CTRL,
    R_CTRL,
    L_ALT,
    R_ALT,
    L_GUI,
    R_GUI,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ESC,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    APP
};

enum input_sources {
    US,
    US_DVORAK,
    US_COLEMAK,
};

#define US_CODE_TO_SCANCODE(code) \
((((code) & 0xFFFFFFFFFF) == BKSP ? HID_KEYBOARD_SC_BACKSPACE : \
((code) & 0xFFFFFFFFFF) == ENTER ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_ENTER : HID_KEYBOARD_SC_ENTER : \
((code) & 0xFFFFFFFFFF) == HOME ? HID_KEYBOARD_SC_HOME : \
((code) & 0xFFFFFFFFFF) == END ? HID_KEYBOARD_SC_END : \
((code) & 0xFFFFFFFFFF) == PG_UP ? HID_KEYBOARD_SC_PAGE_UP : \
((code) & 0xFFFFFFFFFF) == PG_DN ? HID_KEYBOARD_SC_PAGE_DOWN : \
((code) & 0xFFFFFFFFFF) == INSERT ? HID_KEYBOARD_SC_INSERT : \
((code) & 0xFFFFFFFFFF) == DELETE ? HID_KEYBOARD_SC_DELETE : \
((code) & 0xFFFFFFFFFF) == TAB ? HID_KEYBOARD_SC_TAB : \
((code) & 0xFFFFFFFFFF) == CAPS_LOCK ? HID_KEYBOARD_SC_CAPS_LOCK : \
((code) & 0xFFFFFFFFFF) == NUM_LOCK ? HID_KEYBOARD_SC_NUM_LOCK : \
((code) & 0xFFFFFFFFFF) == SCROLL_LOCK ? HID_KEYBOARD_SC_SCROLL_LOCK : \
((code) & 0xFFFFFFFFFF) == PRINT_SCREEN ? HID_KEYBOARD_SC_PRINT_SCREEN : \
((code) & 0xFFFFFFFFFF) == L_SHIFT ? L_S(0) : \
((code) & 0xFFFFFFFFFF) == R_SHIFT ? R_S(0) : \
((code) & 0xFFFFFFFFFF) == L_CTRL ? L_C(0) : \
((code) & 0xFFFFFFFFFF) == R_CTRL ? R_C(0) : \
((code) & 0xFFFFFFFFFF) == L_ALT ? L_A(0) : \
((code) & 0xFFFFFFFFFF) == R_ALT ? R_A(0) : \
((code) & 0xFFFFFFFFFF) == L_GUI ? L_G(0) : \
((code) & 0xFFFFFFFFFF) == R_GUI ? R_G(0) : \
((code) & 0xFFFFFFFFFF) == UP ? HID_KEYBOARD_SC_UP_ARROW : \
((code) & 0xFFFFFFFFFF) == DOWN ? HID_KEYBOARD_SC_DOWN_ARROW : \
((code) & 0xFFFFFFFFFF) == LEFT ? HID_KEYBOARD_SC_LEFT_ARROW : \
((code) & 0xFFFFFFFFFF) == RIGHT ? HID_KEYBOARD_SC_RIGHT_ARROW : \
((code) & 0xFFFFFFFFFF) == ESC ? HID_KEYBOARD_SC_ESCAPE : \
((code) & 0xFFFFFFFFFF) == F1 ? HID_KEYBOARD_SC_F1 : \
((code) & 0xFFFFFFFFFF) == F2 ? HID_KEYBOARD_SC_F2 : \
((code) & 0xFFFFFFFFFF) == F3 ? HID_KEYBOARD_SC_F3 : \
((code) & 0xFFFFFFFFFF) == F4 ? HID_KEYBOARD_SC_F4 : \
((code) & 0xFFFFFFFFFF) == F5 ? HID_KEYBOARD_SC_F5 : \
((code) & 0xFFFFFFFFFF) == F6 ? HID_KEYBOARD_SC_F6 : \
((code) & 0xFFFFFFFFFF) == F7 ? HID_KEYBOARD_SC_F7 : \
((code) & 0xFFFFFFFFFF) == F8 ? HID_KEYBOARD_SC_F8 : \
((code) & 0xFFFFFFFFFF) == F9 ? HID_KEYBOARD_SC_F9 : \
((code) & 0xFFFFFFFFFF) == F10 ? HID_KEYBOARD_SC_F10 : \
((code) & 0xFFFFFFFFFF) == F11 ? HID_KEYBOARD_SC_F11 : \
((code) & 0xFFFFFFFFFF) == F12 ? HID_KEYBOARD_SC_F12 : \
((code) & 0xFFFFFFFFFF) == F13 ? HID_KEYBOARD_SC_F13 : \
((code) & 0xFFFFFFFFFF) == F14 ? HID_KEYBOARD_SC_F14 : \
((code) & 0xFFFFFFFFFF) == F15 ? HID_KEYBOARD_SC_F15 : \
((code) & 0xFFFFFFFFFF) == F16 ? HID_KEYBOARD_SC_F16 : \
((code) & 0xFFFFFFFFFF) == F17 ? HID_KEYBOARD_SC_F17 : \
((code) & 0xFFFFFFFFFF) == F18 ? HID_KEYBOARD_SC_F18 : \
((code) & 0xFFFFFFFFFF) == F19 ? HID_KEYBOARD_SC_F19 : \
((code) & 0xFFFFFFFFFF) == F20 ? HID_KEYBOARD_SC_F20 : \
((code) & 0xFFFFFFFFFF) == F21 ? HID_KEYBOARD_SC_F21 : \
((code) & 0xFFFFFFFFFF) == F22 ? HID_KEYBOARD_SC_F22 : \
((code) & 0xFFFFFFFFFF) == F23 ? HID_KEYBOARD_SC_F23 : \
((code) & 0xFFFFFFFFFF) == F24 ? HID_KEYBOARD_SC_F24 : \
((code) & 0xFFFFFFFFFF) == APP ? HID_KEYBOARD_SC_APPLICATION : \
((code) & 0xFFFFFFFFFF) == ' ' ? HID_KEYBOARD_SC_SPACE : \
((code) & 0xFFFFFFFFFF) == '!' ? R_S(HID_KEYBOARD_SC_1_AND_EXCLAMATION) : \
((code) & 0xFFFFFFFFFF) == '\"' ? R_S(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE) : \
((code) & 0xFFFFFFFFFF) == '#' ? R_S(HID_KEYBOARD_SC_3_AND_HASHMARK) : \
((code) & 0xFFFFFFFFFF) == '$' ? R_S(HID_KEYBOARD_SC_4_AND_DOLLAR) : \
((code) & 0xFFFFFFFFFF) == '%' ? R_S(HID_KEYBOARD_SC_5_AND_PERCENTAGE) : \
((code) & 0xFFFFFFFFFF) == '&' ? R_S(HID_KEYBOARD_SC_7_AND_AMPERSAND) : \
((code) & 0xFFFFFFFFFF) == '\'' ? HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE : \
((code) & 0xFFFFFFFFFF) == '(' ? R_S(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS) : \
((code) & 0xFFFFFFFFFF) == ')' ? R_S(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS) : \
((code) & 0xFFFFFFFFFF) == '*' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_ASTERISK : R_S(HID_KEYBOARD_SC_8_AND_ASTERISK) : \
((code) & 0xFFFFFFFFFF) == '+' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_PLUS : R_S(HID_KEYBOARD_SC_EQUAL_AND_PLUS) : \
((code) & 0xFFFFFFFFFF) == ',' ? HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN : \
((code) & 0xFFFFFFFFFF) == '-' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_MINUS : HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE : \
((code) & 0xFFFFFFFFFF) == '.' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE : HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN : \
((code) & 0xFFFFFFFFFF) == '/' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_SLASH : HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK : \
((code) & 0xFFFFFFFFFF) == '0' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT : HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS : \
((code) & 0xFFFFFFFFFF) >= '1' && ((code) & 0xFFFFFFFFFF) <= '9' ? ((code) & 0xFFFFFFFFFF) - '1' + (CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_1_AND_END : HID_KEYBOARD_SC_1_AND_EXCLAMATION) : \
((code) & 0xFFFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON) : \
((code) & 0xFFFFFFFFFF) == ';' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
((code) & 0xFFFFFFFFFF) == '<' ? R_S(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN) : \
((code) & 0xFFFFFFFFFF) == '=' ? HID_KEYBOARD_SC_EQUAL_AND_PLUS : \
((code) & 0xFFFFFFFFFF) == '>' ? R_S(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN) : \
((code) & 0xFFFFFFFFFF) == '\?' ? R_S(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK) : \
((code) & 0xFFFFFFFFFF) == '@' ? R_S(HID_KEYBOARD_SC_2_AND_AT) : \
((code) & 0xFFFFFFFFFF) >= 'A' && ((code) & 0xFFFFFFFFFF) <= 'Z' ? R_S((code) - 'A' + HID_KEYBOARD_SC_A) : \
((code) & 0xFFFFFFFFFF) == '[' ? HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE : \
((code) & 0xFFFFFFFFFF) == '\\' ? HID_KEYBOARD_SC_BACKSLASH_AND_PIPE : \
((code) & 0xFFFFFFFFFF) == ']' ? HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE : \
((code) & 0xFFFFFFFFFF) == '^' ? R_S(HID_KEYBOARD_SC_6_AND_CARET) : \
((code) & 0xFFFFFFFFFF) == '_' ? R_S(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE) : \
((code) & 0xFFFFFFFFFF) == '`' ? HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE : \
((code) & 0xFFFFFFFFFF) >= 'a' && (code) <= 'z' ? (code) - 'a' + HID_KEYBOARD_SC_A : \
((code) & 0xFFFFFFFFFF) == '{' ? R_S(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE) : \
((code) & 0xFFFFFFFFFF) == '|' ? R_S(HID_KEYBOARD_SC_BACKSLASH_AND_PIPE) : \
((code) & 0xFFFFFFFFFF) == '}' ? R_S(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE) : \
((code) & 0xFFFFFFFFFF) == '~' ? R_S(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE) : 0) | ((code) & ~(uint64_t)0xFFFFFFFFFF))

#define US_DVORAK_CODE_TO_SCANCODE(code) \
((((code) & 0xFFFFFFFFFF) == '\'' ? HID_KEYBOARD_SC_Q : \
((code) & 0xFFFFFFFFFF) == '+' ? R_S(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE) : \
((code) & 0xFFFFFFFFFF) == ',' ? HID_KEYBOARD_SC_W : \
((code) & 0xFFFFFFFFFF) == '-' ? HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE : \
((code) & 0xFFFFFFFFFF) == '.' ? HID_KEYBOARD_SC_E : \
((code) & 0xFFFFFFFFFF) == '/' ? HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE : \
((code) & 0xFFFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_Z) : \
((code) & 0xFFFFFFFFFF) == ';' ? HID_KEYBOARD_SC_Z : \
((code) & 0xFFFFFFFFFF) == '<' ? R_S(HID_KEYBOARD_SC_W) : \
((code) & 0xFFFFFFFFFF) == '=' ? HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE : \
((code) & 0xFFFFFFFFFF) == '>' ? R_S(HID_KEYBOARD_SC_E) : \
((code) & 0xFFFFFFFFFF) == '\?' ? R_S(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE) : \
((code) & 0xFFFFFFFFFF) == 'B' ? R_S(HID_KEYBOARD_SC_N) : \
((code) & 0xFFFFFFFFFF) == 'C' ? R_S(HID_KEYBOARD_SC_I) : \
((code) & 0xFFFFFFFFFF) == 'D' ? R_S(HID_KEYBOARD_SC_H) : \
((code) & 0xFFFFFFFFFF) == 'E' ? R_S(HID_KEYBOARD_SC_D) : \
((code) & 0xFFFFFFFFFF) == 'F' ? R_S(HID_KEYBOARD_SC_Y) : \
((code) & 0xFFFFFFFFFF) == 'G' ? R_S(HID_KEYBOARD_SC_U) : \
((code) & 0xFFFFFFFFFF) == 'H' ? R_S(HID_KEYBOARD_SC_J) : \
((code) & 0xFFFFFFFFFF) == 'I' ? R_S(HID_KEYBOARD_SC_G) : \
((code) & 0xFFFFFFFFFF) == 'J' ? R_S(HID_KEYBOARD_SC_C) : \
((code) & 0xFFFFFFFFFF) == 'K' ? R_S(HID_KEYBOARD_SC_V) : \
((code) & 0xFFFFFFFFFF) == 'L' ? R_S(HID_KEYBOARD_SC_P) : \
((code) & 0xFFFFFFFFFF) == 'N' ? R_S(HID_KEYBOARD_SC_L) : \
((code) & 0xFFFFFFFFFF) == 'O' ? R_S(HID_KEYBOARD_SC_S) : \
((code) & 0xFFFFFFFFFF) == 'P' ? R_S(HID_KEYBOARD_SC_R) : \
((code) & 0xFFFFFFFFFF) == 'Q' ? R_S(HID_KEYBOARD_SC_X) : \
((code) & 0xFFFFFFFFFF) == 'R' ? R_S(HID_KEYBOARD_SC_O) : \
((code) & 0xFFFFFFFFFF) == 'S' ? R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON) : \
((code) & 0xFFFFFFFFFF) == 'T' ? R_S(HID_KEYBOARD_SC_K) : \
((code) & 0xFFFFFFFFFF) == 'U' ? R_S(HID_KEYBOARD_SC_F) : \
((code) & 0xFFFFFFFFFF) == 'V' ? R_S(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN) : \
((code) & 0xFFFFFFFFFF) == 'W' ? R_S(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN) : \
((code) & 0xFFFFFFFFFF) == 'X' ? R_S(HID_KEYBOARD_SC_B) : \
((code) & 0xFFFFFFFFFF) == 'Y' ? R_S(HID_KEYBOARD_SC_T) : \
((code) & 0xFFFFFFFFFF) == 'Z' ? R_S(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK) : \
((code) & 0xFFFFFFFFFF) == '[' ? HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE : \
((code) & 0xFFFFFFFFFF) == ']' ? HID_KEYBOARD_SC_EQUAL_AND_PLUS : \
((code) & 0xFFFFFFFFFF) == '_' ? R_S(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE) : \
((code) & 0xFFFFFFFFFF) == 'b' ? HID_KEYBOARD_SC_N : \
((code) & 0xFFFFFFFFFF) == 'c' ? HID_KEYBOARD_SC_I : \
((code) & 0xFFFFFFFFFF) == 'd' ? HID_KEYBOARD_SC_H : \
((code) & 0xFFFFFFFFFF) == 'e' ? HID_KEYBOARD_SC_D : \
((code) & 0xFFFFFFFFFF) == 'f' ? HID_KEYBOARD_SC_Y : \
((code) & 0xFFFFFFFFFF) == 'g' ? HID_KEYBOARD_SC_U : \
((code) & 0xFFFFFFFFFF) == 'h' ? HID_KEYBOARD_SC_J : \
((code) & 0xFFFFFFFFFF) == 'i' ? HID_KEYBOARD_SC_G : \
((code) & 0xFFFFFFFFFF) == 'j' ? HID_KEYBOARD_SC_C : \
((code) & 0xFFFFFFFFFF) == 'k' ? HID_KEYBOARD_SC_V : \
((code) & 0xFFFFFFFFFF) == 'l' ? HID_KEYBOARD_SC_P : \
((code) & 0xFFFFFFFFFF) == 'n' ? HID_KEYBOARD_SC_L : \
((code) & 0xFFFFFFFFFF) == 'o' ? HID_KEYBOARD_SC_S : \
((code) & 0xFFFFFFFFFF) == 'p' ? HID_KEYBOARD_SC_R : \
((code) & 0xFFFFFFFFFF) == 'q' ? HID_KEYBOARD_SC_X : \
((code) & 0xFFFFFFFFFF) == 'r' ? HID_KEYBOARD_SC_O : \
((code) & 0xFFFFFFFFFF) == 's' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
((code) & 0xFFFFFFFFFF) == 't' ? HID_KEYBOARD_SC_K : \
((code) & 0xFFFFFFFFFF) == 'u' ? HID_KEYBOARD_SC_F : \
((code) & 0xFFFFFFFFFF) == 'v' ? HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN : \
((code) & 0xFFFFFFFFFF) == 'w' ? HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN : \
((code) & 0xFFFFFFFFFF) == 'x' ? HID_KEYBOARD_SC_B : \
((code) & 0xFFFFFFFFFF) == 'y' ? HID_KEYBOARD_SC_T : \
((code) & 0xFFFFFFFFFF) == 'z' ? HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK : \
((code) & 0xFFFFFFFFFF) == '{' ? R_S(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE) : \
((code) & 0xFFFFFFFFFF) == '}' ? R_S(HID_KEYBOARD_SC_EQUAL_AND_PLUS) : \
US_CODE_TO_SCANCODE(code)) | ((code) & ~(uint64_t)0xFFFFFFFFFF))

#define US_COLEMAK_CODE_TO_SCANCODE(code) \
((((code) & 0xFFFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_P) : \
((code) & 0xFFFFFFFFFF) == ';' ? HID_KEYBOARD_SC_P : \
((code) & 0xFFFFFFFFFF) == 'D' ? R_S(HID_KEYBOARD_SC_G) : \
((code) & 0xFFFFFFFFFF) == 'E' ? R_S(HID_KEYBOARD_SC_K) : \
((code) & 0xFFFFFFFFFF) == 'F' ? R_S(HID_KEYBOARD_SC_E) : \
((code) & 0xFFFFFFFFFF) == 'G' ? R_S(HID_KEYBOARD_SC_T) : \
((code) & 0xFFFFFFFFFF) == 'I' ? R_S(HID_KEYBOARD_SC_L) : \
((code) & 0xFFFFFFFFFF) == 'J' ? R_S(HID_KEYBOARD_SC_Y) : \
((code) & 0xFFFFFFFFFF) == 'K' ? R_S(HID_KEYBOARD_SC_N) : \
((code) & 0xFFFFFFFFFF) == 'L' ? R_S(HID_KEYBOARD_SC_U) : \
((code) & 0xFFFFFFFFFF) == 'N' ? R_S(HID_KEYBOARD_SC_J) : \
((code) & 0xFFFFFFFFFF) == 'O' ? R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON) : \
((code) & 0xFFFFFFFFFF) == 'P' ? R_S(HID_KEYBOARD_SC_R) : \
((code) & 0xFFFFFFFFFF) == 'R' ? R_S(HID_KEYBOARD_SC_S) : \
((code) & 0xFFFFFFFFFF) == 'S' ? R_S(HID_KEYBOARD_SC_D) : \
((code) & 0xFFFFFFFFFF) == 'T' ? R_S(HID_KEYBOARD_SC_F) : \
((code) & 0xFFFFFFFFFF) == 'U' ? R_S(HID_KEYBOARD_SC_I) : \
((code) & 0xFFFFFFFFFF) == 'Y' ? R_S(HID_KEYBOARD_SC_O) : \
((code) & 0xFFFFFFFFFF) == 'd' ? HID_KEYBOARD_SC_G : \
((code) & 0xFFFFFFFFFF) == 'e' ? HID_KEYBOARD_SC_K : \
((code) & 0xFFFFFFFFFF) == 'f' ? HID_KEYBOARD_SC_E : \
((code) & 0xFFFFFFFFFF) == 'g' ? HID_KEYBOARD_SC_T : \
((code) & 0xFFFFFFFFFF) == 'i' ? HID_KEYBOARD_SC_L : \
((code) & 0xFFFFFFFFFF) == 'j' ? HID_KEYBOARD_SC_Y : \
((code) & 0xFFFFFFFFFF) == 'k' ? HID_KEYBOARD_SC_N : \
((code) & 0xFFFFFFFFFF) == 'l' ? HID_KEYBOARD_SC_U : \
((code) & 0xFFFFFFFFFF) == 'n' ? HID_KEYBOARD_SC_J : \
((code) & 0xFFFFFFFFFF) == 'o' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
((code) & 0xFFFFFFFFFF) == 'p' ? HID_KEYBOARD_SC_R : \
((code) & 0xFFFFFFFFFF) == 'r' ? HID_KEYBOARD_SC_S : \
((code) & 0xFFFFFFFFFF) == 's' ? HID_KEYBOARD_SC_D : \
((code) & 0xFFFFFFFFFF) == 't' ? HID_KEYBOARD_SC_F : \
((code) & 0xFFFFFFFFFF) == 'u' ? HID_KEYBOARD_SC_I : \
((code) & 0xFFFFFFFFFF) == 'y' ? HID_KEYBOARD_SC_O : \
US_PRINTING_CODE_TO_SCANCODE(code)) | ((code) & ~(uint64_t)0xFFFFFFFFFF))

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

#define SC_ASSEMBLE(code) \
(CODE_GET_MODIFIER(code) << 8 | CODE_GET_SCANCODE(code))

#define SC(country, code) \
SC_ASSEMBLE((country == US ? US_CODE_TO_SCANCODE(code) : \
country == US_DVORAK ? US_DVORAK_CODE_TO_SCANCODE(code) : 0))

#define PM(code) \
{ \
    PM_CREATE_FCN(CODE_GET_MODIFIER(code) << 8 | ((code) & 0xFF)), \
    PM_CREATE_ARG(CODE_GET_MODIFIER(code) << 8 | ((code) & 0xFF)) \
}

#define M(code) \
{ \
    M_CREATE_FCN(CODE_GET_MODIFIER(code) << 16 | ((code) & 0xFFFF)), \
    M_CREATE_ARG(CODE_GET_MODIFIER(code) << 16 | ((code) & 0xFFFF)) \
}

#endif
