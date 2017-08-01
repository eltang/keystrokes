#include "layout.h"
#include "../ergodox.h"

LAYOUT(
    LAYER(
        NO_ACTION, K(US_SC('7')), K(US_SC('5')), K(US_SC('3')), K(US_SC('1')), K(US_SC('9')), K(US_SC('`')),
        K(US_SC(ESC)), K(US_SC('\'')), K(US_SC(',')), K(US_SC('.')), K(US_SC('p')), K(US_SC('y')), K(US_SC('[')),
        K(US_SC(TAB)), K(US_SC('a')), K(US_SC('o')), K(US_SC('e')), K(US_SC('u')), K(US_SC('i')),
        K(US_SC(CAPS_LOCK)), K(US_SC(';')), K(US_SC('q')), K(US_SC('j')), K(US_SC('k')), K(US_SC('x')), L(GOTO, 1),
        NO_ACTION, K(US_SC(L_SHIFT)), K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)),
                                                               K(US_SC(HOME)), K(US_SC(END)),
                                                                          K(US_SC(PG_UP)),
                                                    K(US_SC(' ')), K(US_SC(BKSP)), K(US_SC(PG_DN)),
        K(US_SC('\\')), K(US_SC('0')), K(US_SC('2')), K(US_SC('4')), K(US_SC('6')), K(US_SC('8')), NO_ACTION,
        K(US_SC(']')), K(US_SC('f')), K(US_SC('g')), K(US_SC('c')), K(US_SC('r')), K(US_SC('l')), K(US_SC('=')),
                   K(US_SC('d')), K(US_SC('h')), K(US_SC('t')), K(US_SC('n')), K(US_SC('s')), K(US_SC('/')),
        NO_ACTION, K(US_SC('b')), K(US_SC('m')), K(US_SC('w')), K(US_SC('v')), K(US_SC('z')), K(US_SC('-')),
                              K(US_SC(R_GUI)), K(US_SC(R_ALT)),K(US_SC(R_CTRL)), K(US_SC(R_SHIFT)), NO_ACTION,
        M(0xE2), PM(0x81),
        M(0xE9),
        M(0xEA), K(US_SC(ENTER)), K(US_SC(' '))
    ),
    LAYER(
        NO_ACTION, K(US_SC(F11)), K(US_SC(F12)), K(US_SC(F13)), K(US_SC(F14)), K(US_SC(F15)), NO_ACTION,
        NO_ACTION, K(US_SC(F6)), K(US_SC(F7)), K(US_SC(F8)), K(US_SC(F9)), K(US_SC(F10)), NO_ACTION,
        NO_ACTION, K(US_SC(F1)), K(US_SC(F2)), K(US_SC(F3)), K(US_SC(F4)), K(US_SC(F5)),
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, L(GOTO, 2),
        NO_ACTION, K(US_SC(L_SHIFT)), K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)),
                                                               NO_ACTION, NO_ACTION,
                                                                          NO_ACTION,
                                                    NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, K(US_SC(UP)), NO_ACTION, NO_ACTION, NO_ACTION,
                   NO_ACTION, K(US_SC(LEFT)), K(US_SC(DOWN)), K(US_SC(RIGHT)), NO_ACTION, NO_ACTION,
        L(GOTO, 0), NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                              K(US_SC(R_GUI)), K(US_SC(R_ALT)), K(US_SC(R_CTRL)), K(US_SC(R_SHIFT)), NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION,  NO_ACTION
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
        NO_ACTION, NO_ACTION, K(US_SC(NUM_LOCK)), K(US_SC(NK('/'))), K(US_SC(NK('*'))), K(US_SC(NK('-'))), NO_ACTION,
        NO_ACTION, NO_ACTION, K(US_SC(NK('7'))), K(US_SC(NK('8'))), K(US_SC(NK('9'))), K(US_SC(NK('+'))), NO_ACTION,
                   NO_ACTION, K(US_SC(NK('4'))), K(US_SC(NK('5'))), K(US_SC(NK('6'))), K(US_SC(NK('+'))), NO_ACTION,
        L(GOTO, 0), NO_ACTION, K(US_SC(NK('1'))), K(US_SC(NK('2'))), K(US_SC(NK('3'))), K(US_SC(NK(ENTER))), NO_ACTION,
                              K(US_SC(NK('0'))), K(US_SC(NK('0'))), K(US_SC(NK('.'))), K(US_SC(NK(ENTER))), NO_ACTION,
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
