#ifndef LAYOUT_H
#define LAYOUT_H

#include <stdint.h>
#include "matrix.h"
#include "actions.h"
#include <LUFA/Drivers/USB/USB.h>


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

extern const __flash action_t layout[][ROWS][COLUMNS];

#define NO_ACTION { 0 }
#define LAYOUT(...) \
const __flash action_t layout[][ROWS][COLUMNS] = { __VA_ARGS__ }
#define LEADER_KEY { key_leader_start }
#define TRANSPARENT { keyswitch_transparent }

#define LEADER_KEY_SEQUENCE(...) { __VA_ARGS__, { 0 } }


#define HT(hold_action, tap_action) \
{ \
    key_hold_tap, \
    (const __flash action_t []){ hold_action, tap_action } \
}

#define TH(tap_action, hold_action) \
{ \
    key_tap_hold, \
    (const __flash action_t []){ tap_action, hold_action } \
}

#define MA(...) \
{ \
    key_multiple_actions, \
    (const __flash action_t []){ __VA_ARGS__, { 0 } } \
}

#define CC(case_number) \
{ \
    key_custom_code, \
    (const __flash uint8_t){ case_number } \
}

enum layer_operations {
    VISIT,
    TOGGLE,
    GOTO
};

#define L_CREATE_FCN(operation) \
(operation == VISIT ? actions_layer_visit_wrapper : \
operation == TOGGLE ? actions_layer_toggle_wrapper : \
operation == GOTO ? actions_layer_goto_wrapper : 0)

#define L(operation, ...) \
{ \
    L_CREATE_FCN(operation), \
    (const __flash uint8_t []){ __VA_ARGS__ } \
}

#define RESET \
{ \
    actions_reset, \
    0 \
}

#define M(code) \
{ \
    key_mouse, \
}
#if 0
code == NORTH ?
code == SOUTH ?
code == EAST ?
code == WEST ?
code == NORTHEAST ?
code == SOUTHEAST ?
code == SOUTHWEST ?
code == NORTHWEST ?
code == CLICK ?
code == DOUBLE_CLICK ?
code == CLICK_BEGIN ?
code == CLICK_END ?
#endif



// TODO: Make US() output a 16-bit value consisting of a scancode byte and a
// modifier byte above it. The processing of somethingss will take place in it.
// Make the outer code detect whether each is present and choose a function and
// the associated data acccordingly. Do not do this when sleepy

enum {
    SCANCODE_OFFSET = 0,
    CHARACTER_OFFSET = 0,
    MODIFIER_OFFSET = 32,
    DISAMBIGUATION_OFFSET = 40
};

enum {
    NK_VALUE = 1,
    DEAD_VALUE = 1 << 1,
    NP_VALUE = 1 << 2
};


#define CODE_GET_DISAMBIGUATION(code) (((uint64_t)(code) >> DISAMBIGUATION_OFFSET) & 0xFF)
#define CODE_GET_MODIFIER(code) (((uint64_t)(code) >> MODIFIER_OFFSET) & 0xFF)
#define CODE_GET_SCANCODE(code) (((uint64_t)(code) >> SCANCODE_OFFSET) & 0xFF)
#define CODE_GET_CHARACTER(code) (((uint64_t)(code) >> CHARACTER_OFFSET) & 0xFFFFFFFF)

#define NK(code) ((code) | ((uint64_t)NK_VALUE << DISAMBIGUATION_OFFSET))
#define DEAD(code) ((code) | ((uint64_t)DEAD_VALUE << DISAMBIGUATION_OFFSET))
#define NP(code) ((code) | ((uint64_t)NP_VALUE << DISAMBIGUATION_OFFSET))

#define L_C(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTCTRL << MODIFIER_OFFSET))
#define L_S(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTSHIFT << MODIFIER_OFFSET))
#define L_A(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTALT << MODIFIER_OFFSET))
#define L_G(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_LEFTGUI << MODIFIER_OFFSET))
#define R_C(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTCTRL << MODIFIER_OFFSET))
#define R_S(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTSHIFT << MODIFIER_OFFSET))
#define R_A(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTALT << MODIFIER_OFFSET))
#define R_G(code) ((code) | ((uint64_t)HID_KEYBOARD_MODIFIER_RIGHTGUI << MODIFIER_OFFSET))

enum english_nonprinting_codes {
    BKSP = 1,
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
    F24
};

