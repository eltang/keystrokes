#include "layout.h"
#include "../ergodox.h"

#define BASE 0
#define SYMB 1
#define MDIA 2

LAYOUT(
    [BASE] = LAYER(
        K(SC(US, '=')), K(SC(US, '1')), K(SC(US, '2')), K(SC(US, '3')), K(SC(US, '4')), K(SC(US, '5')), K(SC(US, L_C('-'))),
        K(SC(US, DELETE)), K(SC(US, 'q')), K(SC(US, 'w')), K(SC(US, 'e')), K(SC(US, 'r')), K(SC(US, 't')), L(GOTO, SYMB),
        K(SC(US, BKSP)), K(SC(US, 'a')), K(SC(US, 's')), K(SC(US, 'd')), K(SC(US, 'f')), K(SC(US, 'g')),
        HT(K(SC(US, L_SHIFT)), K(SC(US, '('))), TH(K(SC(US, 'z')), K(SC(US, L_CTRL))), K(SC(US, 'x')), K(SC(US, 'c')), K(SC(US, 'v')), K(SC(US, 'b')), HT(K(SC(US, L_C(L_S(L_A(L_G(0)))))), K(SC(US, '['))),
        HT(L(VISIT, SYMB), K(SC(US, '`'))), K(SC(US, '\'')), K(SC(US, L_A(L_S(0)))), K(SC(US, LEFT)), K(SC(US, RIGHT)),
                                                                HT(K(SC(US, L_ALT)), K(SC(US, APP))), K(SC(US, L_GUI)),
                                                                           K(SC(US, HOME)),
                                                     K(SC(US, ' ')), LEADER_KEY, K(SC(US, END)),
        K(SC(US, R_C('='))), K(SC(US, '6')), K(SC(US, '7')), K(SC(US, '8')), K(SC(US, '9')), K(SC(US, '0')), K(SC(US, '-')),
        L(GOTO, SYMB), K(SC(US, 'y')), K(SC(US, 'u')), K(SC(US, 'i')), K(SC(US, 'o')), K(SC(US, 'p')), K(SC(US, '\\')),
                    K(SC(US, 'h')), TH(K(SC(US, 'j')), K(SC(US, R_ALT))), K(SC(US, 'k')), K(SC(US, 'l')), TH(K(SC(US, ';')), L(VISIT, MDIA)), TH(K(SC(US, '\'')), K(SC(US, R_GUI))),
        HT(K(SC(US, R_C(R_S(R_A(0))))), K(SC(US, ']'))), K(SC(US, 'n')), K(SC(US, 'm')), K(SC(US, ',')), K(SC(US, '.')), TH(K(SC(US, '/')), K(SC(US, R_CTRL))), HT(K(SC(US, R_SHIFT)), K(SC(US, ')'))),
                               K(SC(US, UP)), K(SC(US, DOWN)), K(SC(US, '[')), K(SC(US, ']')), HT(L(VISIT, SYMB), K(SC(US, '-'))),
        K(SC(US, R_ALT)), HT(K(SC(US, R_CTRL)), K(SC(US, ESC))),
        K(SC(US, PG_UP)),
        K(SC(US, PG_DN)), HT(L(VISIT, SYMB), K(SC(US, TAB))), K(SC(US, ENTER))
    ),
    [SYMB] = LAYER(
         NO_ACTION, K(SC(US, F1)), K(SC(US, F2)), K(SC(US, F3)), K(SC(US, F4)), K(SC(US, F5)), NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, L(GOTO, BASE),
         NO_ACTION, K(SC(US, '1')), K(SC(US, '2')), K(SC(US, '3')), K(SC(US, '4')), K(SC(US, '5')),
         NO_ACTION, K(SC(US, '6')), K(SC(US, '7')), K(SC(US, '8')), K(SC(US, '9')), K(SC(US, '0')), NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, K(SC(US, L_C(PG_UP))), K(SC(US, L_C(PG_DN))),
                                                                NO_ACTION, NO_ACTION,
                                                                           NO_ACTION,
                                                     NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, K(SC(US, F6)), K(SC(US, F7)), K(SC(US, F8)), K(SC(US, F9)), K(SC(US, F10)), K(SC(US, F11)),
         L(GOTO, BASE), NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, K(SC(US, F12)),
                    K(SC(US, '&')), K(SC(US, '_')), K(SC(US, '-')), K(SC(US, 'p')), K(SC(US, '+')), NO_ACTION,
         NO_ACTION, K(SC(US, '|')), K(SC(US, '@')), K(SC(US, '=')), K(SC(US, '%')), NO_ACTION, NO_ACTION,
                               NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION,
         NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION
    ),
    [MDIA] = LAYER(
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, K(SC(US, PG_UP)), K(SC(US, HOME)), K(SC(US, END)), K(SC(US, PG_DN)), NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                                NO_ACTION, NO_ACTION,
                                                                           NO_ACTION,
                                                     NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                    NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, K(C(0xCD)),
         NO_ACTION, NO_ACTION, NO_ACTION, K(C(0xB6)), K(C(0xB5)), NO_ACTION, NO_ACTION,
                               K(C(0xE9)), K(C(0xEA)), K(C(0xE2)), NO_ACTION, NO_ACTION,
         NO_ACTION, NO_ACTION,
         NO_ACTION,
         NO_ACTION, NO_ACTION, K(C(0x0224))
    ),
);

LEADER_KEY_DICTIONARY(
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(SC(US, 'w'), 0, 0, 0),
        K(SC(US, L_A(F4)))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(SC(US, 'o'), 0, 0, 0),
        K(SC(US, L_C('O')))
    )
);
