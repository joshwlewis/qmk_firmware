#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default, base layer
#define SPCL 1 // special, secondary layer
#define XTRA 2 // extra,   trietary layer

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Layer 0: Base, default
/*
 * ,---------------------------------------------------.        ,---------------------------------------------------.
 * | `       | 1    | 2    | 3    | 4    | 5    | scr- |        | scr+ | 6    | 7    | 8    | 9    | 0    | pow     |
 * |---------+------+------+------+------+------+------|        |------+------+------+------+------+------+---------|
 * | tab     | q    | w    | e    | r    | t    | [    |        | ]    | y    | u    | i    | o    | p    | \       |
 * |---------+------+------+------+------+------|      |        |      |------+------+------+------+------+---------|
 * | cps/ctl | a    | s    | d    | f    | g    |------|        |------| h    | j    | k    | l    | ;    | '/ctl   |
 * |---------+------+------+------+------+------|  -   |        | =    |------+------+------+------+------+---------|
 * | shift   | z    | x    | c    | v    | b    |      |        |      | n    | m    | ,    | .    | /    | shift   |
 * `---------+------+------+------+------+-------------'        `-------------+------+------+------+------+---------'
 *     | esc | vol- | mute | vol+ | gui  |                                    | gui  | left | down | up   | rt  |
 *     `---------------------------------'                                    `---------------------------------'
 *                                       ,-------------.        ,-------------.
 *                                       | l1   | home |        | pgup | l1   |
 *                                ,------|------|------|        |------+------+------.
 *                                |      |      | end  |        | pgdn |      |      |
 *                                | spc  | back |------|        |------| ent  | spc  |
 *                                |      | spc  | alt  |        | alt  |      |      |
 *                                `--------------------'        `--------------------'
 */
[BASE] = KEYMAP(
       // left hand
       KC_GRV,         KC_1,     KC_2,    KC_3,    KC_4,    KC_5,     0x90,
       KC_TAB,         KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,     KC_LBRC,
       CTL_T(KC_CAPS), KC_A,     KC_S,    KC_D,    KC_F,    KC_G,
       KC_LSFT,        KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_MINS,
       KC_ESC,         KC_VOLD,  KC_MUTE, KC_VOLU, KC_LGUI,
                                                            MO(SPCL), KC_HOME,
                                                                      KC_END,
                                                   KC_BSPC, KC_DEL,   KC_LALT,
       // right hand
       0x91,           KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_PWR,
       KC_RBRC,        KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_BSLS,
                       KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,  CTL_T(KC_QUOT),
       KC_EQL,         KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                 KC_RGUI, KC_LEFT, KC_DOWN, KC_UP,    KC_RGHT,
       KC_PGUP,        MO(SPCL),
       KC_PGDN,
       KC_RALT,        KC_ENT,   KC_SPC
),

// Layer 1: Special, secondary
/*
 * ,--------------------------------------------------.         ,--------------------------------------------------.
 * | vrsn   | f1   | f2   | f3   | f4   | f5   |      |         |      | f6   | f7   | f8   | f9   | f10  | eprm   |
 * |--------+------+------+------+------+------+------|         |------+------+------+------+------+------+--------|
 * |        |      | up   |      |      |      | L1   |         | L1   |      |      | lclk | mup  | rclk |        |
 * |--------+------+------+------+------+------|      |         |      |------+------+------+------+------+--------|
 * |        | left | down | rght |      |      |------|         |------|      |      | mlft | mdn  | mrht |        |
 * |--------+------+------+------+------+------| L2   |         | L2   |------+------+------+------+------+--------|
 * |        | f11  | f12  | f13  | f14  | f15  |      |         |      | f16  | f17  | f18  | f19  | f20  |        |
 * `--------+------+------+------+------+-------------'         `-------------+------+------+------+------+--------'
 *    |     | prev | play | next |      |                                     |      |      |      |      |      |
 *    `---------------------------------'                                     `----------------------------------'
 *                                      ,-------------.         ,-------------.
 *                                      |      |      |         |      |      |
 *                               ,------|------|------|         |------+------+------.
 *                               |      |      |      |         |      |      |      |
 *                               |      |      |------|         |------|      |      |
 *                               |      |      |      |         |      |      |      |
 *                               `--------------------'         `--------------------'
 */
[SPCL] = KEYMAP(
       // left hand
       VRSN,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, TG(SPCL),
       KC_TRNS, KC_LEFT,  KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F11,   KC_F12,  KC_F13,  KC_F14,  KC_F15,  TG(XTRA),
       KC_TRNS, KC_MPRV,  KC_MPLY, KC_MNXT, KC_TRNS,
                                                     KC_TRNS, KC_TRNS,
                                                              KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS,  KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   EPRM,
       TG(SPCL), KC_TRNS,  KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2,  KC_TRNS,
                 KC_TRNS,  KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R,  KC_TRNS,
       TG(XTRA), KC_F16,   KC_F17,  KC_F18,  KC_F19,  KC_F20,   KC_TRNS,
                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS,  KC_TRNS,
       KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_TRNS
),

// Layer 2: Extra, trietary
/*
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[XTRA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
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
    [1] = ACTION_LAYER_TAP_TOGGLE(SPCL)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_led_all_on();
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