enum input_sources {
    US,
    US_DVORAK,
    US_COLEMAK,
};

#define US_CODE_TO_SCANCODE(code) (CODE_GET_DISAMBIGUATION(code) & NP_VALUE ? US_NONPRINTING_CODE_TO_SCANCODE(code) : US_PRINTING_CODE_TO_SCANCODE(code))

#define US_NONPRINTING_CODE_TO_SCANCODE(code) \
(((code & 0xFFFFFFFF) == BKSP ? HID_KEYBOARD_SC_BACKSPACE : \
(code & 0xFFFFFFFF) == ENTER ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_ENTER : HID_KEYBOARD_SC_KEYPAD_ENTER : \
(code & 0xFFFFFFFF) == HOME ? HID_KEYBOARD_SC_HOME : \
(code & 0xFFFFFFFF) == END ? HID_KEYBOARD_SC_END : \
(code & 0xFFFFFFFF) == PG_UP ? HID_KEYBOARD_SC_PAGE_UP : \
(code & 0xFFFFFFFF) == PG_DN ? HID_KEYBOARD_SC_PAGE_DOWN : \
(code & 0xFFFFFFFF) == INSERT ? HID_KEYBOARD_SC_INSERT : \
(code & 0xFFFFFFFF) == DELETE ? HID_KEYBOARD_SC_DELETE : \
(code & 0xFFFFFFFF) == TAB ? HID_KEYBOARD_SC_TAB : \
(code & 0xFFFFFFFF) == CAPS_LOCK ? HID_KEYBOARD_SC_CAPS_LOCK : \
(code & 0xFFFFFFFF) == NUM_LOCK ? HID_KEYBOARD_SC_NUM_LOCK : \
(code & 0xFFFFFFFF) == SCROLL_LOCK ? HID_KEYBOARD_SC_SCROLL_LOCK : \
(code & 0xFFFFFFFF) == PRINT_SCREEN ? HID_KEYBOARD_SC_PRINT_SCREEN : \
(code & 0xFFFFFFFF) == L_SHIFT ? L_S(0) : \
(code & 0xFFFFFFFF) == R_SHIFT ? R_S(0) : \
(code & 0xFFFFFFFF) == L_CTRL ? L_C(0) : \
(code & 0xFFFFFFFF) == R_CTRL ? R_C(0) : \
(code & 0xFFFFFFFF) == L_ALT ? L_A(0) : \
(code & 0xFFFFFFFF) == R_ALT ? R_A(0) : \
(code & 0xFFFFFFFF) == L_GUI ? L_G(0) : \
(code & 0xFFFFFFFF) == R_GUI ? R_G(0) : \
(code & 0xFFFFFFFF) == UP ? HID_KEYBOARD_SC_UP_ARROW : \
(code & 0xFFFFFFFF) == DOWN ? HID_KEYBOARD_SC_DOWN_ARROW : \
(code & 0xFFFFFFFF) == LEFT ? HID_KEYBOARD_SC_LEFT_ARROW : \
(code & 0xFFFFFFFF) == RIGHT ? HID_KEYBOARD_SC_RIGHT_ARROW : \
(code & 0xFFFFFFFF) == F1 ? HID_KEYBOARD_SC_F1 : \
(code & 0xFFFFFFFF) == F2 ? HID_KEYBOARD_SC_F2 : \
(code & 0xFFFFFFFF) == F3 ? HID_KEYBOARD_SC_F3 : \
(code & 0xFFFFFFFF) == F4 ? HID_KEYBOARD_SC_F4 : \
(code & 0xFFFFFFFF) == F5 ? HID_KEYBOARD_SC_F5 : \
(code & 0xFFFFFFFF) == F6 ? HID_KEYBOARD_SC_F6 : \
(code & 0xFFFFFFFF) == F7 ? HID_KEYBOARD_SC_F7 : \
(code & 0xFFFFFFFF) == F8 ? HID_KEYBOARD_SC_F8 : \
(code & 0xFFFFFFFF) == F9 ? HID_KEYBOARD_SC_F9 : \
(code & 0xFFFFFFFF) == F10 ? HID_KEYBOARD_SC_F10 : \
(code & 0xFFFFFFFF) == F11 ? HID_KEYBOARD_SC_F11 : \
(code & 0xFFFFFFFF) == F12 ? HID_KEYBOARD_SC_F12 : \
(code & 0xFFFFFFFF) == F13 ? HID_KEYBOARD_SC_F13 : \
(code & 0xFFFFFFFF) == F14 ? HID_KEYBOARD_SC_F14 : \
(code & 0xFFFFFFFF) == F15 ? HID_KEYBOARD_SC_F15 : \
(code & 0xFFFFFFFF) == F16 ? HID_KEYBOARD_SC_F16 : \
(code & 0xFFFFFFFF) == F17 ? HID_KEYBOARD_SC_F17 : \
(code & 0xFFFFFFFF) == F18 ? HID_KEYBOARD_SC_F18 : \
(code & 0xFFFFFFFF) == F19 ? HID_KEYBOARD_SC_F19 : \
(code & 0xFFFFFFFF) == F20 ? HID_KEYBOARD_SC_F20 : \
(code & 0xFFFFFFFF) == F21 ? HID_KEYBOARD_SC_F21 : \
(code & 0xFFFFFFFF) == F22 ? HID_KEYBOARD_SC_F22 : \
(code & 0xFFFFFFFF) == F23 ? HID_KEYBOARD_SC_F23 : \
(code & 0xFFFFFFFF) == F24 ? HID_KEYBOARD_SC_F24 : 0) | (code & ~0xFFFFFFFFULL))

