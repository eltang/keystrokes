#include "layout.h"
#include "../ergodox.h"

LAYOUT(
    LAYER(
        K(ESC), K(US_7), K(US_5), K(US_3), K(US_1), K(US_9), K(US_OPENING_BRACKET),
        K(US_GRAVE), K(US_APOSTROPHE), K(US_COMMA), K(US_PERIOD), K(US_P), K(US_Y), K(BKSP),
        K(TAB), K(US_A), K(US_O), K(US_E), K(US_U), K(US_I),
        K(CAPS_LOCK), K(US_SEMICOLON), K(US_Q), K(US_J), K(US_K), K(US_X), L(GOTO, 1),
        NO_ACTION, NO_ACTION, K(L_CTRL), K(L_ALT), K(L_GUI),
                                                               K(HOME), K(END),
                                                                          K(PG_UP),
                                                    K(SPACE), K(L_SHIFT), K(PG_DN),
        K(US_CLOSING_BRACKET), K(US_0), K(US_2), K(US_4), K(US_6), K(US_8), K(US_BACKSLASH),
        K(ENTER), K(US_F), K(US_G), K(US_C), K(US_R), K(US_L), K(US_EQUAL),
                   K(US_D), K(US_H), K(US_T), K(US_N), K(US_S), K(US_SLASH),
        NO_ACTION, K(US_B), K(US_M), K(US_W), K(US_V), K(US_Z), K(US_HYPHEN),
                              K(R_GUI), K(R_ALT),K(R_CTRL), NO_ACTION, NO_ACTION,
        M(0xE2), PM(0x81),
        M(0xE9),
        M(0xEA), K(R_SHIFT), K(SPACE)
    ),
    LAYER(
        NO_ACTION, K(F11), K(F12), K(F13), K(F14), K(F15), NO_ACTION,
        NO_ACTION, K(F6), K(F7), K(F8), K(F9), K(F10), NO_ACTION,
        NO_ACTION, K(F1), K(F2), K(F3), K(F4), K(F5),
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, L(GOTO, 2),
        NO_ACTION, NO_ACTION, K(L_CTRL), K(L_ALT), K(L_GUI),
                                                               NO_ACTION, NO_ACTION,
                                                                          NO_ACTION,
                                                    NO_ACTION, K(L_SHIFT), NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, K(UP), NO_ACTION, NO_ACTION, NO_ACTION,
                   NO_ACTION, K(LEFT), K(DOWN), K(RIGHT), NO_ACTION, NO_ACTION,
        L(GOTO, 0), NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                              K(R_GUI), K(R_ALT), K(R_CTRL), NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, K(R_SHIFT), NO_ACTION
    ),
    LAYER(
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                               NO_ACTION, NO_ACTION,
                                                                          NO_ACTION,
                                                    RESET, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, K(NUM_LOCK), K(KP_SLASH), K(KP_ASTERISK), K(KP_MINUS), NO_ACTION,
        NO_ACTION, NO_ACTION, K(KP_7), K(KP_8), K(KP_9), K(KP_PLUS), NO_ACTION,
                   NO_ACTION, K(KP_4), K(KP_5), K(KP_6), K(KP_PLUS), NO_ACTION,
        L(GOTO, 0), NO_ACTION, K(KP_1), K(KP_2), K(KP_3), K(KP_ENTER), NO_ACTION,
                              K(KP_0), K(KP_0), K(KP_DOT), K(KP_ENTER), NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION
    ),
#if 0
    LAYER(
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                            NO_ACTION, NO_ACTION,
                                                                        NO_ACTION,
                                                 NO_ACTION, NO_ACTION, NO_ACTION,

        NO_ACTION, NO_ACTION, NO_ACTION, M(LEFT_BUTTON), M(BOTH_BUTTONS), M(RIGHT_BUTTON), NO_ACTION,
        NO_ACTION, NO_ACTION, M(NORTHWEST), M(NORTH), M(NORTHEAST), M(DOUBLE_CLICK), NO_ACTION,
                   NO_ACTION, M(WEST), M(CLICK), M(EAST), M(DOUBLE_CLICK), NO_ACTION,
        NO_ACTION, NO_ACTION, M(SOUTHWEST), M(SOUTH), M(SOUTHEAST), NO_ACTION, NO_ACTION,
                   NO_ACTION, NO_ACTION, NO_ACTION, M(RELEASE), NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, M(PRESS)
    ))
#endif
);
