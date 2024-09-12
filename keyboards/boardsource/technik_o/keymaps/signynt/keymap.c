// qmk flash -kb boardsource/technik_o -km signynt

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
#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)
#define A_DMPC MEH(KC_COMM) // Amethyst: Decrease Main Pane Count
#define A_IMPC MEH(KC_DOT) // Amethyst: Increase Main Pane Count
#define A_CLF A(S(KC_SPC)) // Amethyst: Cycle Layout Forward
#define A_SFW G(A(S(KC_H))) // Amethyst: Swap Focused Window to Clockwise Screen
#define A_RR KC_TD(TD_RR) // Amethyst: Reset Amethyst (One Tap) or Reset Auto Rais (Two Taps)
#define BCK C(KC_LBRC) // Navigate Back
#define SL G(KC_LEFT) // Move a Space Left
#define SR G(KC_RIGHT) // Move a Space Right
#define MC G(KC_UP) // Mission Control
#define SCRS KC_TD(TD_SCREEN) // Screenshot to Clipboard (One Tap) or to Desktop (Two Taps)
#define ST MEH(KC_EQL) // Shade: Toggle On/Off
#define SU MEH(KC_LBRC) // Shade: Brightness Up
#define SD MEH(KC_RBRC) // Shade: Brightness Down
#define DR_SCRL DRAGSCROLL_MODE // Dragscroll
#define DPI_U POINTER_DEFAULT_DPI_FORWARD // Increase Trackball DPI
#define DPI_D POINTER_DEFAULT_DPI_REVERSE // Decrease Trackball DPI
#define THR_R C(G(KC_RIGHT)) //Throw the Active Window to the Space to the Right
#define THR_L C(G(KC_LEFT)) //Throw the Active Window to the Space to the Right
#define TAB_L C(S(KC_LEFT)) // Switch to the Tab to the Left
#define TAB_R C(S(KC_RIGHT)) // Switch to the Tab to the Right
#define Q_ALT LALT_T(KC_Q) // Mod Tap for the Left Alt Key
#define A_SFT LSFT_T(KC_A) // Mod Tap for the Left Shift Key
#define Z_CTL LCTL_T(KC_Z) // Mod Tap for the Left Ctl Key
#define P_ALT RALT_T(KC_P) // Mod Tap for the Right Alt Key
#define QUOT_SFT RSFT_T(KC_QUOT) // Mod Tap for the Right Shift Key
#define SLSH_CTL RCTL_T(KC_SLSH) // Mod Tap for the Right Ctl Key

//define layers
enum layers {BASE, IPAD, MEDR, NAVR, NSSL, MOUS, NSL, FUNL, GAME, SECGAME, UML, INAV, OFF, SAFE};

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
  UML_A,
  UML_U,
  UML_O,
  UML_S,
  SPOTL,
  OCR,
  THROW_L,
  THROW_R,
};

//commmand tab

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

// ipad macros
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

  //take screenshot, then ocr

      case OCR:
        if (record->event.pressed) {
          tap_code16(G(S(KC_S)));
        }
        else
        {
          tap_code16(MEH(KC_O));
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

//tap dance declarations
enum {
    TD_MEDIA, TD_SCREEN, TD_SPACE, TD_RESETRAISE,
};

//tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MEDIA] = ACTION_TAP_DANCE_DOUBLE( KC_MPLY , KC_MNXT ),
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE( (G(S(KC_S))) , S(C(KC_4)) ),
    [TD_SPACE] = ACTION_TAP_DANCE_DOUBLE( G(KC_RIGHT) , G(KC_LEFT) ),
    [TD_RESETRAISE] = ACTION_TAP_DANCE_DOUBLE( MEH(KC_Z) , MEH(KC_X) ),
};

//combos
enum combos {
  JM_MOUSE1,
  KCOMM_MOUSE2,
  LDOT_MOUSE3,
};

const uint16_t PROGMEM mous1_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM mous2_combo[] = {KC_K, KC_COMM, COMBO_END};
const uint16_t PROGMEM mous3_combo[] = {KC_L, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(mous1_combo, KC_BTN1),
    COMBO(mous2_combo, KC_BTN2),
    COMBO(mous3_combo, KC_BTN3),
};


#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)

//--------------------------------------------------------------------------------------------------------

//base

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ortho_4x12(
    KC_NO,                Q_ALT,             KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              P_ALT,             KC_NO,
    KC_NO,                A_SFT,             KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              QUOT_SFT,          KC_NO,
    KC_NO,                Z_CTL,             KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            SLSH_CTL,          KC_NO,
    G(A(S(KC_H))),        OCR,               KC_ESC,            LT(MEDR, KC_TAB),  LT(NAVR, KC_SPC),  LT(MOUS, KC_ENT),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),   CMD_TAB
  ),
  [IPAD] = LAYOUT_ortho_4x12(
    LM(UML, MOD_LALT),    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              LM(UML, MOD_LALT),
    KC_LSFT,              KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_QUOT,           KC_LSFT,
    KC_LCTL,              KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    G(KC_UP),             S(C(KC_4)),        KC_ESC,            LT(MEDR, KC_TAB),  LT(INAV, KC_SPC),  LT(NSSL, KC_ENT), LT(NSSL, KC_ENT),   LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL),  KC_LGUI,           KC_TD(TD_MEDIA),   CMD_TAB
  ),

