#include "layout.h"
#include "../ergodox.h"

/*
 * algernon's ErgoDox EZ layout, please see the readme.md file!
 */

/* Layers */

enum {
  BASE = 0,
  ADORE,
  ARRW,
  APPSEL,
  HUN,
  NMDIA,
  PLVR,
};

/* Macros */

#define HU_AA SA(SSA(K(US_SC('\'')), K(US_SC('\''))), K(US_SC('a')))
#define HU_OO SA(SSA(K(US_SC('\'')), K(US_SC('\''))), K(US_SC('o')))
#define HU_EE SA(SSA(K(US_SC('\'')), K(US_SC('\''))), K(US_SC('e')))
#define HU_UU SA(SSA(K(US_SC('\'')), K(US_SC('\''))), K(US_SC('u')))
#define HU_II SA(SSA(K(US_SC('\'')), K(US_SC('\''))), K(US_SC('i')))
#define HU_OE SA(SSA(K(US_SC('\"')), K(US_SC('\"'))), K(US_SC('o')))
#define HU_UE SA(SSA(K(US_SC('\"')), K(US_SC('\"'))), K(US_SC('u')))
#define HU_OEE SA(SSA(K(US_SC('=')), K(US_SC('='))), K(US_SC('o')))
#define HU_UEE SA(SSA(K(US_SC('=')), K(US_SC('='))), K(US_SC('u')))

#define APP_SLK SA(K(US_SC('s')), K(US_SC('l')), K(US_SC('a')), K(US_SC('c')), K(US_SC('k')), K(US_SC(ENTER)))
#define APP_EMCS SA(K(US_SC('g')), K(US_SC('n')), K(US_SC('u')), K(US_SC(' ')), K(US_SC('e')), K(US_SC('m')), K(US_SC('a')), K(US_SC('c')), K(US_SC('s')), K(US_SC(' ')), K(US_SC('2')), K(US_SC('4')), K(US_SC(ENTER)))
#define APP_TERM SA(K(US_SC('t')), K(US_SC('e')), K(US_SC('r')), K(US_SC('m')), K(US_SC('i')), K(US_SC('n')), K(US_SC('a')), K(US_SC('l')), K(US_SC(ENTER)))
#define APP_CHRM SA(K(US_SC('c')), K(US_SC('h')), K(US_SC('r')), K(US_SC('o')), K(US_SC('m')), K(US_SC(ENTER)))
#define APP_MSIC SA(K(US_SC('r')), K(US_SC('h')), K(US_SC('y')), K(US_SC('t')), K(US_SC('h')), K(US_SC('m')), K(US_SC('b')), K(US_SC('o')), K(US_SC('x')), K(US_SC(ENTER)))

#define PLOVER_TOGGLE NA(K(US_SC('e')), K(US_SC('r')), K(US_SC('f')), K(US_SC('v')), K(US_SC('o')), K(US_SC('l')))

#define Fx OSA(NA(L(VISIT, NMDIA), K(US_SC(L_ALT))))

#define A_9 SSA(K(US_SC('9')), NO_ACTION)
#define A_7 SSA(K(US_SC('7')), K(US_SC('@')))
#define A_5 SSA(K(US_SC('5')), K(US_SC('*')))
#define A_3 SSA(K(US_SC('3')), K(US_SC('^')))
#define A_1 SSA(K(US_SC('1')), K(US_SC('$')))
#define A_0 SSA(K(US_SC('0')), K(US_SC('%')))
#define A_2 SSA(K(US_SC('2')), K(US_SC('!')))
#define A_4 SSA(K(US_SC('4')), K(US_SC('#')))
#define A_6 SSA(K(US_SC('6')), K(US_SC('&')))
#define A_8 SSA(K(US_SC('8')), NO_ACTION)

#define CT_CLN TDA(K(US_SC(':')), K(US_SC(';')))
#define CT_TA ATDA(L(VISIT, ARRW), NO_ACTION, K(US_SC(TAB)), L(GOTO, ARRW))
#define CT_LBP TDA(K(US_SC('[')), K(US_SC('(')))
#define CT_RBP TDA(K(US_SC(']')), K(US_SC(')')))
#define CT_TMUX TDA(K(US_SC(L_A(' '))), K(US_SC(L_C('a'))))
#define CT_TPS TDA(SA(K(US_SC(L_A(' '))), K(US_SC('p'))), SA(K(US_SC(L_A(' '))), K(US_SC('p'))), SA(K(US_SC(L_A(' '))), K(US_SC('z'))))
#define CT_SR TDA(M(0xB7), NO_ACTION, NO_ACTION, RESET)

