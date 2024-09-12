// qmk flash -kb boardsource/technik_o -km signynt_homerow

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
enum layers {BASE, IPAD, MEDR, NAVR, NSSL, NSL, FUNL, GAME, SECGAME, UML, INAV, OFF, SAFE};

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
  UML_A,
  UML_U,
  UML_O,
  UML_S,
  SPOTL,
};

//cmd tab

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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

      case UML_S:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT("s"));
        }
      break;

      case UML_A:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
            SEND_STRING(SS_UP(X_LSFT)SS_LALT("u")SS_DOWN(X_LSFT)"a");
          } else {
            SEND_STRING(SS_LALT("u")"a");
          }
        }
      break;

      case UML_U:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
            SEND_STRING(SS_UP(X_LSFT)SS_LALT("u")SS_DOWN(X_LSFT)"u");
          } else {
            SEND_STRING(SS_LALT("u")"u");
          }
        }
      break;

      case UML_O:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
            SEND_STRING(SS_UP(X_LSFT)SS_LALT("u")SS_DOWN(X_LSFT)"o");
          } else {
            SEND_STRING(SS_LALT("u")"o");
          }
        }
      break;


      case SPOTL:
        if (record->event.pressed) {
            SEND_STRING(SS_UP(X_LALT)SS_LCTL(" "));
        }
      break;

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

//specify tappping term for homerow mods
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX ? TAPPING_TERM + 50 : TAPPING_TERM;
}

//--------------------------------------------------------------------------------------------------------

//base

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ortho_4x12(
    KC_NO,                KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              KC_NO,
    KC_NO,                LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_QUOT),   KC_NO,
    KC_NO,                KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_NO,
    G(A(S(KC_H))),        KC_TD(TD_SCREEN),  KC_ESC,            LT(MEDR, KC_TAB),  LT(NAVR, KC_SPC),  LT(NSSL, KC_ENT), LT(NSSL, KC_ENT),   LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),   CMD_TAB
  ),
  [IPAD] = LAYOUT_ortho_4x12(
    LM(UML, MOD_LALT),    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              LM(UML, MOD_LALT),
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    KC_LCTL,              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    G(KC_UP),             S(C(KC_4)),        KC_ESC,            LT(MEDR, KC_TAB),  LT(INAV, KC_SPC),  LT(NSSL, KC_ENT), LT(NSSL, KC_ENT),   LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),   CMD_TAB
  ),

