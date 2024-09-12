/*
qmk compile -kb bastardkb/charybdis/3x6 -km signynt

 * Copyright 2022 Vincenzo Mitchell Barroso (Signynt)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

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
enum layers {BASE, POINTER, MEDR, NAVR, NSSL, FUNL, MOUS, NSL,};

//Trackball Settings

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;
#endif

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(POINTER);
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_kb(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(POINTER);
    }
    matrix_scan_user();
}
#    endif  // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif

//tap dance declarations
enum {
  TD_SCREEN, TD_RR,
};

//tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE( (G(S(KC_S))) , S(C(KC_4)) ),
    [TD_RR] = ACTION_TAP_DANCE_DOUBLE( MEH(KC_Z) , MEH(KC_X) ), // Reset Raise
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_NO,    Q_ALT,   KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,   KC_I,   KC_O,   P_ALT, KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,    A_SFT,   KC_S,   KC_D,   KC_F,   KC_G,       KC_H,    KC_J,   KC_K,   KC_L,QUOT_SFT, KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,    Z_CTL,   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,KC_COMM, KC_DOT,SLSH_CTL, KC_NO,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
    LT(MEDR, KC_TAB), LT(NAVR, KC_SPC), LT(MOUS, KC_ESC),    LT(NSSL, KC_ENT), LT(NSL, KC_BSPC)
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [POINTER] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_NO,    Q_ALT,   KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,   KC_I,   KC_O,   P_ALT, KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,    A_SFT,   KC_S,   KC_D,   KC_F,   KC_G,       KC_H, KC_BTN1,KC_BTN2,KC_BTN3,QUOT_SFT, KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_NO,    Z_CTL,   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,DR_SCRL, KC_DOT,SLSH_CTL, KC_NO,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
    LT(MEDR, KC_TAB), LT(NAVR, KC_SPC), LT(MOUS, KC_ENT),    LT(NSSL, KC_ENT), LT(NSL, KC_BSPC)
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NAVR] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_LALT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  TAB_L,  KC_NO,  KC_NO,  TAB_R,  KC_LALT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT,  KC_NO,KC_LSFT,KC_LCTL,KC_LALT,  KC_NO,     KC_CLCK,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,  KC_LSFT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,      KC_INS,KC_HOME,KC_PGDN,KC_PGUP, KC_END,  KC_LCTL,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_NO,  KC_NO, KC_ENT,      KC_ENT, KC_DEL
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NSL] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_LALT,KC_LPRN,   KC_7,   KC_8,   KC_9,KC_RPRN,     KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,KC_RBRC,  KC_BSPC,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT,KC_COLN,   KC_4,   KC_5,   KC_6, KC_EQL,     KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,KC_RCBR,  KC_LSFT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL, KC_GRV,   KC_1,   KC_2,   KC_3,KC_PLUS,     KC_TILD,KC_EXLM,KC_COMM, KC_DOT,KC_SLSH,  KC_LCTL,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_UNDS, KC_0,KC_MINS,     KC_MINS, KC_NO
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NSSL] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_LALT,KC_LCBR,KC_AMPR,KC_ASTR,KC_LPRN,KC_RCBR,     KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,KC_RBRC,  KC_BSPC,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT,KC_SCLN,KC_DLR, KC_PERC,KC_CIRC,KC_PLUS,     KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,KC_RCBR,  KC_LSFT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL,KC_TILD,KC_EXLM,  KC_AT,KC_HASH,KC_PIPE,     KC_TILD,KC_EXLM,KC_COMM,KC_DOT, KC_SLSH,  KC_LCTL,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                MO(FUNL), KC_SPC,KC_MINS,     KC_MINS, KC_LGUI
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [FUNL] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_LALT, KC_F12,  KC_F7,  KC_F8,  KC_F9,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LALT,    KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT, KC_F11,  KC_F4,  KC_F5,  KC_F6,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LSFT,    KC_NO,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL, KC_F10,  KC_F1,  KC_F2,  KC_F3,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LCTL,    KC_NO,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [MOUS] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
         KC_LALT, A_DMPC, A_IMPC,MEH(KC_T),A_CLF,   A_RR,         BCK,    SL,      MC,     MC,     SR,  KC_BSPC,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT,  THR_L,  DPI_D,  DPI_U,  THR_R,  KC_NO,       KC_NO,KC_BTN1,KC_BTN2,KC_BTN3,DR_SCRL,  KC_LSFT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL,  A_SFW,   SCRS,  KC_NO,  KC_NO,  KC_NO,       KC_NO,KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,  KC_LCTL,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [MEDR] = LAYOUT_charybdis_3x6(
  // ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
          KC_ESC,  KC_RST, KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LALT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LSFT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,  KC_LSFT,
  // ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
         KC_LCTL,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          ST,  KC_NO,     SD,     SU,  KC_NO,  KC_LCTL,
  // ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_NO,KC_MUTE,KC_MSTP,     KC_MSTP, KC_MPLY
  //                          ╰───────────────────────────╯ ╰──────────────────╯
  ),
;

// clang-format on

/* Template


[LAYER] = LAYOUT_charybdis_3x6(
// ╭────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_LALT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LALT,
// ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LSFT,
// ├────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LCTL,
// ╰────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                 KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO
//                          ╰───────────────────────────╯ ╰──────────────────╯
),


*/