#define F_BSE L(GOTO, BASE)
#define F_HUN OSA(L(VISIT, HUN))
#define F_GUI TDA(K(US_SC(L_GUI)) ,SA(K(US_SC(L_G('w'))), OSA(L(VISIT, APPSEL))))
#define F_SFT OSA(K(US_SC(L_SHIFT)))
#define F_ALT OSA(K(US_SC(L_ALT)))
#define F_CTRL OSA(K(US_SC(L_CTRL)))

/* The Keymap */

LAYOUT(

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Next/Prev | 9    | 7  @ | 5  * | 3  ^ | 1  $ | F11  |           |  Fx  | 0  % | 2  ! | 4  # | 6  & | 8    |    Plover |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |         ~ |   '  |   ,  |   .  |   P  |   Y  |   (  |           |  )   |   F  |   G  |   C  |   R  |  L   | \         |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/ARROW |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   | = / Arrow |
 * |-----------+------+------+------+------+------| tmux |           | tmux |------+------+------+------+------+-----------|
 * | Play/Pause|   /  |   Q  |   J  |   K  |   X  |      |           | Pane |   B  |   M  |   W  |   V  |  Z   | Stop/Reset|
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |   :  |                                       |   -  |      |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | LEAD |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | HUN  |      |      |
 *                                  `--------------------'           `--------------------'
 */

[BASE] = LAYER(
// left hand
 SSA(M(0xB5) ,M(0xB6)) ,A_9 ,A_7 ,A_5 ,A_3 ,A_1 ,K(US_SC(F11))
,K(US_SC('`')) ,K(US_SC('\'')) ,K(US_SC(',')) ,K(US_SC('.')) ,K(US_SC('p')) ,K(US_SC('y')) ,CT_LBP
,CT_TA ,K(US_SC('a')) ,K(US_SC('o')) ,K(US_SC('e')) ,K(US_SC('u')) ,K(US_SC('i'))
,M(0xCD) ,K(US_SC('/')) ,K(US_SC('q')) ,K(US_SC('j')) ,K(US_SC('k')) ,K(US_SC('x')) ,CT_TMUX
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,CT_CLN
                                                      ,F_ALT ,F_GUI
                                                                 ,F_CTRL
                                           ,K(US_SC(BKSP)) ,F_SFT ,K(US_SC(ESC))

// right hand
,Fx ,A_0 ,A_2 ,A_4 ,A_6 ,A_8 ,NA(L(GOTO, PLVR), PLOVER_TOGGLE)
,CT_RBP ,K(US_SC('f')) ,K(US_SC('g')) ,K(US_SC('c')) ,K(US_SC('r')) ,K(US_SC('l')) ,K(US_SC('\\'))
           ,K(US_SC('d')) ,K(US_SC('h')) ,K(US_SC('t')) ,K(US_SC('n')) ,K(US_SC('s')) ,K(US_SC('='))
,CT_TPS ,K(US_SC('b')) ,K(US_SC('m')) ,K(US_SC('w')) ,K(US_SC('v')) ,K(US_SC('z')) ,CT_SR
                      ,K(US_SC('-')) ,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION
,OSA(L(VISIT, NMDIA)) ,K(US_SC(DELETE))
,LEADER_KEY
,F_HUN ,K(US_SC(ENTER)) ,K(US_SC(' '))
),

/* Keymap 1: Adore layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Play/Pause| 9    | 7  @ | 5  * | 3  ^ | 1  $ | F11  |           |  Fx  | 0  % | 2  ! | 4  # | 6  & | 8    |    Plover |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |         \ |   X  |   W  |   C  |   H  |   F  |   (  |           |  )   |   M  |   G  |   L  |   P  |  /   | `~        |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/Arrow |   A  |   O  |   E  |   I  |   U  |------|           |------|   D  |   R  |   T  |   N  |  S   | =         |
 * |-----------+------+------+------+------+------| tmux |           | tmux |------+------+------+------+------+-----------|
 * |           |   Z  |   Q  |   '  |   ,  |   .  |      |           | pane |   B  |   K  |   V  |   Y  |  J   |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |   :  |                                       |   -  |      |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | HUN  |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | LEAD |      |      |
 *                                  `--------------------'           `--------------------'
 */

[ADORE] = LAYER(
// left hand
 M(0xCD) ,A_9 ,A_7 ,A_5 ,A_3 ,A_1 ,K(US_SC(F11))
,K(US_SC('\\')) ,K(US_SC('x')) ,K(US_SC('w')) ,K(US_SC('c')) ,K(US_SC('h')) ,K(US_SC('f')) ,CT_LBP
,CT_TA ,K(US_SC('a')) ,K(US_SC('o')) ,K(US_SC('e')) ,K(US_SC('i')) ,K(US_SC('u'))
,NO_ACTION ,K(US_SC('z')) ,K(US_SC('q')) ,K(US_SC('\'')) ,K(US_SC(',')) ,K(US_SC('.')) ,CT_TMUX
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,CT_CLN
                                                      ,F_ALT ,F_GUI
                                                                 ,F_CTRL
                                           ,K(US_SC(BKSP)) ,F_SFT ,K(US_SC(ESC))

// right hand
,Fx ,A_0 ,A_2 ,A_4 ,A_6 ,A_8 ,NA(L(GOTO, PLVR), PLOVER_TOGGLE)
,CT_RBP ,K(US_SC('m')) ,K(US_SC('g')) ,K(US_SC('l')) ,K(US_SC('p')) ,K(US_SC('=')) ,K(US_SC('`'))
           ,K(US_SC('d')) ,K(US_SC('r')) ,K(US_SC('t')) ,K(US_SC('n')) ,K(US_SC('s')) ,K(US_SC('='))
,CT_TPS,K(US_SC('b')) ,K(US_SC('k')) ,K(US_SC('v')) ,K(US_SC('y')) ,K(US_SC('j')) ,NO_ACTION
                      ,K(US_SC('-')) ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,OSA(L(VISIT, NMDIA)) ,K(US_SC(DELETE))
,F_HUN
,LEADER_KEY ,K(US_SC(ENTER)) ,K(US_SC(' '))
),

/* Keymap 2: Arrow layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      | Home |  Up  |  End |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      | Left | Down | Rght |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  | Enter|      |------|           |------| PgUp | PgDn |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[ARRW] = LAYER(
// left hand
 NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,L(GOTO, BASE) ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                                                      ,NO_ACTION ,NO_ACTION
                                                                 ,NO_ACTION
                                           ,K(US_SC(ENTER)) ,NO_ACTION ,NO_ACTION

// right hand
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,K(US_SC(HOME)) ,K(US_SC(UP)) ,K(US_SC(END)) ,NO_ACTION ,NO_ACTION
           ,NO_ACTION ,K(US_SC(LEFT)) ,K(US_SC(DOWN)) ,K(US_SC(RIGHT)) ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                      ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION

,NO_ACTION ,NO_ACTION
,NO_ACTION
,NO_ACTION ,K(US_SC(PG_UP)) ,K(US_SC(PG_DN))
),

/* Keymap 3: Application select layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |Music |Slack |Emacs |Term  |Chrome|      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[APPSEL] = LAYER(
// left hand
 NO_ACTION ,APP_MSIC ,APP_SLK ,APP_EMCS ,APP_TERM ,APP_CHRM ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                                                      ,NO_ACTION ,NO_ACTION
                                                                 ,NO_ACTION
                                           ,NO_ACTION ,NO_ACTION ,NO_ACTION

// right hand
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
           ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                      ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION

,NO_ACTION ,NO_ACTION
,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION
),

/* Keymap 4: Hungarian Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |  Ő   |      |  Ű   |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   Á  |  Ó   |  É   |  Ú   |  Í   |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |  Ö   |      |  Ü   |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           | BASE |      |      |
 *                                  `--------------------'           `--------------------'
 */

[HUN] = LAYER(
// left hand
 NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION ,NO_ACTION,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,HU_OEE ,NO_ACTION ,HU_UEE ,NO_ACTION ,NO_ACTION
,NO_ACTION ,HU_AA ,HU_OO ,HU_EE ,HU_UU ,HU_II
,NO_ACTION ,NO_ACTION ,HU_OE ,NO_ACTION ,HU_UE ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION ,NO_ACTION
                                                      ,NO_ACTION ,NO_ACTION
                                                                 ,NO_ACTION
                                           ,NO_ACTION ,NO_ACTION ,NO_ACTION

// right hand
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
           ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                      ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION
,NO_ACTION
,F_BSE ,NO_ACTION ,NO_ACTION
),

/* Keymap 5: Navigation & Media layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F9  |  F7  |  F5  |  F3  |  F1  |ScrLCK|           |      | F10  |  F2  |  F4  |  F6  |  F8  |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Mute | VlUp |           | BASE |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | VlDn |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[NMDIA] = LAYER(
// left hand
 NO_ACTION ,K(US_SC(F9)) ,K(US_SC(F7)) ,K(US_SC(F5)) ,K(US_SC(F3)) ,K(US_SC(F1)) ,K(US_SC(L_G('l')))
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION
                                                      ,M(0xE2) ,M(0xE9)
                                                                 ,M(0xEA)
                                           ,NO_ACTION ,NO_ACTION ,NO_ACTION

// right hand
,NO_ACTION ,K(US_SC(F10)) ,K(US_SC(F2)) ,K(US_SC(F4)) ,K(US_SC(F6)) ,K(US_SC(F8)) ,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION
           ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION
                      ,NO_ACTION ,NO_ACTION ,NO_ACTION ,NO_ACTION,NO_ACTION
,NO_ACTION ,NO_ACTION
,NO_ACTION
,NO_ACTION ,NO_ACTION ,NO_ACTION
),

/* Keymap 6: Steno for Plover
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |  BASE  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   #  |   #  |   #  |   #  |   #  |   #  |           |  #   |  #   |  #   |   #  |   #  |  #   |   #    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   T  |   P  |   H  |      |------|           |------|      |  F   |   P  |   L  |  T   |   D    |
 * |--------+   S  +------+------+------+   *  |   *  |           |  *   |  *   +------+------+------+------+--------|
 * |        |      |   K  |   W  |   R  |      |      |           |      |      |  R   |   B  |   G  |  S   |   Z    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   A  |   O  |------|       |------|  E   |  U   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[PLVR] = LAYER(
// left hand
NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
NO_ACTION, K(US_SC('1')), K(US_SC('2')), K(US_SC('3')), K(US_SC('4')), K(US_SC('5')), K(US_SC('5')),
NO_ACTION, K(US_SC('q')), K(US_SC('w')), K(US_SC('e')), K(US_SC('r')), K(US_SC('t')),
NO_ACTION, K(US_SC('a')), K(US_SC('s')), K(US_SC('d')), K(US_SC('f')), K(US_SC('g')), K(US_SC('g')),
NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
                                                      NO_ACTION, NO_ACTION,
                                                                 NO_ACTION,
                                           K(US_SC('c')), K(US_SC('v')), NO_ACTION,

// right hand
NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NA(L(GOTO, BASE), PLOVER_TOGGLE),
K(US_SC('6')), K(US_SC('6')), K(US_SC('7')), K(US_SC('8')), K(US_SC('9')), K(US_SC('0')), K(US_SC('0')),
          K(US_SC('y')), K(US_SC('u')), K(US_SC('i')), K(US_SC('o')), K(US_SC('p')), K(US_SC('[')),
K(US_SC('h')), K(US_SC('h')), K(US_SC('j')), K(US_SC('k')), K(US_SC('l')), K(US_SC(';')), K(US_SC('\'')),
                  NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION,
NO_ACTION, NO_ACTION,
NO_ACTION,
NO_ACTION, K(US_SC('n')), K(US_SC('m'))
)

);

LEADER_KEY_DICTIONARY(
    LEADER_KEY_DICTIONARY_ENTRY(
         LEADER_KEY_SEQUENCE(US_SC('c')),
         SA(
             K(US_SC('C')), K(US_SC('s')), K(US_SC('i')), K(US_SC('l')), K(US_SC('l')), K(US_SC(R_ALT)), K(US_SC('\'')), K(US_SC('a')), K(US_SC('m')), K(US_SC('a')), K(US_SC('s')),
             K(US_SC('s')), K(US_SC('z')), K(US_SC('o')), K(US_SC('n')), K(US_SC('y')), K(US_SC('k')), K(US_SC(R_ALT)), K(US_SC('\'')), K(US_SC('a')), K(US_SC('m'))
         )
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('k')),
        SA(
            K(US_SC(' ')), K(US_SC('&')), K(US_SC(' ')),
            K(US_SC(L_C('U'))),
            K(US_SC('1')), K(US_SC('f')), K(US_SC('4')), K(US_SC('7')), K(US_SC('6')),
            K(US_SC(ENTER)),
            K(US_SC(ENTER)),
            K(US_SC(END)),
            K(US_SC(L_C('U'))),
            K(US_SC('1')), K(US_SC('f')), K(US_SC('4')), K(US_SC('7')), K(US_SC('6')),
            K(US_SC(' '))
        )
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('g')),
        SA(
            K(US_SC('G')), K(US_SC('e')), K(US_SC('j')), K(US_SC('g')), K(US_SC(R_ALT)), K(US_SC('=')), K(US_SC('o')),
            K(US_SC(R_ALT)), K(US_SC('=')), K(US_SC('o')),
            K(US_SC(R_ALT)), K(US_SC('=')), K(US_SC('o'))
        )
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('y')),
        SA(K(US_SC('\\')), K(US_SC('o')), K(US_SC('/')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('w'), US_SC('m')),
        SA(
            K(US_SC(L_A(F2))),
            K(US_SC('m')), K(US_SC('a')), K(US_SC('x')), K(US_SC('-')), K(US_SC('f')), K(US_SC('o')), K(US_SC('c')), K(US_SC('u')), K(US_SC('s')), K(US_SC('e')), K(US_SC('d')), K(US_SC(ENTER)),
            K(US_SC(L_G(UP)))
        )
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('a')),
        L(GOTO, ADORE)
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('l')),
        /* λ */
        SA(K(US_SC(L_C('U'))), K(US_SC('0')), K(US_SC('3')), K(US_SC('b')), K(US_SC('b')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('s')),
        SA(
            K(US_SC(L_C('U'))), K(US_SC('0')), K(US_SC('0')), K(US_SC('a')), K(US_SC('f')), K(US_SC(' ')),
            K(US_SC('\\')),
            K(US_SC('_')), K(US_SC('(')),
            K(US_SC(L_C('U'))), K(US_SC('3')), K(US_SC('0')), K(US_SC('c')), K(US_SC('4')), K(US_SC(' ')),
            K(US_SC(')')), K(US_SC('_')),
            K(US_SC('/')),
            K(US_SC(L_C('U'))), K(US_SC('0')), K(US_SC('0')), K(US_SC('a')), K(US_SC('f')), K(US_SC(' '))
        )
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('p'), US_SC('o'), US_SC('o'), US_SC('p')),
        SA(K(US_SC(L_C('U'))), K(US_SC('1')), K(US_SC('f')), K(US_SC('4')), K(US_SC('a')), K(US_SC('9')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('r'), US_SC('o'), US_SC('f'), US_SC('l')),
        SA(K(US_SC(L_C('U'))), K(US_SC('1')), K(US_SC('f')), K(US_SC('9')), K(US_SC('2')), K(US_SC('3')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('k'), US_SC('i'), US_SC('s'), US_SC('s')),
        SA(K(US_SC(L_C('U'))), K(US_SC('1')), K(US_SC('f')), K(US_SC('6')), K(US_SC('1')), K(US_SC('9')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('s'), US_SC('n'), US_SC('o'), US_SC('w'), US_SC('m'), US_SC('a'), US_SC('n')),
        SA(K(US_SC(L_C('U'))), K(US_SC('2')), K(US_SC('6')), K(US_SC('0')), K(US_SC('3')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('c'), US_SC('o'), US_SC('f'), US_SC('f'), US_SC('e'), US_SC('e')),
        SA(K(US_SC(L_C('U'))), K(US_SC('2')), K(US_SC('6')), K(US_SC('1')), K(US_SC('5')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('h'), US_SC('e'), US_SC('a'), US_SC('r'), US_SC('t')),
        SA(K(US_SC(L_C('U'))), K(US_SC('2')), K(US_SC('7')), K(US_SC('6')), K(US_SC('4')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('b'), US_SC('o'), US_SC('l'), US_SC('t')),
        SA(K(US_SC(L_C('U'))), K(US_SC('2')), K(US_SC('6')), K(US_SC('a')), K(US_SC('1')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('p'), US_SC('i')),
        SA(K(US_SC(L_C('U'))), K(US_SC('0')), K(US_SC('3')), K(US_SC('c')), K(US_SC('0')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('m'), US_SC('o'), US_SC('u'), US_SC('s'), US_SC('e')),
        SA(K(US_SC(L_C('U'))), K(US_SC('1')), K(US_SC('f')), K(US_SC('4')), K(US_SC('0')), K(US_SC('1')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('m'), US_SC('i'), US_SC('c'), US_SC('r'), US_SC('o')),
        SA(K(US_SC(L_C('U'))), K(US_SC('0')), K(US_SC('0')), K(US_SC('b')), K(US_SC('5')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('t'), US_SC('m')),
        SA(K(US_SC(L_C('U'))), K(US_SC('2')), K(US_SC('1')), K(US_SC('2')), K(US_SC('2')), K(US_SC(' ')))
    ),
    LEADER_KEY_DICTIONARY_ENTRY(
        LEADER_KEY_SEQUENCE(US_SC('c'), US_SC('h'), US_SC('i'), US_SC('l'), US_SC('d')),
        SA(K(US_SC(L_C('U'))), K(US_SC('1')), K(US_SC('f')), K(US_SC('4')), K(US_SC('7')), K(US_SC('6')), K(US_SC(' ')))
    )
);
