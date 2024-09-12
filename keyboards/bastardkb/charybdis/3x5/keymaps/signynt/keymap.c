/*
qmk flash -kb bastardkb/charybdis/3x5/v2/elitec -km signynt
qmk generate-autocorrect-data autocorrect_dictionary.txt -kb bastardkb/charybdis/3x5/v2/elitec -km signynt

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
#define Y_TERM G(A(S(KC_T))) // Yabai: Terminal Scratchpad
#define Y_BROW G(A(S(KC_B))) // Yabai: Browser Scratchpad
#define Y_SPOT G(A(S(KC_S))) // Yabai: Spotify Scratchpad
#define Y_FIND G(A(S(KC_F))) // Yabai: Finder Scratchpad
#define A_SFW G(A(S(KC_H))) // Yabai: Swap Focused Window to Clockwise Screen
#define A_RR KC_TD(TD_RR) // Yabai: Make Window Fill Space (One Tap) or Reset Yabai (Two Taps)
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
enum layers {BASE, POINTER, MEDR, NAVR, NSSL, FUNL, MOUS, NSL, GAME, SECGAME, STEN};

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
    [TD_RR] = ACTION_TAP_DANCE_DOUBLE( MEH(KC_X) , MEH(KC_Z) ), // Reset Raise
};

//intercept mod taps
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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

// Activate or deactivate Plover when the stenography layer is toggled
bool sten_was_active = false;  // Track whether the STEN (stenography) layer was active
layer_state_t layer_state_set_user(layer_state_t state) {
    bool sten_is_active = layer_state_cmp(state, STEN);
    // Check if the STEN layer was toggled (either activated or deactivated)
    if (sten_is_active != sten_was_active) {
        // Send your keystrokes when the STEN layer is toggled
        register_code(KC_D);
        register_code(KC_F);
        register_code(KC_V);
        register_code(KC_TAB);
        register_code(KC_K);
        register_code(KC_COMM);

        unregister_code(KC_D);
        unregister_code(KC_F);
        unregister_code(KC_V);
        unregister_code(KC_TAB);
        unregister_code(KC_K);
        unregister_code(KC_COMM);
    }

    // Update the state tracking
    sten_was_active = sten_is_active;

    return state;
}


// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         Q_ALT,   KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,   KC_I,   KC_O,   P_ALT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         A_SFT,   KC_S,   KC_D,   KC_F,   KC_G,       KC_H,    KC_J,   KC_K,   KC_L,QUOT_SFT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         Z_CTL,   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,KC_COMM, KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                    ESC_MEDR,SPC_NAVR,TAB_MOUS,   ENT_NSSL,BSPC_NSL
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [POINTER] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         Q_ALT,   KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,   KC_I,   KC_O,   P_ALT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         A_SFT,   KC_S,   KC_D,   KC_F,   KC_G,       KC_H, KC_BTN1,KC_BTN2,KC_BTN3,QUOT_SFT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         Z_CTL,   KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,DR_SCRL, KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                    ESC_MEDR,SPC_NAVR,TAB_MOUS,   ENT_NSSL,BSPC_NSL
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NAVR] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_LGUI,  KC_NO,  KC_NO,  KC_NO,  KC_NO,     CAPSWRD,  TAB_L,  TAB_D,  TAB_U,  TAB_R,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI,KC_LSFT,KC_LCTL,KC_LALT,  KC_NO,     KC_CLCK,KC_LEFT,KC_DOWN,  KC_UP,KC_RGHT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LCTL,  KC_NO,TG(STEN), KC_NO,AC_TOGG,      KC_INS,KC_HOME,KC_PGDN,KC_PGUP, KC_END,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                      TG(GAME),  KC_NO, KC_ENT,      KC_ENT, KC_DEL
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NSL] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        LPRN_ALT,   KC_7,   KC_8,   KC_9,KC_RPRN,     KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,RBRC_ALT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        COLN_SFT,   KC_4,   KC_5,   KC_6, KC_EQL,     KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,RCBR_SFT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         GRV_CTL,   KC_1,   KC_2,   KC_3,KC_PLUS,     KC_TILD,KC_EXLM,KC_COMM, KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                           KC_UNDS, KC_0,KC_MINS,     KC_MINS, KC_NO
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [NSSL] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        LCBR_ALT,KC_AMPR,KC_ASTR,KC_LPRN,KC_RCBR,     KC_LBRC,KC_AMPR,KC_ASTR,KC_BSLS,RBRC_ALT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_SCLN,KC_DLR, KC_PERC,KC_CIRC,KC_PLUS,     KC_LCBR, KC_DLR,KC_PERC,KC_CIRC,RCBR_SFT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_TILD,KC_EXLM,  KC_AT,KC_HASH,KC_PIPE,     KC_TILD,KC_EXLM,KC_COMM,KC_DOT,SLSH_CTL,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        MO(FUNL), KC_SPC,KC_MINS,     KC_MINS, KC_LGUI
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [FUNL] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_F12,  KC_F7,  KC_F8,  KC_F9,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LALT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_F11,  KC_F4,  KC_F5,  KC_F6,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LSFT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_F10,  KC_F1,  KC_F2,  KC_F3,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_LCTL,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [MOUS] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         Y_TERM, Y_BROW, Y_SPOT,  Y_FIND,  A_RR,         BCK,    SL,      MC,     MC,     SR,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          THR_L,  DPI_D,  DPI_U,  THR_R,  KC_NO,       KC_NO,KC_BTN1,KC_BTN2,KC_BTN3,DR_SCRL,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          A_SFW,   SCRS,  KC_NO,  KC_NO,  KC_NO,       KC_NO,KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [MEDR] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_RST, KC_NO,  KC_NO,  KC_NO,   KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,KC_MPRV,KC_VOLD,KC_VOLU,KC_MNXT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          ST,  KC_NO,     SD,     SU,  KC_NO,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_NO,KC_MUTE,KC_MSTP,     KC_MSTP, KC_MPLY
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [GAME] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,        KC_Y,   KC_U,   KC_I,   KC_O,TG(GAME),
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_LSFT,   KC_A,   KC_S,   KC_D,   KC_F,        KC_H,   KC_J,   KC_K,   KC_L,KC_QUOT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_LCTL,   KC_X,   KC_Z,   KC_C,   KC_V,        KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_TAB, KC_SPC,OSL(SECGAME), KC_ENT,KC_BSPC
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [SECGAME] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_ESC,   KC_7,   KC_8,   KC_9,   KC_T,        KC_Y,   KC_U,   KC_I,   KC_O,TG(GAME),
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_LSFT,   KC_4,   KC_5,   KC_6,   KC_G,        KC_H,   KC_J,   KC_K,   KC_L,KC_QUOT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_LCTL,   KC_1,   KC_2,   KC_3,   KC_B,        KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_TAB,   KC_0,  KC_NO,      KC_ENT,KC_BSPC
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [STEN] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,       KC_Y,    KC_U,   KC_I,   KC_O,    KC_P,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_A,    KC_S,   KC_D,   KC_F,   KC_G,       KC_H,    KC_J,   KC_K,   KC_L, KC_QUOT,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,       KC_N,    KC_M,KC_COMM, KC_DOT, KC_SLSH,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                      TG(STEN), KC_SPC, KC_TAB,     KC_ENT, KC_BSPC
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),
};

// clang-format on

/* Template


  [LAYER] = LAYOUT_charybdis_3x5(
  // ╭───────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ├───────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  // ╰───────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO
  //                 ╰───────────────────────────╯ ╰──────────────────╯
  ),


*/
