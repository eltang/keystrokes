#include "layout.h"

LAYOUT(
    {
        K(SC(US, TAB)), K(SC(US, 'q')), K(SC(US, 'w')), K(SC(US, 'e')), K(SC(US, 'r')), K(SC(US, 't')), K(SC(US, 'y')), K(SC(US, 'u')), K(SC(US, 'i')), K(SC(US, 'o')), K(SC(US, 'p')), K(SC(US, BKSP)),
        K(SC(US, ESC)), TD(K(SC(US, 'a')), K(SC(US, 'q'))), K(SC(US, 's')), K(SC(US, 'd')), TH(K(SC(US, 'f')), K(SC(US, R_ALT))), K(SC(US, 'g')), K(SC(US, 'h')), TH(K(SC(US, 'j')), K(SC(US, R_ALT))), K(SC(US, 'k')), K(SC(US, 'l')), TD(K(SC(US, ';')), K(SC(US, 'p'))), K(SC(US, '\'')),
        HT(K(SC(US, L_SHIFT)), K(SC(US, '('))), K(SC(US, 'z')), K(SC(US, 'x')), K(SC(US, 'c')), K(SC(US, 'v')), K(SC(US, 'b')), K(SC(US, 'n')), K(SC(US, 'm')), K(SC(US, ',')), K(SC(US, '.')), K(SC(US, '/')), K(SC(US, ENTER)),
        LEADER_KEY, K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)), L(VISIT, 1), K(SC(US, ' ')), K(SC(US, ' ')), L(VISIT, 2), K(SC(US, LEFT)), K(SC(US, DOWN)), K(SC(US, UP)), K(SC(US, RIGHT))
    },
    {
        K(SC(US, '~')), K(SC(US, '!')), K(SC(US, '@')), K(SC(US, '#')), K(SC(US, '$')), K(SC(US, '%')), K(SC(US, '^')), K(SC(US, '&')), K(SC(US, '*')), K(SC(US, '(')), K(SC(US, ')')), K(SC(US, BKSP)),
        K(SC(US, DELETE)), K(SC(US, F1)), K(SC(US, F2)), K(SC(US, F3)), K(SC(US, F4)), K(SC(US, F5)), K(SC(US, F6)), K(SC(US, '_')), K(SC(US, '+')), K(SC(US, '{')), K(SC(US, '}')), K(SC(US, '|')),
        K(SC(US, L_SHIFT)), K(SC(US, F7)), K(SC(US, F8)), K(SC(US, F9)), K(SC(US, F10)), K(SC(US, F11)), K(SC(US, F12)), NO_ACTION, NO_ACTION, K(SC(US, HOME)), K(SC(US, END)), K(SC(US, ENTER)),
        RESET, K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)), L(VISIT, 1), K(SC(US, ' ')), K(SC(US, ' ')), L(VISIT, 2), M(0xB5), M(0xEA), M(0xE9), M(0xCD)
    },
    {
        K(SC(US, '`')), K(SC(US, '1')), K(SC(US, '2')), K(SC(US, '3')), K(SC(US, '4')), K(SC(US, '5')), K(SC(US, '6')), K(SC(US, '7')), K(SC(US, '8')), K(SC(US, '9')), K(SC(US, '0')), K(SC(US, BKSP)),
        K(SC(US, DELETE)), TD(K(SC(US, F1)), K(SC(US, 'q'))), K(SC(US, F2)), K(SC(US, F3)), K(SC(US, F4)), K(SC(US, F5)), K(SC(US, F6)), K(SC(US, '-')), K(SC(US, '=')), K(SC(US, '[')), K(SC(US, ']')), K(SC(US, '\\')),
        K(SC(US, L_SHIFT)), K(SC(US, F7)), K(SC(US, F8)), K(SC(US, F9)), K(SC(US, F10)), K(SC(US, F11)), K(SC(US, F12)), NO_ACTION, NO_ACTION, K(SC(US, PG_UP)), K(SC(US, PG_DN)), K(SC(US, ENTER)),
        PM(0x81), K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)), L(VISIT, 1), K(SC(US, ' ')), K(SC(US, ' ')), L(VISIT, 2), M(0xB5), M(0xEA), M(0xE9), M(0xCD)
    }
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
