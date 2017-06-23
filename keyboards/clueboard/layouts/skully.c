#include "../clueboard.h"
#include "layout.h"

enum {
    _BL,
    _FL,
    _CL
};

LAYOUT(
    // Layer _BL: Base Layer (Default Layer)
    [_BL] = LAYER(
        SSA(K(US_SC(ESC)), K(US_SC('`'))),    K(US_SC('1')),   K(US_SC('2')),   K(US_SC('3')), K(US_SC('4')), K(US_SC('5')), K(US_SC('6')), K(US_SC('7')), K(US_SC('8')), K(US_SC('9')), K(US_SC('0')),   K(US_SC('-')),   K(US_SC('=')),    K(US_SC('`')),     K(US_SC(BKSP)), K(US_SC(PG_UP)),
        K(US_SC(TAB)),                        K(US_SC('q')),   K(US_SC('w')),   K(US_SC('e')), K(US_SC('r')), K(US_SC('t')), K(US_SC('y')), K(US_SC('u')), K(US_SC('i')), K(US_SC('o')), K(US_SC('p')),   K(US_SC('[')),   K(US_SC(']')),    K(US_SC('\\')),                    K(US_SC(PG_DN)),
        K(US_SC(L_CTRL)),                     K(US_SC('a')),   K(US_SC('s')),   K(US_SC('d')), K(US_SC('f')), K(US_SC('g')), K(US_SC('h')), K(US_SC('j')), K(US_SC('k')), K(US_SC('l')), K(US_SC(';')),   K(US_SC('\'')),  K(0x32),          K(US_SC(ENTER)),
        NA(K(US_SC(L_SHIFT)), L(VISIT, _FL)), K(0x64),         K(US_SC('z')),   K(US_SC('x')), K(US_SC('c')), K(US_SC('v')), K(US_SC('b')), K(US_SC('n')), K(US_SC('m')), K(US_SC(',')), K(US_SC('.')),   K(US_SC('/')),   K(0x87),          K(US_SC(R_SHIFT)), K(US_SC(UP)),
        K(US_SC(L_CTRL)),                     K(US_SC(L_ALT)), K(US_SC(L_GUI)), K(0x8B),                      K(US_SC(' ')), K(US_SC(' ')),                K(0x8A),                      K(US_SC(R_GUI)), K(US_SC(R_ALT)), K(US_SC(R_CTRL)), K(US_SC(LEFT)),    K(US_SC(DOWN)), K(US_SC(RIGHT))
    ),
    // Layer _FL: Function Layer
    [_FL] = LAYER(
        K(US_SC('`')),    K(US_SC(F1)),    K(US_SC(F2)),    K(US_SC(F3)),  K(US_SC(F4)),  K(US_SC(F5)),  K(US_SC(F6)),  K(US_SC(F7)),  K(US_SC(F8)),  K(US_SC(F9)),  K(US_SC(F10)),   K(US_SC(F11)),   K(US_SC(F12)),    K(US_SC('`')),     K(US_SC(DELETE)), NO_ACTION,
        K(US_SC(TAB)),    K(US_SC('q')),   K(US_SC('w')),   K(US_SC('e')), K(US_SC('r')), K(US_SC('t')), K(US_SC('y')), K(US_SC('u')), K(US_SC('i')), K(US_SC('o')), K(US_SC('p')),   K(US_SC('[')),   K(US_SC(']')),    K(US_SC('\\')),                      K(US_SC(PG_DN)),
        K(US_SC(L_CTRL)), K(US_SC('a')),   L(VISIT, _CL),   K(US_SC('d')), K(US_SC('f')), K(US_SC('g')), K(US_SC('h')), K(US_SC('j')), K(US_SC('k')), K(US_SC('l')), K(US_SC(';')),   K(US_SC('\'')),  K(0x32),          K(US_SC(ENTER)),
        NO_ACTION,        K(0x64),         K(US_SC('z')),   K(US_SC('x')), K(US_SC('c')), K(US_SC('v')), K(US_SC('b')), K(US_SC('n')), K(US_SC('m')), K(US_SC(',')), K(US_SC('.')),   K(US_SC('/')),   K(0x87),          K(US_SC(R_SHIFT)), K(US_SC(PG_UP)),
        K(US_SC(L_CTRL)), K(US_SC(L_ALT)), K(US_SC(L_GUI)), K(0x8B),                      K(US_SC(' ')), K(US_SC(' ')),                K(0x8A),                      K(US_SC(R_GUI)), K(US_SC(R_ALT)), K(US_SC(R_CTRL)), K(US_SC(HOME)),    K(US_SC(PG_DN)),  K(US_SC(END))
    ),
    // Layer _CL: Control layer
    [_CL] = LAYER(
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, RESET,     NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,            NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
        NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,            NO_ACTION, NO_ACTION,            NO_ACTION,            NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION
    )
);
