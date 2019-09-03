/* Copyright 2019 Peter Witt
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

enum layers{
  _BASE,
  _RAISE,
  _LOWER,
  _UTIL
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  RAISE = SAFE_RANGE,
  LOWER,
  UTIL
};

#define XXXXXXX KC_NO
#define _______ KC_TRNS

uint8_t adjustCount;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,     KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC,
    UTIL,    RAISE,   KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    KC_H,     KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,     KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_UP,   KC_DEL,
    KC_LCTL, KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, LOWER,  KC_BSPC, KC_SPACE, KC_LSFT, KC_RALT, KC_APP, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
 
  [_RAISE] = LAYOUT(
    RESET,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,  _______, _______, _______,
    _______, _______, _______, KC_TAB, KC_LALT, KC_LGUI,  KC_RCTL, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_DEL,  _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, LALT(KC_BSPC), _______, _______, _______, _______,  _______, _______, _______
  ),

  [_LOWER] = LAYOUT(
    KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______,
    _______, _______, _______, _______, _______, _______, KC_GRV,  KC_COMM, KC_DOT,  KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

    [_UTIL] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case RAISE:
        //Check if pressed or released
        if (record->event.pressed) {
          layer_on(_RAISE);
        } else {
          layer_off(_RAISE);
        }
        return false;
        break;

        case LOWER:
        //Check if pressed or released
        if (record->event.pressed) {
          layer_on(_LOWER);
        } else {
          layer_off(_LOWER);
        }
        return false;
        break;

        case UTIL:
        //Check if pressed or released
        if (record->event.pressed) {
          layer_on(_UTIL);
        } else {
          layer_off(_UTIL);
        }
        return false;
        break;
    }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