//layers
  [NAVR] = LAYOUT_ortho_4x12(
    KC_LALT,              G(A(S(KC_COMM))),  G(A(S(KC_DOT))),   G(A(S(KC_T))),      G(A(S(KC_X))),    A(S(KC_SPC)),      C(S(KC_Z)),        C(S(KC_LEFT)),     C(KC_X),           C(KC_C),           C(S(KC_RGHT)),     KC_LALT,
    KC_LSFT,              KC_LGUI,           KC_LALT,           KC_LCTRL,           KC_LSHIFT,        KC_NO,             KC_CLCK,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_LSFT,
    KC_LCTL,              G(S(C(KC_F1))),    G(S(C(KC_F3))),    G(S(C(KC_F4))),     G(S(C(KC_F2))),   KC_NO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_LCTL,
    TG(GAME),             KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_ENT,            KC_ENT,            KC_BSPC,           KC_DEL,            KC_NO,             C(G(KC_LEFT)),     C(G(KC_RIGHT))
  ),
  [MEDR] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_RST,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_TOG,            KC_MOD,            KC_HUI,            KC_SAI,            KC_VAI,            KC_LALT,
    KC_LSFT,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             MEH(KC_EQL),       MEH(KC_LBRC),      MEH(KC_RBRC),      RGB_VAI,           KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_MSTP,           KC_MSTP,           KC_MPLY,           KC_MUTE,           KC_NO,             KC_NO,             KC_NO
  ),
  [FUNL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_F12,            KC_F7,             KC_F8,              KC_F9,            KC_PSCR,           KC_F15,            KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_LALT,
    KC_LSFT,              KC_F11,            KC_F4,             KC_F5,              KC_F6,            KC_SLCK,           KC_F14,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LSFT,
    KC_LCTL,              KC_F10,            KC_F1,             KC_F2,              KC_F3,            KC_PAUS,           KC_F13,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LCTL,
    KC_NO,                KC_NO,             KC_TAB,            KC_APP,             KC_SPC,           KC_UNDS,           KC_UNDS,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_LPRN,           KC_7,              KC_8,               KC_9,             KC_RPRN,           KC_LBRC,           KC_AMPR,           KC_ASTR,           KC_BSLS,           KC_RBRC,           KC_BSPC,
    KC_LSFT,              KC_COLN,           KC_4,              KC_5,               KC_6,             KC_EQL,            KC_LCBR,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_RCBR,           KC_LSFT,
    KC_LCTL,              KC_GRV,            KC_1,              KC_2,               KC_3,             KC_PLUS,           KC_TILD,           KC_EXLM,           KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    A(S(C(KC_N))),        S(C(KC_5)),        KC_NO,             KC_UNDS,            KC_0,             KC_MINS,           KC_MINS,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             DF(IPAD)
  ),
  [NSSL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_LCBR,           KC_AMPR,           KC_ASTR,            KC_LPRN,          KC_RCBR,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_BSPC,
    KC_LSFT,              KC_SCLN,           KC_DLR,            KC_PERC,            KC_CIRC,          KC_PLUS,           KC_NO,             KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           KC_LSFT,
    KC_LCTL,              KC_TILD,           KC_EXLM,           KC_AT,              KC_HASH,          KC_PIPE,           KC_NO,             KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           KC_LCTL,
    KC_NO,                KC_NO,             KC_UNDS,           KC_GT,              KC_SPC,           KC_NO,             KC_NO,             KC_BTN1,           KC_BTN3,           KC_BTN2,           KC_NO,             KC_NO
  ),
  [GAME] = LAYOUT_ortho_4x12(
    KC_ESC,               KC_Q,              KC_W,              KC_E,               KC_R,             KC_T,              KC_Y,              KC_U,               KC_I,             KC_O,              KC_P,              TG(GAME),
    KC_LALT,              KC_A,              KC_S,              KC_D,               KC_F,             KC_G,              KC_H,              KC_J,               KC_K,             KC_L,              KC_QUOT,           KC_VOLU,
    KC_LSFT,              KC_Z,              KC_X,              KC_C,               KC_V,             KC_B,              KC_N,              KC_M,               KC_COMM,          KC_DOT,            KC_SLSH,           KC_VOLD,
    KC_LCTL,              A(KC_TAB),         MO(SECGAME),       KC_TAB,             KC_SPC,           LT(SECGAME, KC_ENT),LT(SECGAME, KC_ENT),KC_BSPC,          KC_DEL,           KC_MPRV,           KC_MPLY,           KC_MNXT
  ),
  [SECGAME] = LAYOUT_ortho_4x12(
    KC_1,                 KC_2,              KC_3,              KC_4,               KC_5,             KC_6,              KC_7,              KC_8,               KC_9,             KC_0,              KC_MINS,           KC_EQL,
    KC_F1,                KC_F2,             KC_F3,             KC_F4,              KC_F5,            KC_F6,             KC_F7,             KC_F8,              KC_F9,            KC_F10,            KC_F11,            KC_F12,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,            KC_NO,             KC_NO,             KC_P1,              KC_P2,            KC_P3,             KC_P4,             KC_P5,
    KC_LEFT,              KC_DOWN,           KC_UP,             KC_RGHT,            KC_NO,            KC_NO,             KC_NO,             KC_P6,              KC_P7,            KC_P8,             KC_P9,             KC_P0
  ),
  [UML] = LAYOUT_ortho_4x12(
    KC_TRNS,              KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           UML_U,              KC_TRNS,          UML_O,             KC_TRNS,           KC_TRNS,
    KC_TRNS,              UML_A,             UML_S,             KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           KC_TRNS,
    KC_TRNS,              KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           KC_TRNS,
    KC_TRNS,              KC_TRNS,           KC_TRNS,           KC_TRNS,            SPOTL,            KC_TRNS,           KC_TRNS,           KC_TRNS,            KC_TRNS,          KC_TRNS,           KC_TRNS,           KC_TRNS
  ),
  [INAV] = LAYOUT_ortho_4x12(
    KC_LALT,              G(A(S(KC_COMM))),  G(A(S(KC_DOT))),   G(A(S(KC_T))),      G(A(S(KC_X))),    A(S(KC_SPC)),      C(S(KC_Z)),        C(S(KC_LEFT)),     C(KC_X),           C(KC_C),           C(S(KC_RGHT)),     KC_LALT,
    KC_LSFT,              KC_NO,             KC_LSFT,           KC_LCTRL,           KC_LALT,          KC_NO,             KC_CLCK,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_LSFT,
    KC_LCTL,              G(S(C(KC_F1))),    G(S(C(KC_F3))),    G(S(C(KC_F4))),     G(S(C(KC_F2))),   KC_NO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_LCTL,
    TO(OFF),              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_ENT,            KC_ENT,            KC_BSPC,           KC_DEL,            KC_NO,             G(KC_LEFT),        G(KC_RIGHT)
  ),
  [OFF] = LAYOUT_ortho_4x12(
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             MO(SAFE),          KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [SAFE] = LAYOUT_ortho_4x12(
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              TG(OFF),          KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,
    KC_NO,                 KC_NO,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  )
};
