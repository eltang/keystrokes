#include "layout.h"
#include "../ergodox.h"

#define BASE 0
#define SYMB 1
#define MDIA 2

LAYOUT(
    [BASE] = LAYER(
        K(US_SC('=')), K(US_SC('1')), K(US_SC('2')), K(US_SC('3')), K(US_SC('4')), K(US_SC('5')), K(US_SC(L_C('-'))),
        K(US_SC(DELETE)), K(US_SC('q')), K(US_SC('w')), K(US_SC('e')), K(US_SC('r')), K(US_SC('t')), L(GOTO, SYMB),
        K(US_SC(BKSP)), K(US_SC('a')), K(US_SC('s')), K(US_SC('d')), K(US_SC('f')), K(US_SC('g')),
        HTA(K(US_SC(L_SHIFT)), K(US_SC('('))), THA(K(US_SC('z')), K(US_SC(L_CTRL))), K(US_SC('x')), K(US_SC('c')), K(US_SC('v')), K(US_SC('b')), HTA(K(US_SC(L_C(L_S(L_A(L_G(0)))))), K(US_SC('['))),
        HTA(L(VISIT, SYMB), K(US_SC('`'))), K(US_SC('\'')), K(US_SC(L_A(L_S(0)))), K(US_SC(LEFT)), K(US_SC(RIGHT)),
                                                               HTA(K(US_SC(L_ALT)), K(US_SC(APP))), K(US_SC(L_GUI)),
                                                                          K(US_SC(HOME)),
                                                    K(US_SC(' ')), LEADER_KEY, K(US_SC(END)),
        K(US_SC(R_C('='))), K(US_SC('6')), K(US_SC('7')), K(US_SC('8')), K(US_SC('9')), K(US_SC('0')), K(US_SC('-')),
        L(GOTO, SYMB), K(US_SC('y')), K(US_SC('u')), K(US_SC('i')), K(US_SC('o')), K(US_SC('p')), K(US_SC('\\')),
                   K(US_SC('h')), THA(K(US_SC('j')), K(US_SC(R_ALT))), K(US_SC('k')), K(US_SC('l')), THA(K(US_SC(';')), L(VISIT, MDIA)), THA(K(US_SC('\'')), K(US_SC(R_GUI))),
        HTA(K(US_SC(R_C(R_S(R_A(0))))), K(US_SC(']'))), K(US_SC('n')), K(US_SC('m')), K(US_SC(',')), K(US_SC('.')), THA(K(US_SC('/')), K(US_SC(R_CTRL))), HTA(K(US_SC(R_SHIFT)), K(US_SC(')'))),
                              K(US_SC(UP)), K(US_SC(DOWN)), K(US_SC('[')), K(US_SC(']')), HTA(L(VISIT, SYMB), K(US_SC('-'))),
        K(US_SC(R_ALT)), HTA(K(US_SC(R_CTRL)), K(US_SC(ESC))),
        K(US_SC(PG_UP)),
        K(US_SC(PG_DN)), HTA(L(VISIT, SYMB), K(US_SC(TAB))), K(US_SC(ENTER))
    ),
    [SYMB] = LAYER(
        NO_ACTION, K(US_SC(F1)), K(US_SC(F2)), K(US_SC(F3)), K(US_SC(F4)), K(US_SC(F5)), NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, L(GOTO, BASE),
        NO_ACTION, K(US_SC('1')), K(US_SC('2')), K(US_SC('3')), K(US_SC('4')), K(US_SC('5')),
        NO_ACTION, K(US_SC('6')), K(US_SC('7')), K(US_SC('8')), K(US_SC('9')), K(US_SC('0')), NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, K(US_SC(L_C(PG_UP))), K(US_SC(L_C(PG_DN))),
                                                               NO_ACTION, NO_ACTION,
                                                                          NO_ACTION,
                                                    NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, K(US_SC(F6)), K(US_SC(F7)), K(US_SC(F8)), K(US_SC(F9)), K(US_SC(F10)), K(US_SC(F11)),
        L(GOTO, BASE), NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, K(US_SC(F12)),
                   K(US_SC('&')), K(US_SC('_')), K(US_SC('-')), K(US_SC('p')), K(US_SC('+')), NO_ACTION,
        NO_ACTION, K(US_SC('|')), K(US_SC('@')), K(US_SC('=')), K(US_SC('%')), NO_ACTION, NO_ACTION,
                              NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION
    ),
    [MDIA] = LAYER(
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, K(US_SC(PG_UP)), K(US_SC(HOME)), K(US_SC(END)), K(US_SC(PG_DN)), NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                               NO_ACTION, NO_ACTION,
                                                                          NO_ACTION,
                                                    NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                   NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, M(0xCD),
        NO_ACTION, NO_ACTION, NO_ACTION, M(0xB6), M(0xB5), NO_ACTION, NO_ACTION,
                              M(0xE9), M(0xEA), M(0xE2), NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, M(0x0224)
    ),
);

LEADER_KEY_DICTIONARY(
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('w')),
        K(US_SC(L_A(F4)))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('o')),
        K(US_SC(L_C('O')))
    )
);