//layers
  [NAVR] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             C(S(KC_LEFT)),     KC_NO,             KC_NO,             C(S(KC_RGHT)),     KC_LALT,
    KC_LSFT,              KC_NO,             KC_LSFT,           KC_LCTRL,           KC_LALT,          KC_NO,             KC_CLCK,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_LCTL,
    TG(GAME),             S(C(KC_5)),        KC_NO,             KC_NO,              KC_NO,            KC_ENT,            KC_ENT,            KC_BSPC,           KC_DEL,            KC_NO,             THROW_L,           THROW_R
  ),
  [MEDR] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_RST,            KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_TOG,            KC_MOD,            KC_HUI,            KC_SAI,            KC_VAI,            KC_LALT,
    KC_LSFT,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           KC_LSFT,
    KC_LCTL,              KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             MEH(KC_EQL),       KC_NO,             MEH(KC_LBRC),      MEH(KC_RBRC),      KC_NO,             KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_MSTP,           KC_MSTP,           KC_MPLY,           KC_MUTE,           KC_NO,             KC_NO,             KC_NO
  ),
  [FUNL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_F12,            KC_F7,             KC_F8,              KC_F9,            KC_PSCR,           KC_F15,            KC_NO,             KC_NO,             KC_NO,             KC_RST,            KC_LALT,
    KC_LSFT,              KC_F11,            KC_F4,             KC_F5,              KC_F6,            KC_SLCK,           KC_F14,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LSFT,
    KC_LCTL,              KC_F10,            KC_F1,             KC_F2,              KC_F3,            KC_PAUS,           KC_F13,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [NSL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_LPRN,           KC_7,              KC_8,               KC_9,             KC_RPRN,           KC_LBRC,           KC_AMPR,           KC_ASTR,           KC_BSLS,           KC_RBRC,           KC_BSPC,
    KC_LSFT,              KC_COLN,           KC_4,              KC_5,               KC_6,             KC_EQL,            KC_LCBR,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_RCBR,           KC_LSFT,
    KC_LCTL,              KC_GRV,            KC_1,              KC_2,               KC_3,             KC_PLUS,           KC_TILD,           KC_EXLM,           KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    KC_NO,                KC_NO,             KC_NO,             KC_UNDS,            KC_0,             KC_MINS,           KC_MINS,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             DF(IPAD)
  ),
  [NSSL] = LAYOUT_ortho_4x12(
    KC_LALT,              KC_LCBR,           KC_AMPR,           KC_ASTR,            KC_LPRN,          KC_RCBR,           KC_LBRC,           KC_AMPR,           KC_ASTR,           KC_BSLS,           KC_RBRC,           KC_BSPC,
    KC_LSFT,              KC_SCLN,           KC_DLR,            KC_PERC,            KC_CIRC,          KC_PLUS,           KC_LCBR,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_RCBR,           KC_LSFT,
    KC_LCTL,              KC_TILD,           KC_EXLM,           KC_AT,              KC_HASH,          KC_PIPE,           KC_TILD,           KC_EXLM,           KC_COMM,           KC_DOT,            KC_SLSH,           KC_LCTL,
    KC_NO,                KC_NO,             KC_UNDS,           KC_ESC,             KC_SPC,           KC_MINS,           KC_MINS,           KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
  ),
  [MOUS] = LAYOUT_ortho_4x12(
    KC_LALT,              MEH(KC_COMM),      MEH(KC_DOT),       MEH(KC_T),          A(S(KC_SPC)),     KC_TD(TD_RESETRAISE),C(KC_LBRC),      G(KC_LEFT),        G(KC_UP),          G(KC_UP),          G(KC_RIGHT),       KC_BSPC,
    KC_LSFT,              THROW_L,           KC_NO,             KC_NO,              THROW_R,          KC_NO,             KC_NO,             KC_BTN1,           KC_BTN2,           KC_BTN3,           KC_NO,             KC_LSFT,
    KC_LCTL,              G(A(S(KC_H))),     KC_TD(TD_SCREEN),  KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           KC_LCTL,
    KC_NO,                KC_NO,              KC_NO,            KC_NO,              KC_NO,            KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO,             KC_NO
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
    KC_LALT,              MEH(KC_COMM),      MEH(KC_DOT),       MEH(KC_T),          A(S(KC_SPC)),     KC_TD(TD_RESETRAISE),C(S(KC_Z)),      C(S(KC_LEFT)),     C(KC_X),           C(KC_C),           C(S(KC_RGHT)),     KC_LALT,
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
