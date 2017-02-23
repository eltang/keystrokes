#include "layout.h"
#include "../ergodox.h"

LAYOUT(
    LAYER(
        K(SC(US, ESC)), K(SC(US, '1')), K(SC(US, '2')), K(SC(US, '3')), K(SC(US, '4')), K(SC(US, '5')), K(SC(US, '`')),
        K(SC(US, TAB)), K(SC(US, '\'')), K(SC(US, ',')), K(SC(US, '.')), K(SC(US, 'p')), K(SC(US, 'y')), K(SC(US, '[')),
        K(SC(US, CAPS_LOCK)), K(SC(US, 'a')), K(SC(US, 'o')), K(SC(US, 'e')), K(SC(US, 'u')), K(SC(US, 'i')),
        HT(K(SC(US, L_SHIFT)), K(SC(US, '('))), K(SC(US, ';')), K(SC(US, 'q')), K(SC(US, 'j')), K(SC(US, 'k')), K(SC(US, 'x')), L(GOTO, 1),
        NO_ACTION, K(GD(0x81)), K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)),
                                                                K(SC(US, HOME)), K(SC(US, END)),
                                                                          K(SC(US, PG_UP)),
                                                     K(SC(US, ' ')), K(SC(US, BKSP)), K(SC(US, PG_DN)),
        K(SC(US, '\\')), K(SC(US, '6')), K(SC(US, '7')), K(SC(US, '8')), K(SC(US, '9')), K(SC(US, '0')), K(SC(US, '=')),
        K(SC(US, ']')), K(SC(US, 'f')), K(SC(US, 'g')), K(SC(US, 'c')), K(SC(US, 'r')), K(SC(US, 'l')), K(SC(US, '/')),
                   K(SC(US, 'd')), K(SC(US, 'h')), K(SC(US, 't')), K(SC(US, 'n')), K(SC(US, 's')), K(SC(US, '-')),
        NO_ACTION, K(SC(US, 'b')), K(SC(US, 'm')), K(SC(US, 'w')), K(SC(US, 'v')), K(SC(US, 'z')), HT(K(SC(US, R_SHIFT)), K(SC(US, ')'))),
                   K(SC(US, R_GUI)), K(SC(US, R_ALT)), K(SC(US, R_CTRL)), K(GD(0x81)), NO_ACTION,
        K(SC(US, LEFT)), K(SC(US, RIGHT)),
        K(SC(US, UP)),
        K(SC(US, DOWN)), K(SC(US, ENTER)), K(SC(US, ' '))
    ),
    LAYER(
        RESET, K(SC(US, F11)), K(SC(US, F12)), K(SC(US, F13)), K(SC(US, F14)), K(SC(US, F15)), NO_ACTION,
        NO_ACTION, K(SC(US, F6)), K(SC(US, F7)), K(SC(US, F8)), K(SC(US, F9)), K(SC(US, F10)), NO_ACTION,
        NO_ACTION, K(SC(US, F1)), K(SC(US, F2)), K(SC(US, F3)), K(SC(US, F4)), K(SC(US, F5)),
        HT(K(SC(US, L_SHIFT)), K(SC(US, '('))), NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)),
                                                                NO_ACTION, NO_ACTION,
                                                                           NO_ACTION,
                                                     K(C(0xEA)), K(C(0xE9)), K(C(0xE2)),
        NO_ACTION, NO_ACTION, K(SC(US, NUM_LOCK)), K(SC(US, NK('/'))), K(SC(US, NK('*'))), K(SC(US, NK('-'))), NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, NK('7'))), K(SC(US, NK('8'))), K(SC(US, NK('9'))), K(SC(US, NK('+'))), NO_ACTION,
                   NO_ACTION, K(SC(US, NK('4'))), K(SC(US, NK('5'))), K(SC(US, NK('6'))), K(SC(US, NK('+'))), NO_ACTION,
        L(GOTO, 0), NO_ACTION, K(SC(US, NK('1'))), K(SC(US, NK('2'))), K(SC(US, NK('3'))), K(SC(US, NK(ENTER))), HT(K(SC(US, R_SHIFT)), K(SC(US, ')'))),
                   K(SC(US, R_GUI)), K(SC(US, R_ALT)), TH(K(SC(US, NK('.'))), K(SC(US, R_CTRL))), NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, NK('0')))
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

        NO_ACTION, NO_ACTION, NO_ACTION, M(LEFT_BUTTON)), M(BOTH_BUTTONS)), M(RIGHT_BUTTON)), NO_ACTION,
        NO_ACTION, NO_ACTION, M(NORTHWEST)), M(NORTH)), M(NORTHEAST)), M(DOUBLE_CLICK)), NO_ACTION,
                   NO_ACTION, M(WEST)), M(CLICK)), M(EAST)), M(DOUBLE_CLICK)), NO_ACTION,
        NO_ACTION, NO_ACTION, M(SOUTHWEST)), M(SOUTH)), M(SOUTHEAST)), NO_ACTION, NO_ACTION,
                   NO_ACTION, NO_ACTION, NO_ACTION, M(RELEASE)), NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, M(PRESS)
    ))
#endif
);

const __flash leader_key_dictionary_entry_t leader_key_dictionary[] = {
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(0, 0, 0, 0),
        NO_ACTION
    )
};
