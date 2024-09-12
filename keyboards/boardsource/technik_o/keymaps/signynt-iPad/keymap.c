/*
qmk flash -kb boardsource/technik_o -km signynt-iPad

 Copyright 2021 Vincenzo Mitchell Barroso
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
#define KC_RST QK_BOOT
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI
#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)
#define ESC_MEDR LT(MEDR, KC_ESC)
#define SPC_NAVR LT(NAVR, KC_SPC)
#define TAB_MOUS LT(MOUS, KC_TAB)
#define ENT_NSSL LT(NSSL, KC_ENT)
#define BSPC_NSL LT(NSL, KC_BSPC)
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
#define SD MEH(KC_LBRC) // Shade: Brightness Up
#define SU MEH(KC_RBRC) // Shade: Brightness Down
#define DR_SCRL DRAGSCROLL_MODE // Dragscroll
#define DPI_U POINTER_DEFAULT_DPI_FORWARD // Increase Trackball DPI
#define DPI_D POINTER_DEFAULT_DPI_REVERSE // Decrease Trackball DPI
#define THR_R C(G(KC_RIGHT)) //Throw the Active Window to the Space to the Right
#define THR_L C(G(KC_LEFT)) //Throw the Active Window to the Space to the Right
#define TAB_L C(S(KC_LEFT)) // Switch to the Tab to the Left
#define TAB_R C(S(KC_RIGHT)) // Switch to the Tab to the Right
#define TAB_U C(S(KC_UP)) // Switch to the Tab Above
#define TAB_D C(S(KC_DOWN)) // Switch to the Tab Below
#define Q_ALT LALT_T(KC_Q) // Mod Tap for the Left Alt Key
#define A_SFT LSFT_T(KC_A) // Mod Tap for the Left Shift Key
#define Z_CTL LCTL_T(KC_Z) // Mod Tap for the Left Ctl Key
#define P_ALT RALT_T(KC_P) // Mod Tap for the Right Alt Key
#define QUOT_SFT RSFT_T(KC_QUOT) // Mod Tap for the Right Shift Key
#define SLSH_CTL RCTL_T(KC_SLSH) // Mod Tap for the Right Ctl Key
#define LPRN_ALT LALT_T(KC_LPRN)
#define COLN_SFT LSFT_T(KC_COLN)
#define GRV_CTL LCTL_T(KC_GRV)
#define RBRC_ALT RALT_T(KC_RBRC)
#define RCBR_SFT RSFT_T(KC_RCBR)
#define SLSH_CTL RCTL_T(KC_SLSH)
#define LCBR_ALT LALT_T(KC_LCBR)
#define TILD_CTL LCTL_T(KC_TILD)

//define layers
enum layers {BASE, MEDR, NAVR, NSSL, MOUS, NSL, FUNL, GAME, SECGAME,};

enum custom_keycodes {
  CMD_TAB = SAFE_RANGE,
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
      case A_SFT:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_RALT)) == MOD_BIT(KC_RALT)) {
            if ((get_mods() & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)) {
              SEND_STRING(SS_UP(X_RSFT)SS_RALT("u")SS_DOWN(X_RSFT));
            } else {
              SEND_STRING(SS_RALT("u"));
            }
          }
        }
      break;

      case KC_U:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
              SEND_STRING(SS_UP(X_LSFT)SS_LALT("u")SS_DOWN(X_LSFT));
            } else {
              SEND_STRING(SS_RALT("u"));
            }
          }
        }
      break;

      case KC_O:
        if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
              SEND_STRING(SS_UP(X_LSFT)SS_LALT("u")SS_DOWN(X_LSFT));
            } else {
              SEND_STRING(SS_RALT("u"));
            }
          }
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

// fix mod keycodes

    case COLN_SFT:
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_COLN);
            return false;
        }
        break;

    case LPRN_ALT:
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LPRN);
            return false;
        }
        break;

    case RCBR_SFT:
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_RCBR);
            return false;
        }
        break;

    case LCBR_ALT:
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LCBR);
            return false;
        }
        break;

    case GRV_CTL:
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_GRV);
            return false;
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
    TD_MEDIA, TD_SCREEN, TD_SPACE, TD_RESETRAISE,
};

//tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MEDIA] = ACTION_TAP_DANCE_DOUBLE( KC_MPLY , KC_MNXT ),
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE( (G(S(KC_4))) , S(C(KC_4)) ),
    [TD_SPACE] = ACTION_TAP_DANCE_DOUBLE( G(KC_RIGHT) , G(KC_LEFT) ),
    [TD_RESETRAISE] = ACTION_TAP_DANCE_DOUBLE( MEH(KC_Z) , MEH(KC_X) ),
};

#define KC_TD(TD_VARIABLE) TD(TD_VARIABLE)

//--------------------------------------------------------------------------------------------------------


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         Q_ALT,   KC_W,   KC_E,   KC_R,   KC_T,    KC_NO, KC_NO,    KC_Y,    KC_U,   KC_I,   KC_O,   P_ALT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
         A_SFT,   KC_S,   KC_D,   KC_F,   KC_G,    KC_NO, KC_NO,    KC_H,    KC_J,   KC_K,   KC_L,QUOT_SFT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
         Z_CTL,   KC_X,   KC_C,   KC_V,   KC_B,    KC_NO, KC_NO,    KC_N,    KC_M,KC_COMM, KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,   ESC_MEDR,SPC_NAVR,TAB_MOUS,    KC_NO, KC_NO,ENT_NSSL,BSPC_NSL,          KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [NAVR] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
       KC_LGUI,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO, KC_NO, CAPSWRD,  TAB_L,  TAB_D,  TAB_U,  TAB_R,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
       KC_LGUI,KC_LSFT,KC_LCTL,KC_LALT,  KC_NO,    KC_NO, KC_NO, KC_CLCK,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
       KC_LCTL,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_INS,KC_HOME,KC_PGDN,KC_PGUP, KC_END,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,     TG(GAME),  KC_NO,  KC_ENT,    KC_NO, KC_NO, KC_ENT, KC_DEL,           KC_NO, KC_NO,  KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [NSL] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
        LPRN_ALT,   KC_7,   KC_8,   KC_9,KC_RPRN,  KC_NO, KC_NO, KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,RBRC_ALT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        COLN_SFT,   KC_4,   KC_5,   KC_6, KC_EQL,  KC_NO, KC_NO, KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,RCBR_SFT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
         GRV_CTL,   KC_1,   KC_2,   KC_3,KC_PLUS,  KC_NO, KC_NO, KC_TILD,KC_EXLM,KC_COMM, KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,          KC_UNDS, KC_0,KC_MINS,  KC_NO, KC_NO, KC_MINS, KC_NO,            KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [NSSL] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
        LCBR_ALT,KC_AMPR,KC_ASTR,KC_LPRN,KC_RCBR,  KC_NO, KC_NO, KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,RBRC_ALT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_SCLN ,KC_DLR, KC_PERC,KC_CIRC,KC_PLUS,  KC_NO, KC_NO, KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,RCBR_SFT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_TILD, KC_EXLM,  KC_AT,KC_HASH,KC_PIPE,  KC_NO, KC_NO, KC_TILD,KC_EXLM,KC_COMM,KC_DOT, SLSH_CTL,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,       MO(FUNL), KC_SPC,KC_MINS,  KC_NO, KC_NO, KC_MINS, KC_LGUI,          KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [FUNL] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         KC_F12,  KC_F7,  KC_F8,  KC_F9,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LALT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
         KC_F11,  KC_F4,  KC_F5,  KC_F6,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LSFT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
         KC_F10,  KC_F1,  KC_F2,  KC_F3,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LCTL,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,         KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [MOUS] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         A_DMPC, A_IMPC,MEH(KC_T),A_CLF,  KC_NO,    KC_NO, KC_NO,    BCK,    SL,      MC,     MC,     SR,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          THR_L,  KC_NO,  KC_NO,  THR_R,  KC_NO,    KC_NO, KC_NO,  KC_NO,KC_BTN1,KC_BTN2,KC_BTN3,  KC_NO,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          A_SFW,   SCRS,  KC_NO,  KC_NO,  KC_NO,    KC_NO, KC_NO,  KC_NO,KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,         KC_NO,  KC_NO,  KC_NO,    KC_NO, KC_NO,  KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [MEDR] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         KC_RST, KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO,KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,      ST,  KC_NO,     SD,     SU,  KC_NO,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,         KC_NO,KC_MUTE,KC_MSTP,   KC_NO, KC_NO, KC_MSTP, KC_MPLY,          KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [GAME] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_NO, KC_NO,    KC_Y,   KC_U,   KC_I,   KC_O,TG(GAME),
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_LSFT,   KC_A,   KC_S,   KC_D,   KC_F,   KC_NO, KC_NO,    KC_H,   KC_J,   KC_K,   KC_L,KC_QUOT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_LCTL,   KC_X,   KC_Z,   KC_C,   KC_V,   KC_NO, KC_NO,    KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,      KC_TAB, KC_SPC,OSL(SECGAME),KC_NO, KC_NO,KC_ENT,KC_BSPC,             KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),

  [SECGAME] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
         KC_ESC,   KC_7,   KC_8,   KC_9,   KC_T,   KC_NO, KC_NO,    KC_Y,   KC_U,   KC_I,   KC_O,TG(GAME),
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_LSFT,   KC_4,   KC_5,   KC_6,   KC_G,   KC_NO, KC_NO,    KC_H,   KC_J,   KC_K,   KC_L,KC_QUOT,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
        KC_LCTL,   KC_1,   KC_2,   KC_3,   KC_B,   KC_NO, KC_NO,    KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,        KC_TAB,   KC_0,  KC_NO,   KC_NO, KC_NO,  KC_ENT,KC_BSPC,           KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),
};

// clang-format on

/* Template


  [LAYER] = LAYOUT_ortho_4x12(
  // ╭───────────────────────────────────────────╮               ╭─────────────────────────────────────────────╮
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤               ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ╰───────────────────────────────────────────┤               ├─────────────────────────────────────────────╯
    KC_NO, KC_NO,         KC_NO,  KC_NO,  KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,           KC_NO, KC_NO, KC_NO
  //                 ╰───────────────────────────╯               ╰──────────────────╯
  ),


*/