#define US_PRINTING_CODE_TO_SCANCODE(code) \
(((code & 0xFFFFFFFF) == ' ' ? HID_KEYBOARD_SC_SPACE : \
(code & 0xFFFFFFFF) == '!' ? R_S(HID_KEYBOARD_SC_1_AND_EXCLAMATION) : \
(code & 0xFFFFFFFF) == '\"' ? R_S(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE) : \
(code & 0xFFFFFFFF) == '#' ? R_S(HID_KEYBOARD_SC_3_AND_HASHMARK) : \
(code & 0xFFFFFFFF) == '$' ? R_S(HID_KEYBOARD_SC_4_AND_DOLLAR) : \
(code & 0xFFFFFFFF) == '%' ? R_S(HID_KEYBOARD_SC_5_AND_PERCENTAGE) : \
(code & 0xFFFFFFFF) == '&' ? R_S(HID_KEYBOARD_SC_7_AND_AMPERSAND) : \
(code & 0xFFFFFFFF) == '\'' ? HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE : \
(code & 0xFFFFFFFF) == '(' ? R_S(HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS) : \
(code & 0xFFFFFFFF) == ')' ? R_S(HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS) : \
(code & 0xFFFFFFFF) == '*' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_ASTERISK : R_S(HID_KEYBOARD_SC_8_AND_ASTERISK) : \
(code & 0xFFFFFFFF) == '+' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_PLUS : R_S(HID_KEYBOARD_SC_EQUAL_AND_PLUS) : \
(code & 0xFFFFFFFF) == ',' ? HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN : \
(code & 0xFFFFFFFF) == '-' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_MINUS : HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE : \
(code & 0xFFFFFFFF) == '.' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE : HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN : \
(code & 0xFFFFFFFF) == '/' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_SLASH : HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK : \
(code & 0xFFFFFFFF) == '0' ? CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT : HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS : \
(code & 0xFFFFFFFF) >= '1' && code <= '9' ? code - '1' + (CODE_GET_DISAMBIGUATION(code) & NK_VALUE ? HID_KEYBOARD_SC_KEYPAD_1_AND_END : HID_KEYBOARD_SC_1_AND_EXCLAMATION) : \
(code & 0xFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON) : \
(code & 0xFFFFFFFF) == ';' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
(code & 0xFFFFFFFF) == '<' ? R_S(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN) : \
(code & 0xFFFFFFFF) == '=' ? HID_KEYBOARD_SC_EQUAL_AND_PLUS : \
(code & 0xFFFFFFFF) == '>' ? R_S(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN) : \
(code & 0xFFFFFFFF) == '\?' ? R_S(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK) : \
(code & 0xFFFFFFFF) == '@' ? R_S(HID_KEYBOARD_SC_2_AND_AT) : \
(code & 0xFFFFFFFF) >= 'A' && code <= 'Z' ? R_S(code - 'A' + HID_KEYBOARD_SC_A) : \
(code & 0xFFFFFFFF) == '[' ? HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE : \
(code & 0xFFFFFFFF) == '\\' ? HID_KEYBOARD_SC_BACKSLASH_AND_PIPE : \
(code & 0xFFFFFFFF) == ']' ? HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE : \
(code & 0xFFFFFFFF) == '^' ? R_S(HID_KEYBOARD_SC_6_AND_CARET) : \
(code & 0xFFFFFFFF) == '_' ? R_S(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE) : \
(code & 0xFFFFFFFF) == '`' ? HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE : \
(code & 0xFFFFFFFF) >= 'a' && code <= 'z' ? code - 'a' + HID_KEYBOARD_SC_A : \
(code & 0xFFFFFFFF) == '{' ? R_S(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE) : \
(code & 0xFFFFFFFF) == '|' ? R_S(HID_KEYBOARD_SC_BACKSLASH_AND_PIPE) : \
(code & 0xFFFFFFFF) == '}' ? R_S(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE) : \
(code & 0xFFFFFFFF) == '~' ? R_S(HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE) : 0) | (code & ~0xFFFFFFFFULL))

