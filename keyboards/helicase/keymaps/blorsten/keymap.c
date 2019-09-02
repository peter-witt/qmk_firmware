#include "helicase.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum telophase_layers
{
	_QWERTY,
  _MEDIA,
  _GAMING,
  _LEFT,
  _RIGHT
};

enum telophase_keycodes
{
  ADJUST = SAFE_RANGE,
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO
#define _______ KC_TRNS

uint8_t adjustCount;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = { /*QWERTY*/
	{KC_ESC,  KC_1,    KC_2,    KC_3,       KC_4,      KC_5,    KC_6,    KC_7,    KC_8,   KC_9,       KC_0,    KC_MINS, KC_EQL,  KC_BSPC },
	{KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,      KC_T,    _______, _______, KC_Y,   KC_U,       KC_I,    KC_O,    KC_P,    KC_LBRC },
  {KC_LCTL, KC_A,    KC_S,    KC_D,       KC_F,      KC_G,    _______, _______, KC_H,   KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT },
	{KC_LSFT, KC_Z,    KC_X,    KC_C,       KC_V,      KC_B,    _______, _______,  KC_N,   KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_DEL  },
	{KC_LCTL, KC_LGUI, KC_LALT, MO(_MEDIA), MO(_LEFT), KC_BSPC, _______, _______, KC_SPACE, MO(_RIGHT), KC_RCTL, KC_RALT, _______, _______}
},

[_LEFT] = {//Layer for special characters
  {KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL  },
  {KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, _______, _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, KC_BSLS, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
},

[_RIGHT] = {//Movement layer
  {KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL  },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_UP,   KC_PGDN,  _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSPC, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_DEL,  XXXXXXX, XXXXXXX,  _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______ },
},

[_MEDIA] = {//Media layer
  {TG(_GAMING), _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______, _______, _______, _______, _______ },
  {_______,     _______, _______, _______, _______, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______ },
  {_______,     _______, _______, _______, _______, _______, KC_MNXT, _______, _______, _______, _______, _______, _______, _______ },
  {_______,     _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______, _______, _______, _______, _______ },
  {_______,     _______, _______, _______, _______, _______, KC_MPRV, _______, _______, _______, _______, _______, _______, _______ },
},

[_GAMING] = {//Gaming layer
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  {_______, _______, _______, _______, _______, _______,  KC_SPC, _______, _______, _______, _______, _______, _______, _______ },
}};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ADJUST:
      //Check if pressed or released
      if (record->event.pressed) {
        adjustCount ++;
      } else {
        adjustCount --;
      }

      //enable and disable if no buttons are pressed
      if(adjustCount > 0){
        //layer_on(_ADJUST);
      }
      else{
        //layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
