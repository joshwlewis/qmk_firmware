#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define QWER 0 // qwerty
#define DVOR 1 // dvorak
#define SPCL 2 // symbols

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWER] = LAYOUT_ergodox(
  // left
  KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_F11,
  KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_LBRC,
  KC_LCTL,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
  KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_MINS,
  KC_ESC,         KC_INS,         KC_LALT,        MO(SPCL),       KC_LGUI,
                                                                                  KC_PAUSE,       KC_SLCK,
                                                                                                  KC_HOME,
                                                                  KC_BSPC,        KC_DELT,        KC_END,
  // right
  LT(SPCL,KC_F12),KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_EQL,
  ALL_T(KC_RBRC), KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           ALT_T(KC_BSLS),
                  KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        CTL_T(KC_QUOT),
  MEH_T(KC_EQL),  KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLSH,        SFT_T(KC_MINS),
                                  KC_RGUI,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,
  KC_MENU,        KC_APP,
  KC_PGUP,
  KC_PGDN,        KC_ENT,         KC_SPC
),

[DVOR] = LAYOUT_ergodox(
  // left
  KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_F11,
  KC_TAB,         KC_QUOT,        KC_COMM,        KC_DOT,         KC_P,           KC_Y,           KC_LBRC,
  KC_LCTL,        KC_A,           KC_O,           KC_E,           KC_U,           KC_I,
  KC_LSFT,        KC_SCLN,        KC_Q,           KC_J,           KC_K,           KC_X,           KC_MINS,
  KC_ESC,         KC_INS,         KC_LALT,        MO(SPCL),       KC_LGUI,
                                                                                  KC_PAUSE,       KC_SLCK,
                                                                                                  KC_HOME,
                                                                  KC_BSPC,        KC_DELT,        KC_END,
  // right
  LT(SPCL,KC_F12),KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_EQL,
  ALL_T(KC_RBRC), KC_F,           KC_G,           KC_C,           KC_R,           KC_L,           ALT_T(KC_SLSH),
                  KC_D,           KC_H,           KC_T,           KC_N,           KC_S,           CTL_T(KC_MINS),
  MEH_T(KC_EQL),  KC_B,           KC_M,           KC_W,           KC_V,           KC_Z,           SFT_T(KC_BSLS),
                                  KC_RGUI,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,
  KC_MENU,        KC_APP,
  KC_PGUP,
  KC_PGDN,        KC_ENT,         KC_SPC
),


[SPCL] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRNS,
  KC_TRNS,        KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        TG(DVOR),
  KC_TRNS,        KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRV,
  KC_TRNS,        KC_PERC,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,        EPRM,
  KC_TRNS,        KC_MUTE,        KC_TRNS,        KC_TRNS,        KC_TRNS,
                                                                                  KC_MUTE,        BL_INC,
                                                                                                  BL_TOGG,
                                                                  KC_VOLD,        KC_VOLU,        BL_DEC,
  // right hand
  KC_TRNS,        KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_POWER,
  TG(DVOR),       KC_P7,          KC_P8,          KC_P9,          KC_PPLS,        KC_PSLS,        KC_PWR,
                  KC_P4,          KC_P5,          KC_P6,          KC_PPLS,        KC_PAST,        KC_WAKE,
  EPRM,           KC_P1,          KC_P2,          KC_P3,          KC_PENT,        KC_PMNS,        KC_EJCT,
                                  KC_PDOT,        KC_P0,          KC_PENT,        KC_TRNS,        VRSN,
  BL_INC,         KC_MPLY,
  BL_TOGG,
  BL_DEC,         KC_MRWD,        KC_MFFD
),
};

const uint16_t PROGMEM fn_actions[] = {
    // FN1 - Momentary Layer 1 (SPCL)
    [1] = ACTION_LAYER_TAP_TOGGLE(SPCL)
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
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


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
};