#define US_DVORAK_CODE_TO_SCANCODE(code) (CODE_GET_DISAMBIGUATION(code) & NP_VALUE ? US_NONPRINTING_CODE_TO_SCANCODE(code) : US_DVORAK_PRINTING_CODE_TO_SCANCODE(code))
#define US_COLEMAK_CODE_TO_SCANCODE(code) (CODE_GET_DISAMBIGUATION(code) & NP_VALUE ? US_NONPRINTING_CODE_TO_SCANCODE(code) : COLEMAK_PRINTING_CODE_TO_SCANCODE(code))

#define US_DVORAK_PRINTING_CODE_TO_SCANCODE(code) \
(((code & 0xFFFFFFFF) == '\'' ? HID_KEYBOARD_SC_Q : \
(code & 0xFFFFFFFF) == '+' ? R_S(HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE) : \
(code & 0xFFFFFFFF) == ',' ? HID_KEYBOARD_SC_W : \
(code & 0xFFFFFFFF) == '-' ? HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE : \
(code & 0xFFFFFFFF) == '.' ? HID_KEYBOARD_SC_E : \
(code & 0xFFFFFFFF) == '/' ? HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE : \
(code & 0xFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_Z) : \
(code & 0xFFFFFFFF) == ';' ? HID_KEYBOARD_SC_Z : \
(code & 0xFFFFFFFF) == '<' ? R_S(HID_KEYBOARD_SC_W) : \
(code & 0xFFFFFFFF) == '=' ? HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE : \
(code & 0xFFFFFFFF) == '>' ? R_S(HID_KEYBOARD_SC_E) : \
(code & 0xFFFFFFFF) == '\?' ? R_S(HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE) : \
(code & 0xFFFFFFFF) == 'B' ? R_S(HID_KEYBOARD_SC_N) : \
(code & 0xFFFFFFFF) == 'C' ? R_S(HID_KEYBOARD_SC_I) : \
(code & 0xFFFFFFFF) == 'D' ? R_S(HID_KEYBOARD_SC_H) : \
(code & 0xFFFFFFFF) == 'E' ? R_S(HID_KEYBOARD_SC_D) : \
(code & 0xFFFFFFFF) == 'F' ? R_S(HID_KEYBOARD_SC_Y) : \
(code & 0xFFFFFFFF) == 'G' ? R_S(HID_KEYBOARD_SC_U) : \
(code & 0xFFFFFFFF) == 'H' ? R_S(HID_KEYBOARD_SC_J) : \
(code & 0xFFFFFFFF) == 'I' ? R_S(HID_KEYBOARD_SC_G) : \
(code & 0xFFFFFFFF) == 'J' ? R_S(HID_KEYBOARD_SC_C) : \
(code & 0xFFFFFFFF) == 'K' ? R_S(HID_KEYBOARD_SC_V) : \
(code & 0xFFFFFFFF) == 'L' ? R_S(HID_KEYBOARD_SC_P) : \
(code & 0xFFFFFFFF) == 'N' ? R_S(HID_KEYBOARD_SC_L) : \
(code & 0xFFFFFFFF) == 'O' ? R_S(HID_KEYBOARD_SC_S) : \
(code & 0xFFFFFFFF) == 'P' ? R_S(HID_KEYBOARD_SC_R) : \
(code & 0xFFFFFFFF) == 'Q' ? R_S(HID_KEYBOARD_SC_X) : \
(code & 0xFFFFFFFF) == 'R' ? R_S(HID_KEYBOARD_SC_O) : \
(code & 0xFFFFFFFF) == 'S' ? R_S(R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON)) : \
(code & 0xFFFFFFFF) == 'T' ? R_S(HID_KEYBOARD_SC_K) : \
(code & 0xFFFFFFFF) == 'U' ? R_S(HID_KEYBOARD_SC_F) : \
(code & 0xFFFFFFFF) == 'V' ? R_S(HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN) : \
(code & 0xFFFFFFFF) == 'W' ? R_S(HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN) : \
(code & 0xFFFFFFFF) == 'X' ? R_S(HID_KEYBOARD_SC_B) : \
(code & 0xFFFFFFFF) == 'Y' ? R_S(HID_KEYBOARD_SC_T) : \
(code & 0xFFFFFFFF) == 'Z' ? R_S(HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK) : \
(code & 0xFFFFFFFF) == '[' ? HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE : \
(code & 0xFFFFFFFF) == ']' ? HID_KEYBOARD_SC_EQUAL_AND_PLUS : \
(code & 0xFFFFFFFF) == '_' ? R_S(HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE) : \
(code & 0xFFFFFFFF) == 'b' ? HID_KEYBOARD_SC_N : \
(code & 0xFFFFFFFF) == 'c' ? HID_KEYBOARD_SC_I : \
(code & 0xFFFFFFFF) == 'd' ? HID_KEYBOARD_SC_H : \
(code & 0xFFFFFFFF) == 'e' ? HID_KEYBOARD_SC_D : \
(code & 0xFFFFFFFF) == 'f' ? HID_KEYBOARD_SC_Y : \
(code & 0xFFFFFFFF) == 'g' ? HID_KEYBOARD_SC_U : \
(code & 0xFFFFFFFF) == 'h' ? HID_KEYBOARD_SC_J : \
(code & 0xFFFFFFFF) == 'i' ? HID_KEYBOARD_SC_G : \
(code & 0xFFFFFFFF) == 'j' ? HID_KEYBOARD_SC_C : \
(code & 0xFFFFFFFF) == 'k' ? HID_KEYBOARD_SC_V : \
(code & 0xFFFFFFFF) == 'l' ? HID_KEYBOARD_SC_P : \
(code & 0xFFFFFFFF) == 'n' ? HID_KEYBOARD_SC_L : \
(code & 0xFFFFFFFF) == 'o' ? HID_KEYBOARD_SC_S : \
(code & 0xFFFFFFFF) == 'p' ? HID_KEYBOARD_SC_R : \
(code & 0xFFFFFFFF) == 'q' ? HID_KEYBOARD_SC_X : \
(code & 0xFFFFFFFF) == 'r' ? HID_KEYBOARD_SC_O : \
(code & 0xFFFFFFFF) == 's' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
(code & 0xFFFFFFFF) == 't' ? HID_KEYBOARD_SC_K : \
(code & 0xFFFFFFFF) == 'u' ? HID_KEYBOARD_SC_F : \
(code & 0xFFFFFFFF) == 'v' ? HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN : \
(code & 0xFFFFFFFF) == 'w' ? HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN : \
(code & 0xFFFFFFFF) == 'x' ? HID_KEYBOARD_SC_B : \
(code & 0xFFFFFFFF) == 'y' ? HID_KEYBOARD_SC_T : \
(code & 0xFFFFFFFF) == 'z' ? HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK : \
(code & 0xFFFFFFFF) == '{' ? R_S(HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE) : \
(code & 0xFFFFFFFF) == '}' ? R_S(HID_KEYBOARD_SC_EQUAL_AND_PLUS) : \
US_PRINTING_CODE_TO_SCANCODE(code)) | (code & ~0xFFFFFFFFULL))

