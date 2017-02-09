#include "layout.h"
#include "../ergodox.h"

LAYOUT(
    LAYER(
        K(SC(US, '`')), K(SC(US, '1')), K(SC(US, '2')), K(SC(US, '3')), K(SC(US, '4')), K(SC(US, '5')), NO_ACTION,
        K(SC(US, TAB)), K(SC(US, '\'')), K(SC(US, ',')), K(SC(US, '.')), K(SC(US, 'p')), K(SC(US, 'y')), K(SC(US, '[')),
        K(SC(US, CAPS_LOCK)), K(SC(US, 'a')), K(SC(US, 'o')), K(SC(US, 'e')), K(SC(US, 'u')), K(SC(US, 'i')),
        K(SC(US, L_SHIFT)), K(SC(US, ';')), K(SC(US, 'q')), K(SC(US, 'j')), K(SC(US, 'k')), K(SC(US, 'x')), NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, L_CTRL)), K(SC(US, L_ALT)), K(SC(US, L_GUI)),
                                                                K(SC(US, HOME)), K(SC(US, END)),
                                                                          K(SC(US, PG_UP)),
                                                     K(SC(US, ' ')), K(SC(US, BKSP)), K(SC(US, PG_DN)),

        K(SC(US, '=')), K(SC(US, '6')), K(SC(US, '7')), K(SC(US, '8')), K(SC(US, '9')), K(SC(US, '0')), K(SC(US, '\\')),
        K(SC(US, ']')), K(SC(US, 'f')), K(SC(US, 'g')), K(SC(US, 'c')), K(SC(US, 'r')), K(SC(US, 'l')), K(SC(US, '/')),
                   K(SC(US, 'd')), K(SC(US, 'h')), K(SC(US, 't')), K(SC(US, 'n')), K(SC(US, 's')), K(SC(US, '-')),
        NO_ACTION, K(SC(US, 'b')), K(SC(US, 'm')), K(SC(US, 'w')), K(SC(US, 'v')), K(SC(US, 'z')), K(SC(US, R_SHIFT)),
                                 K(SC(US, R_GUI)), K(SC(US, R_ALT)), K(SC(US, R_CTRL)), NO_ACTION, NO_ACTION,
        K(SC(US, LEFT)), K(SC(US, RIGHT)),
        K(SC(US, UP)),
        K(SC(US, DOWN)), K(SC(US, ENTER)), K(SC(US, ' '))
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

        NO_ACTION, NO_ACTION, NO_ACTION, K(SC(US, NK(SC('1'))), K(SC(US, NK(SC('1'))), K(SC(US, NK(SC('1'))), NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, NK(SC('7'))), K(SC(US, NK(SC('8'))), K(SC(US, NK(SC('9'))), K(SC(US, NK(SC('+'))), NO_ACTION,
                   NO_ACTION, K(SC(US, NK(SC('4'))), K(SC(US, NK(SC('5'))), K(SC(US, NK(SC('6'))), K(SC(US, NK(SC('+'))), NO_ACTION,
        NO_ACTION, NO_ACTION, K(SC(US, NK(SC('1'))), K(SC(US, NK(SC('2'))), K(SC(US, NK(SC('3'))), K(SC(US, NK(SC(ENTER))), NO_ACTION,
                              NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION
    )),
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
