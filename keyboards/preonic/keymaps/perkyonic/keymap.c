/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  DVK,
  QRT,
  PRK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[DVK] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_EQL,          \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,     KC_C,    KC_R,    KC_L,    KC_SLSH,         \
  KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,     KC_T,    KC_N,    KC_S,    KC_MINS,         \
  KC_LBRC, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,     KC_W,    KC_V,    KC_Z,    KC_RBRC,         \
  KC_LSFT, KC_ESC,  KC_LALT, KC_LGUI, KC_ENT,  KC_BSPC, KC_SPC,  KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, LT(PRK, KC_BSLS) \
),

[QRT] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_EQL,          \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_MINS,         \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,         \
  KC_LBRC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,         \
  KC_LSFT, KC_ESC,  KC_LALT, KC_LGUI, KC_ENT,  KC_BSPC, KC_SPC,  KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, LT(PRK, KC_BSLS) \
),

[PRK] = LAYOUT_preonic_grid( \
  KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  AG_TOGG,         \
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,   KC_F18,  KC_F19,  KC_F20,  AU_TOG,          \
  _______, KC_NUHS, KC_NUBS, _______, _______, KC_BRID, KC_BRIU, KC_VOLD,  KC_VOLU, KC_MUTE, KC_MPLY, MU_TOG,          \
  _______, DF(QRT), _______, KC_SLCK, KC_PSCR, KC_PAUS, KC_MPRV, KC_MNXT,  KC_MRWD, KC_MFFD, DF(DVK), CK_TOGG,         \
  _______, _______, _______, _______, KC_CAPS, KC_DEL,  KC_INS,  KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  _______          \
)

};
