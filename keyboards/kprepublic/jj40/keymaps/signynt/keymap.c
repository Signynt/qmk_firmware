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
enum layers {BASE, MEDR, NAVR, NSSL, NSL, FUNL, GAME, SECGAME};

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
  THROW_R,
  THROW_L,
};

//macros

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

//command tab

    case CMD_TAB:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LCTL);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

// throw window to the right

    case THROW_R:
      if (record->event.pressed) {
        tap_code16(C(G(KC_RIGHT)));
        tap_code16(C(G(KC_RIGHT)));
      }

// throw window to the left

    case THROW_L:
      if (record->event.pressed) {
        tap_code16(C(G(KC_LEFT)));
        tap_code16(C(G(KC_LEFT)));
      }

  }
  return true;
}

void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 500) {
      unregister_code(KC_LCTL);
      is_cmd_tab_active = false;
    }
  }
}

//layer led colors

//tap dance declarations
enum {
    TD_MEDIA, TD_SCREEN,
};

//tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MEDIA] = ACTION_TAP_DANCE_DOUBLE( KC_MPLY , KC_MNXT ),
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE( (G(S(KC_S))) , S(C(KC_4)) ),
};

#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)

//--------------------------------------------------------------------------------------------------------

//base

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_planck_mit(
    KC_LALT,              KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_LALT,
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    KC_LCTL,              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    G(A(S(KC_H))),        KC_TD(TD_SCREEN),  KC_ESC,            LT(MEDR, KC_TAB),  LT(NAVR, KC_SPC),      LT(NSSL, KC_ENT),                 LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),   CMD_TAB
  ),

//layers
  [NAVR] = LAYOUT_planck_mit(
    KC_LALT,              G(A(S(KC_COMM))),  G(A(S(KC_DOT))),   G(A(S(KC_T))),      G(A(S(KC_X))),    A(S(KC_SPC)),      C(S(KC_Z)),        C(S(KC_LEFT)),     C(KC_X),           C(KC_C),           C(S(KC_RGHT)),     KC_LALT,
    KC_LSFT,              KC_NO,             KC_LSFT,           KC_LCTRL,           KC_LALT,          KC_NO,             KC_CLCK,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_LSFT,
    KC_LCTL,              G(S(C(KC_F1))),    G(S(C(KC_F3))),    G(S(C(KC_F4))),     G(S(C(KC_F2))),   KC_NO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_LCTL,
    TG(GAME),             KC_NO,             KC_NO,             KC_NO,              KC_NO,                     KC_ENT,                      KC_BSPC,           KC_DEL,            KC_NO,             THROW_L,           THROW_R
  ),
  [MEDR] = LAYOUT_planck_mit(
    KC_LALT,              KC_RST,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_TOG,            KC_MOD,            KC_HUI,            KC_SAI,            KC_VAI,            KC_LALT,
    KC_LSFT,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             MEH(KC_EQL),       MEH(KC_LBRC),      MEH(KC_RBRC),      RGB_VAI,           KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_NO,              KC_NO,                     KC_MSTP,                     KC_MPLY,           KC_MUTE,           KC_NO,             KC_NO,             KC_NO
  ),
  [FUNL] = LAYOUT_planck_mit(
    KC_LALT,              KC_F12,            KC_F7,             KC_F8,              KC_F9,            KC_PSCR,           KC_F15,            KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_LALT,
    KC_LSFT,              KC_F11,            KC_F4,             KC_F5,              KC_F6,            KC_SLCK,           KC_F14,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LSFT,
    KC_LCTL,              KC_F10,            KC_F1,             KC_F2,              KC_F3,            KC_PAUS,           KC_F13,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LCTL,
    KC_NO,                KC_NO,             KC_TAB,            KC_APP,             KC_SPC,                    KC_UNDS,                     KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSL] = LAYOUT_planck_mit(
    KC_LALT,              KC_LPRN,           KC_7,              KC_8,               KC_9,             KC_RPRN,           KC_LBRC,           KC_AMPR,           KC_ASTR,           KC_BSLS,           KC_RBRC,           KC_BSPC,
    KC_LSFT,              KC_COLN,           KC_4,              KC_5,               KC_6,             KC_EQL,            KC_LCBR,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_RCBR,           KC_LSFT,
    KC_LCTL,              KC_GRV,            KC_1,              KC_2,               KC_3,             KC_PLUS,           KC_TILD,           KC_EXLM,           KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    A(S(C(KC_N))),        S(C(KC_5)),        KC_NO,             KC_UNDS,            KC_0,                      KC_MINS,                     KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSSL] = LAYOUT_planck_mit(
    KC_LALT,              KC_LCBR,           KC_AMPR,           KC_ASTR,            KC_LPRN,          KC_RCBR,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_BSPC,
    KC_LSFT,              KC_SCLN,           KC_DLR,            KC_PERC,            KC_CIRC,          KC_PLUS,           KC_NO,             KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           KC_LSFT,
    KC_LCTL,              KC_TILD,           KC_EXLM,           KC_AT,              KC_HASH,          KC_PIPE,           KC_NO,             KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           KC_LCTL,
    KC_NO,                C(A(S(KC_O))),     KC_UNDS,           KC_GT,              KC_SPC,                    KC_NO,                       KC_BTN1,           KC_BTN3,           KC_BTN2,           KC_NO,             KC_NO
  ),
  [GAME] = LAYOUT_planck_mit(
    KC_ESC,               KC_Q,              KC_W,              KC_E,               KC_R,             KC_T,              KC_Y,              KC_U,               KC_I,             KC_O,              KC_P,              TG(GAME),
    KC_LALT,              KC_A,              KC_S,              KC_D,               KC_F,             KC_G,              KC_H,              KC_J,               KC_K,             KC_L,              KC_QUOT,           KC_VOLU,
    KC_LSFT,              KC_Z,              KC_X,              KC_C,               KC_V,             KC_B,              KC_N,              KC_M,               KC_COMM,          KC_DOT,            KC_SLSH,           KC_VOLD,
    KC_LCTL,              A(KC_TAB),         MO(SECGAME),       KC_TAB,             KC_SPC,             LT(SECGAME, KC_ENT),                KC_BSPC,            KC_DEL,           KC_MPRV,           KC_MPLY,           KC_MNXT
  ),
  [SECGAME] = LAYOUT_planck_mit(
    KC_1,                 KC_2,              KC_3,              KC_4,               KC_5,             KC_6,              KC_7,              KC_8,               KC_9,             KC_0,              KC_MINS,           KC_EQL,
    KC_F1,                KC_F2,             KC_F3,             KC_F4,              KC_F5,            KC_F6,             KC_F7,             KC_F8,              KC_F9,            KC_F10,            KC_F11,            KC_F12,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,            KC_NO,             KC_NO,             KC_P1,              KC_P2,            KC_P3,             KC_P4,             KC_P5,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,                     KC_NO,                       KC_P6,              KC_P7,            KC_P8,             KC_P9,             KC_P0
  )
};
