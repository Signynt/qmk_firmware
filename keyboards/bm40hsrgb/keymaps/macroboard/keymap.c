// qmk flash -kb bm40hsrgb -km macroboard

/* Copyright 2021 Vincenzo Mitchell Barroso
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

// non-KC_ keycodes
#define KC_RST RESET
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

//define layers
enum layers {BASE, SOUND, BRIGHT, NUM};

enum custom_keycodes {
    VOL1 = SAFE_RANGE,
    VOL2,
    VOL3,
    VOL4,
    VOL5,
    VOL6,
    VOL7,
    VOL8,
    VOL9,
    VOL10,
    OUTPUT,
};

bool levelOne = false;
bool levelTwo = false;
bool levelThree = false;
bool levelFour = false;
bool levelFive = false;
bool levelSix = false;
bool levelSeven = false;
bool levelEight = false;
bool levelNine = false;
bool levelTen = false;
bool output = false;
bool onAudio = false;
bool onBright = false;
bool onNum = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case VOL1:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F1));
          levelOne = true;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;


    case VOL2:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F2));
          levelOne = false;
          levelTwo = true;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL3:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F3));
          levelOne = false;
          levelTwo = false;
          levelThree = true;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL4:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F4));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = true;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL5:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F5));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = true;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL6:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F6));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = true;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL7:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F7));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = true;
          levelEight = false;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL8:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F8));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = true;
          levelNine = false;
          levelTen = false;
        } else {
        }
        break;

    case VOL9:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F9));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = true;
          levelTen = false;
        } else {
        }
        break;

    case VOL10:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F10));
          levelOne = false;
          levelTwo = false;
          levelThree = false;
          levelFour = false;
          levelFive = false;
          levelSix = false;
          levelSeven = false;
          levelEight = false;
          levelNine = false;
          levelTen = true;
        } else {
        }
        break;

    case OUTPUT:
        if (record->event.pressed) {
          tap_code16(HYPR(KC_F11));
          output = !output;
        } else {
        }
        break;
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case BASE:
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_FRACTAL);
        onAudio = false;
        onBright = false;
        onNum = false;
        break;

    case SOUND:
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_MUSIC_ANIM);
        onAudio = true;
        onBright = false;
        onNum = false;
        break;

    case BRIGHT:
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_BRIGHT_ANIM);
        onAudio = false;
        onBright = true;
        onNum = false;
        break;

    case NUM:
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_NUM_ANIM);
        onAudio = false;
        onBright = false;
        onNum = true;
        break;

      }
        return state;
}


void rgb_matrix_indicators_user(void) {

if(onAudio == true){
  if(IS_LAYER_ON(SOUND)) {
    rgb_matrix_set_color(0, 50, 50, 50);
    rgb_matrix_set_color(12, 0, 0, 0);
    rgb_matrix_set_color(24, 0, 0,  0);
    rgb_matrix_set_color(36, 0, 0, 0);
  }

if(levelOne == true) {

  rgb_matrix_set_color(1, 0, 50, 0);


  }
if(levelTwo == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);

  }
if(levelThree == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);

  }
if(levelFour == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);

  }
if(levelFive == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);

  }
if(levelSix == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);
  rgb_matrix_set_color(6, 0, 50, 0);
  }
if(levelSeven == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);
  rgb_matrix_set_color(6, 0, 50, 0);
  rgb_matrix_set_color(7, 0, 50, 0);

  }
if(levelEight == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);
  rgb_matrix_set_color(6, 0, 50, 0);
  rgb_matrix_set_color(7, 0, 50, 0);
  rgb_matrix_set_color(8, 0, 50, 0);

  }
if(levelNine == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);
  rgb_matrix_set_color(6, 0, 50, 0);
  rgb_matrix_set_color(7, 0, 50, 0);
  rgb_matrix_set_color(8, 0, 50, 0);
  rgb_matrix_set_color(9, 0, 50, 0);

  }
if(levelTen == true) {

  rgb_matrix_set_color(1, 0, 50, 0);
  rgb_matrix_set_color(2, 0, 50, 0);
  rgb_matrix_set_color(3, 0, 50, 0);
  rgb_matrix_set_color(4, 0, 50, 0);
  rgb_matrix_set_color(5, 0, 50, 0);
  rgb_matrix_set_color(6, 0, 50, 0);
  rgb_matrix_set_color(7, 0, 50, 0);
  rgb_matrix_set_color(8, 0, 50, 0);
  rgb_matrix_set_color(9, 0, 50, 0);
  rgb_matrix_set_color(10, 0, 50, 0);

  }
}else{

}

if(onAudio == true){
if(output == true){
  rgb_matrix_set_color(11, 10, 0, 50);
}else{
  rgb_matrix_set_color(11, 0, 40, 50);
}
} else {

}

if(onBright == true){
  rgb_matrix_set_color(0, 0, 0, 0);
  rgb_matrix_set_color(12, 0, 0, 0);
  rgb_matrix_set_color(24, 50, 50, 50);
  rgb_matrix_set_color(36, 0, 0, 0);
}else{

}

if(onNum == true){
  rgb_matrix_set_color(0, 0, 0, 0);
  rgb_matrix_set_color(12, 0, 0, 0);
  rgb_matrix_set_color(24, 0, 0, 0);
  rgb_matrix_set_color(36, 50, 50, 50);

  rgb_matrix_set_color(19, 0, 40, 50);
  rgb_matrix_set_color(20, 0, 40, 50);
  rgb_matrix_set_color(21, 0, 40, 50);
  rgb_matrix_set_color(22, 0, 40, 50);

  rgb_matrix_set_color(2, 10, 0, 50);
  rgb_matrix_set_color(3, 10, 0, 50);
  rgb_matrix_set_color(4, 10, 0, 50);

  rgb_matrix_set_color(14, 10, 0, 50);
  rgb_matrix_set_color(15, 10, 0, 50);
  rgb_matrix_set_color(16, 10, 0, 50);

  rgb_matrix_set_color(26, 10, 0, 50);
  rgb_matrix_set_color(27, 10, 0, 50);
  rgb_matrix_set_color(28, 10, 0, 50);

  rgb_matrix_set_color(40, 10, 0, 50);
}else{

}

}


//--------------------------------------------------------------------------------------------------------

//base

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_planck_mit(
    TO(SOUND),            KC_RST,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_TOG,            KC_MOD,            KC_HUI,            KC_SAI,            KC_VAI,            KC_LALT,
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    TO(BRIGHT),           KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    TO(NUM),                 KC_2,              KC_3,              KC_4,              KC_NO,                        KC_7,              KC_8,              KC_9,              KC_0,              KC_SPC,            KC_BSPC
  ),

  [SOUND] = LAYOUT_planck_mit(
    TO(BASE),              VOL1,              VOL2,              VOL3,              VOL4,              VOL5,              VOL6,              VOL7,              VOL8,              VOL9,              VOL10,              OUTPUT,
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    TO(BRIGHT),              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    TO(NUM),              KC_2,              KC_3,              KC_4,              KC_MPRV,                            KC_MPLY,              KC_MNXT,              KC_9,              KC_0,              KC_1,              KC_2
  ),

  [BRIGHT] = LAYOUT_planck_mit(
    TO(SOUND),          KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    TO(BASE),         KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    TO(NUM),              KC_NO,              KC_NO,              KC_NO,              KC_F14,                       KC_F13,                       KC_F15,             KC_NO,              KC_NO,              KC_NO,              KC_NO
  ),
  [NUM] = LAYOUT_planck_mit(
    TO(SOUND),          KC_EQL,             KC_P7,              KC_P8,              KC_P9,              KC_BSPC,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_NO,              KC_MINS,            KC_P4,              KC_P5,              KC_P6,              KC_NO,              KC_NO,              KC_LEFT,            KC_DOWN,            KC_UP,              KC_RIGHT,           KC_NO,
    TO(BRIGHT),         KC_PLUS,            KC_P1,              KC_P2,              KC_P3,              KC_NO,              KC_NO,              KC_NO,              KC_COMM,            KC_DOT,             KC_NO,              KC_NO,
    TO(BASE),           KC_SPC,             KC_P0,              KC_COMM,            KC_P0,                        KC_SPC,                       KC_BSPC,            KC_NO,              KC_NO,              KC_NO,              KC_NO
  )
};
