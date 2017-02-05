#include "layout.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

LAYOUT(
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |Ctrl- |           | Ctrl+|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  | Alt/J|   K  |   L  |; / L2| LGui/' |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * |LShift/(|Z/Ctrl|   X  |   C  |   V  |   B  |   [  |           |  ]   |   N  |   M  |   ,  |   .  |//Ctrl|RShift/)|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | -/L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Leader|------|       |------| Tab/L1 |Enter |
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,     KC_5,   LCTL(KC_MINS),
        KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,     KC_T,   TG(SYMB),
        KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,     KC_G,
        KC_LSPO,       CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,     KC_B,   ALL_T(KC_LBRC),
        LT(SYMB,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,  KC_RGHT,
                                              ALT_T(KC_APP),    KC_LGUI,
                                                                KC_HOME,
                                                 KC_SPC,KC_LEAD,KC_END,
        // right hand
             LCTL(KC_EQL),       KC_6,KC_7,       KC_8,   KC_9,   KC_0,            KC_MINS,
             TG(SYMB),      KC_Y,KC_U,       KC_I,   KC_O,   KC_P,            KC_BSLS,
                            KC_H,ALT_T(KC_J),KC_K,   KC_L,   LT(MDIA,KC_SCLN),GUI_T(KC_QUOT),
             MEH_T(KC_RBRC),KC_N,KC_M,       KC_COMM,KC_DOT, CTL_T(KC_SLSH),  KC_RSPC,
                            KC_UP,           KC_DOWN,KC_LBRC,KC_RBRC,         LT(SYMB,KC_MINS),
             KC_LALT,       CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,LT(SYMB, KC_TAB), KC_ENT
    ),


K(SC(US, NP(TAB))), K(SC(US, '\'')), K(SC(US, ',')), K(SC(US, '.')), K(SC(US, 'p')), K(SC(US, 'y')), K(SC(US, 'f')), K(SC(US, 'g')), K(SC(US, 'c')), K(SC(US, 'r')), K(SC(US, 'l')), K(SC(US, '/'))
K(SC(US, NP(CAPS_LOCK))), K(SC(US, 'a')), K(SC(US, 'o')), K(SC(US, 'e')), K(SC(US, 'u')), K(SC(US, 'i')), K(SC(US, 'd')), K(SC(US, 'h')), K(SC(US, 't')), K(SC(US, 'n')), K(SC(US, 's')), K(SC(US, '-'))
K(SC(US, NP(L_SHIFT))), K(SC(US, ';')), K(SC(US, 'q')), K(SC(US, 'j')), K(SC(US, 'k')), K(SC(US, 'x')), K(SC(US, 'b')), K(SC(US, 'm')), K(SC(US, 'w')), K(SC(US, 'v')), K(SC(US, 'z')), K(SC(US, NP(R_SHIFT)))
RESET, NO_ACTION, K(SC(US, NP(L_CTRL))), K(SC(US, NP(L_ALT))), K(SC(US, NP(L_GUI))), K(SC(US, ' ')), K(SC(US, ' ')), K(SC(US, NP(R_GUI))), K(SC(US, NP(R_ALT))), K(SC(US, NP(R_CTRL))), NO_ACTION, NO_ACTION

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |------|           |------|   &  |   _  |   -  |   ;  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   0  |      |           |      |   |  |   @  |   =  |   %  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |NxtTab|PrvTab|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |TOG   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |VAI   |VAD   |HUI   |       |SAI   |      |MOD   |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |HUD   |       |SAD   |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       RGB_FF00BB, KC_F1,  KC_F2,  KC_F3,      KC_F4,        KC_F5,   KC_TRNS,
       KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,       KC_TRNS,      KC_TRNS, KC_TRNS,
       KC_TRNS, KC_1,   KC_2,   KC_3,          KC_4,         KC_5,
       KC_TRNS, KC_6,   KC_7,   KC_8,          KC_9,         KC_0,    KC_TRNS,
       KC_TRNS, KC_TRNS,KC_TRNS,LCTL(KC_PGUP), LCTL(KC_PGDN),
                                                                              KC_TRNS,KC_TRNS,
                                                                                      RGB_HUI,
                                                                      RGB_VAI,RGB_VAD,RGB_HUD,
               // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
                KC_AMPR, KC_UNDS, KC_MINS, CM_SCLN, KC_PLUS, KC_TRNS,
       KC_TRNS, KC_PIPE, KC_AT,   KC_EQL,  KC_PERC,   KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       RGB_TOG, KC_TRNS,
       RGB_SAI,
       RGB_SAD, KC_TRNS, RGB_MOD
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | PgUp | Home | End  | PgDn |      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_HOME, KC_END,  KC_PGDN, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),               // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_MACRO_TAP(0),                         // Eric Tang's Famous Macro!
    [3] = ACTION_MACRO_TAP(1)                          // Eric Tang's Famous Macro!
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case RGB_FF00BB:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0xff,0x00,0xbb);
        #endif
      }
      return false;
      break;
  }
  return true;
}





// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    default:
      // none
      break;
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_W) {
      register_code(KC_LALT);
      register_code(KC_F4);
      unregister_code(KC_F4);
      unregister_code(KC_LALT);
    }
    SEQ_ONE_KEY(KC_O) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_O);
      unregister_code(KC_O);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    }
  }
}
