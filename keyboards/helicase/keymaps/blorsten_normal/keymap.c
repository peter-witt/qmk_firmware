#include "helicase.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum telophase_layers
{
	_QWERTY,
  _RAISE,
  _GAMING,
  _MEDIA,
  _LOWER
};

enum telophase_keycodes
{
  RAISE = SAFE_RANGE,
  LOWER,
  MEDIA
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO
#define _______ KC_TRNS

uint8_t adjustCount;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /*QWERTY*/
	{KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,     KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,  KC_BSPC  },
	{KC_TAB,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC  },
  {KC_LCTL, RAISE,   KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    KC_H,     KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT   },
	{KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,     KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_UP,   KC_DEL   },
	{KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, KC_LCTL, LOWER,  KC_BSPC, KC_SPACE, KC_LSFT, KC_RALT, KC_APP, KC_LEFT, KC_DOWN, KC_RIGHT }
},

[_RAISE] = {//Layer for special characters
  {KC_GRV,      KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL  },
  {TG(_GAMING), _______, _______, KC_VOLD, KC_UP,   KC_VOLU,  _______,       _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______ },
  {_______,     _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,       _______, KC_INS,  KC_HOME, KC_PGUP, KC_BSPC, _______, _______ },
  {_______,     _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,  _______,       _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______, _______ },
  {_______,     _______, _______, _______, _______, _______,  LCTL(KC_BSPC), LALT(KC_SPACE), _______, _______, _______, _______, _______, _______ },
},

[_LOWER] = {//Layer for special characters
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______ },
	{_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______ },
  {_______, _______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_LBRC, KC_RBRC, KC_BSLS, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
},

[_MEDIA] = {//Media layer
  {_______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, KC_MNXT, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, KC_MPRV, _______, _______, _______, _______, _______, _______, _______ },
},

[_GAMING] = {//Gaming layer
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, KC_ENT,  _______, KC_I,    _______,  KC_SPC, _______, _______, _______, _______, _______, _______, _______ },
}};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RAISE:
      //Check if pressed or released
      if (record->event.pressed) {
        adjustCount ++;
      } else {
        adjustCount --;
      }

      //enable and disable if no buttons are pressed
      if(adjustCount == 1){
        layer_on(_RAISE);
        layer_off(_LOWER);
      }
      else if (adjustCount == 2){
        layer_on(_LOWER);
        layer_off(_RAISE);
      }
      else{
        layer_off(_LOWER);
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

      case MEDIA:
      if(record->event.pressed){
        layer_on(_MEDIA);
      } else {
        layer_off(_MEDIA);
      }
      return false;
      break;
  }
  return true;
}