#define COLEMAK_PRINTING_CODE_TO_SCANCODE(code) \
(((code & 0xFFFFFFFF) == ':' ? R_S(HID_KEYBOARD_SC_P) : \
(code & 0xFFFFFFFF) == ';' ? HID_KEYBOARD_SC_P : \
(code & 0xFFFFFFFF) == 'D' ? R_S(HID_KEYBOARD_SC_G) : \
(code & 0xFFFFFFFF) == 'E' ? R_S(HID_KEYBOARD_SC_K) : \
(code & 0xFFFFFFFF) == 'F' ? R_S(HID_KEYBOARD_SC_E) : \
(code & 0xFFFFFFFF) == 'G' ? R_S(HID_KEYBOARD_SC_T) : \
(code & 0xFFFFFFFF) == 'I' ? R_S(HID_KEYBOARD_SC_L) : \
(code & 0xFFFFFFFF) == 'J' ? R_S(HID_KEYBOARD_SC_Y) : \
(code & 0xFFFFFFFF) == 'K' ? R_S(HID_KEYBOARD_SC_N) : \
(code & 0xFFFFFFFF) == 'L' ? R_S(HID_KEYBOARD_SC_U) : \
(code & 0xFFFFFFFF) == 'N' ? R_S(HID_KEYBOARD_SC_J) : \
(code & 0xFFFFFFFF) == 'O' ? R_S(HID_KEYBOARD_SC_SEMICOLON_AND_COLON) : \
(code & 0xFFFFFFFF) == 'P' ? R_S(HID_KEYBOARD_SC_R) : \
(code & 0xFFFFFFFF) == 'R' ? R_S(HID_KEYBOARD_SC_S) : \
(code & 0xFFFFFFFF) == 'S' ? R_S(HID_KEYBOARD_SC_D) : \
(code & 0xFFFFFFFF) == 'T' ? R_S(HID_KEYBOARD_SC_F) : \
(code & 0xFFFFFFFF) == 'U' ? R_S(HID_KEYBOARD_SC_I) : \
(code & 0xFFFFFFFF) == 'Y' ? R_S(HID_KEYBOARD_SC_O) : \
(code & 0xFFFFFFFF) == 'd' ? HID_KEYBOARD_SC_G : \
(code & 0xFFFFFFFF) == 'e' ? HID_KEYBOARD_SC_K : \
(code & 0xFFFFFFFF) == 'f' ? HID_KEYBOARD_SC_E : \
(code & 0xFFFFFFFF) == 'g' ? HID_KEYBOARD_SC_T : \
(code & 0xFFFFFFFF) == 'i' ? HID_KEYBOARD_SC_L : \
(code & 0xFFFFFFFF) == 'j' ? HID_KEYBOARD_SC_Y : \
(code & 0xFFFFFFFF) == 'k' ? HID_KEYBOARD_SC_N : \
(code & 0xFFFFFFFF) == 'l' ? HID_KEYBOARD_SC_U : \
(code & 0xFFFFFFFF) == 'n' ? HID_KEYBOARD_SC_J : \
(code & 0xFFFFFFFF) == 'o' ? HID_KEYBOARD_SC_SEMICOLON_AND_COLON : \
(code & 0xFFFFFFFF) == 'p' ? HID_KEYBOARD_SC_R : \
(code & 0xFFFFFFFF) == 'r' ? HID_KEYBOARD_SC_S : \
(code & 0xFFFFFFFF) == 's' ? HID_KEYBOARD_SC_D : \
(code & 0xFFFFFFFF) == 't' ? HID_KEYBOARD_SC_F : \
(code & 0xFFFFFFFF) == 'u' ? HID_KEYBOARD_SC_I : \
(code & 0xFFFFFFFF) == 'y' ? HID_KEYBOARD_SC_O : \
US_PRINTING_CODE_TO_SCANCODE(code)) | (code & ~0xFFFFFFFFULL))

#define K_CREATE_FCN(code) \
(code >> 8 && code & 0xFF ? actions_modifier_and_scancode_wrapper : \
code & 0xFF ? actions_scancode_wrapper : \
code >> 8 ? actions_modifiers_wrapper : 0)

#define K_CREATE_ARG(code) \
(code >> 8 && code & 0xFF ? (const __flash void *)&(const __flash uint16_t){ code } : \
code & 0xFF ? (const __flash void *)&(const __flash uint8_t){ code & 0xFF } : (const __flash void *)&(const __flash uint8_t){ code >> 8 })

#define K(code) \
{ \
    K_CREATE_FCN(code), \
    K_CREATE_ARG(code) \
}

#define SC(country, code) \
SC_ASSEMBLE((country == US ? US_CODE_TO_SCANCODE(code) : \
country == US_DVORAK ? US_DVORAK_CODE_TO_SCANCODE(code) : 0))

#define SC_ASSEMBLE(code) (CODE_GET_MODIFIER(code) << 8 | CODE_GET_SCANCODE(code))

#endif
