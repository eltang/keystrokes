#include "layout.h"
#include "../ergodox.h"

LAYOUT {
    {
        { K(US, NP(TAB)), K(US, '\''), K(US, ','), K(US, '.'), K(US, 'p'), K(US, 'y'), K(US, 'f'), K(US, 'g'), K(US, 'c'), K(US, 'r'), K(US, 'l'), K(US, '/') },
        { K(US, NP(CAPS_LOCK)), K(US, 'a'), K(US, 'o'), K(US, 'e'), K(US, 'u'), K(US, 'i'), K(US, 'd'), K(US, 'h'), K(US, 't'), K(US, 'n'), K(US, 's'), K(US, '-') },
        { K(US, NP(L_SHIFT)), K(US, ';'), K(US, 'q'), K(US, 'j'), K(US, 'k'), K(US, 'x'), K(US, 'b'), K(US, 'm'), K(US, 'w'), K(US, 'v'), K(US, 'z'), K(US, NP(R_SHIFT)) },
        { RESET, NO_ACTION, K(US, NP(L_CTRL)), K(US, NP(L_ALT)), K(US, NP(L_GUI)), K(US, ' '), K(US, ' '), K(US, NP(R_GUI)), K(US, NP(R_ALT)), K(US, NP(R_CTRL)), NO_ACTION, NO_ACTION }
    }
#if 0
    LAYER(
        K(US, '`'), K(US, '1'), K(US, '2'), K(US, '3'), K(US, '4'), K(US, '5'), NO_ACTION,
        K(US, NP(TAB)), K(US, '\''), K(US, ','), K(US, '.'), K(US, 'p'), K(US, 'y'), K(US, '['),
        K(US, NP(CAPS_LOCK)), K(US, 'a'), K(US, 'o'), K(US, 'e'), K(US, 'u'), K(US, 'i'),
        K(US, NP(R_SHIFT)), K(US, ';'), K(US, 'q'), K(US, 'j'), K(US, 'k'), K(US, 'x'), NO_ACTION,
        NO_ACTION, NO_ACTION, K(US, NP(L_CTRL)), K(US, NP(L_ALT)), K(US, NP(L_GUI)),
                                                                K(US, NP(HOME)), K(US, NP(END)),
                                                                          K(US, NP(PG_UP)),
                                                     K(US, ' '), K(US, NP(BKSP)), K(US, NP(PG_DN)),

        K(US, '='), K(US, '6'), K(US, '7'), K(US, '8'), K(US, '9'), K(US, '0'), K(US, '\\'),
        K(US, ']'), K(US, 'f'), K(US, 'g'), K(US, 'c'), K(US, 'r'), K(US, 'l'), K(US, '/'),
                   K(US, 'd'), K(US, 'h'), K(US, 't'), K(US, 'n'), K(US, 's'), K(US, '-'),
        NO_ACTION, K(US, 'b'), K(US, 'm'), K(US, 'w'), K(US, 'v'), K(US, 'z'), K(US, NP(R_SHIFT)),
                                 K(US, NP(R_GUI)), K(US, NP(R_ALT)), K(US, NP(R_CTRL)), NO_ACTION, NO_ACTION,
        K(US, NP(LEFT)), K(US, NP(RIGHT)),
        K(US, NP(UP)),
        K(US, NP(DOWN)), K(US, NP(ENTER)), K(US, ' ')
    ),
    LAYER(
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                                NO_ACTION, NO_ACTION,
                                                                           NO_ACTION,
                                                     NO_ACTION, NO_ACTION, NO_ACTION,

        NO_ACTION, NO_ACTION, NO_ACTION, K(US, NK('1')), K(US, NK('1')), K(US, NK('1')), NO_ACTION,
        NO_ACTION, NO_ACTION, K(US, NK('7')), K(US, NK('8')), K(US, NK('9')), K(US, NK('+')), NO_ACTION,
                   NO_ACTION, K(US, NK('4')), K(US, NK('5')), K(US, NK('6')), K(US, NK('+')), NO_ACTION,
        NO_ACTION, NO_ACTION, K(US, NK('1')), K(US, NK('2')), K(US, NK('3')), K(US, NK(ENTER)), NO_ACTION,
                              NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION,
        NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION
    ),
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
    ),
#endif
};
