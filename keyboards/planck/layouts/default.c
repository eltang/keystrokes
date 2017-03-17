#include "layout.h"

LAYOUT(
    {
        K(US_SC(TAB)), K(US_SC('q')), K(US_SC('w')), K(US_SC('e')), K(US_SC('r')), K(US_SC('t')), K(US_SC('y')), K(US_SC('u')), K(US_SC('i')), K(US_SC('o')), K(US_SC('p')), K(US_SC(BKSP)),
        K(US_SC(ESC)), TD(K(US_SC('a')), K(US_SC('q'))), K(US_SC('s')), K(US_SC('d')), TH(K(US_SC('f')), K(US_SC(R_ALT))), K(US_SC('g')), K(US_SC('h')), TH(K(US_SC('j')), K(US_SC(R_ALT))), K(US_SC('k')), K(US_SC('l')), TD(K(US_SC(';')), K(US_SC('p'))), K(US_SC('\'')),
        HT(K(US_SC(L_SHIFT)), K(US_SC('('))), K(US_SC('z')), K(US_SC('x')), K(US_SC('c')), K(US_SC('v')), K(US_SC('b')), K(US_SC('n')), K(US_SC('m')), K(US_SC(',')), K(US_SC('.')), K(US_SC('/')), HT(K(US_SC(R_SHIFT)), K(US_SC(ENTER))),
        LEADER_KEY, K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)), L(VISIT, 1), K(US_SC(' ')), K(US_SC(' ')), L(VISIT, 2), MA(K(US_SC('a')), K(US_SC('b'))), HT(K(US_SC(R_SHIFT)), TD(K(US_SC('a')), K(US_SC('b')))), OS(K(US_SC(R_ALT))), HT(K(US_SC(R_GUI)), TD(NO_ACTION, OS(K(US_SC(R_SHIFT)))))
    },
    {
        K(US_SC('~')), K(US_SC('!')), K(US_SC('@')), K(US_SC('#')), K(US_SC('$')), K(US_SC('%')), K(US_SC('^')), K(US_SC('&')), K(US_SC('*')), K(US_SC('(')), K(US_SC(')')), K(US_SC(BKSP)),
        K(US_SC(DELETE)), K(US_SC(F1)), K(US_SC(F2)), K(US_SC(F3)), K(US_SC(F4)), K(US_SC(F5)), K(US_SC(F6)), K(US_SC('_')), K(US_SC('+')), K(US_SC('{')), K(US_SC('}')), K(US_SC('|')),
        K(US_SC(L_SHIFT)), K(US_SC(F7)), K(US_SC(F8)), K(US_SC(F9)), K(US_SC(F10)), K(US_SC(F11)), K(US_SC(F12)), NO_ACTION, NO_ACTION, K(US_SC(HOME)), K(US_SC(END)), K(US_SC(ENTER)),
        RESET, K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)), L(VISIT, 1), K(US_SC(' ')), K(US_SC(' ')), L(VISIT, 2), OS(K(US_SC(R_CTRL))), OS(K(US_SC(R_SHIFT))), OS(K(US_SC(R_ALT))), OS(K(US_SC(R_GUI)))
    },
    {
        K(US_SC('`')), K(US_SC('1')), K(US_SC('2')), K(US_SC('3')), K(US_SC('4')), K(US_SC('5')), K(US_SC('6')), K(US_SC('7')), K(US_SC('8')), K(US_SC('9')), K(US_SC('0')), K(US_SC(BKSP)),
        K(US_SC(DELETE)), TD(K(US_SC(F1)), K(US_SC('q'))), K(US_SC(F2)), K(US_SC(F3)), K(US_SC(F4)), K(US_SC(F5)), K(US_SC(F6)), K(US_SC('-')), K(US_SC('=')), K(US_SC('[')), K(US_SC(']')), K(US_SC('\\')),
        K(US_SC(L_SHIFT)), K(US_SC(F7)), K(US_SC(F8)), K(US_SC(F9)), K(US_SC(F10)), K(US_SC(F11)), K(US_SC(F12)), NO_ACTION, NO_ACTION, K(US_SC(PG_UP)), K(US_SC(PG_DN)), K(US_SC(ENTER)),
        PM(0x81), K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)), L(VISIT, 1), K(US_SC(' ')), K(US_SC(' ')), L(VISIT, 2), M(0xB5), M(0xEA), M(0xE9), M(0xCD)
    }
);

LEADER_KEY_DICTIONARY(
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('w'), 0, 0, 0),
        K(US_SC(L_A(F4)))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('o'), 0, 0, 0),
        K(US_SC(L_C('O')))
    )
);
