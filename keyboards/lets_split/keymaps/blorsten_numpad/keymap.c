#include QMK_KEYBOARD_H
#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NORMAL 0
#define _NUMLAYER 1

enum custom_keycodes {
  QUIT = SAFE_RANGE,
  ALTTAB,
  CMD
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NORMAL] =  LAYOUT_ortho_4x12( \
  TG(_NUMLAYER), QUIT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_MNXT, CMD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_MPLY, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  KC_MPRV, KC_VOLD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

[_NUMLAYER] = LAYOUT_ortho_4x12(
   _______, KC_ESC ,  KC_P7,    KC_P8,  KC_P9,  KC_PPLS, _______, _______, _______, _______, _______, _______, \
   QUIT,    KC_NLCK,  KC_P4,    KC_P5,  KC_P6,  KC_PMNS, _______, _______, _______, _______, _______, _______, \
   ALTTAB,  KC_CALC,  KC_P1,    KC_P2,  KC_P3,  KC_PAST, _______, _______, _______, _______, _______, _______ , \
   RESET,   KC_BSPC,  KC_PENT,  KC_P0,  KC_DOT, KC_PSLS, _______, _______, _______, _______, _______, _______  \
),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QUIT:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_F4)SS_UP(X_LALT));
      }
      return false;
      break;
    case ALTTAB:
      if(record->event.pressed){
        SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_TAB)SS_UP(X_LALT));
      }
        return false;
      break;
    case CMD:
      if(record->event.pressed){
       SEND_STRING(SS_LGUI("r") "cmd" SS_TAP(X_ENTER));
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case _NORMAL:
        rgblight_disable();
        break;
    case _NUMLAYER:
        rgblight_sethsv_cyan();
        rgblight_enable_noeeprom();
        break;
    }
  return state;
}
