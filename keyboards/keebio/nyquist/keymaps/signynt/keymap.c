/* 
qmk flash -kb keebio/nyquist/rev3 -km signynt

 * Copyright 2021 Vincenzo Mitchell Barroso
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

// Port of https://github.com/Signynt/zmk-config/blob/master/config/cygnus.keymap
// The source keymap credits the ZMK Contributors (2020), under the MIT license.
enum layers { BASE, NAVR, NSL, NSSL, FUNL, MOUS, MEDR, GAME, SECGAME };
enum { TD_SCREEN };

#define Y_TERM G(A(S(KC_T)))
#define Y_CALE G(A(S(KC_B)))
#define Y_SPOT G(A(S(KC_Y)))
#define Y_WAPP G(A(S(KC_F)))
#define Y_MAIL G(A(S(KC_M)))
#define Y_SFW  G(A(S(KC_H)))
#define Y_RR   C(S(A(KC_X)))
#define BCK    C(KC_LBRC)
#define SL     G(KC_LEFT)
#define SR     G(KC_RGHT)
#define MC     G(KC_UP)
#define THR_R  C(G(KC_RGHT))
#define THR_L  C(G(KC_LEFT))
#define TAB_L  C(S(KC_LEFT))
#define TAB_R  C(S(KC_RGHT))
#define TAB_U  C(S(KC_UP))
#define TAB_D  C(S(KC_DOWN))

// Mod-tap only stores an 8-bit tap keycode. Intercept these dummy taps below
// to emit shifted symbols while retaining native QMK hold handling.
#define LPRN_ALT LALT_T(KC_F16)
#define COLN_SFT LSFT_T(KC_F17)
#define RCBR_SFT LSFT_T(KC_F18)
#define LCBR_ALT LALT_T(KC_F19)
#define TILD_CTL LCTL_T(KC_F20)

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCREEN] = ACTION_TAP_DANCE_DOUBLE(G(S(KC_S)), C(S(KC_4))),
};

// Outer columns are explicitly disabled on every non-gaming layer.
// Cygnus thumbs map to the three innermost bottom-row keys on each half.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ortho_4x12(
        KC_NO              , LALT_T(KC_Q)       , KC_W               , KC_E               , KC_R               , KC_T               , KC_Y               , KC_U               , KC_I               , KC_O               , LALT_T(KC_P)       , KC_NO,
        KC_NO              , LSFT_T(KC_A)       , KC_S               , KC_D               , KC_F               , KC_G               , KC_H               , KC_J               , KC_K               , KC_L               , LSFT_T(KC_QUOT)    , KC_NO,
        KC_NO              , LCTL_T(KC_Z)       , KC_X               , KC_C               , KC_V               , KC_B               , KC_N               , KC_M               , KC_COMM            , KC_DOT             , LCTL_T(KC_SLSH)    , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , LT(MEDR,KC_ESC)    , LT(NAVR,KC_SPC)    , LT(MOUS,KC_TAB)    , LT(NSSL,KC_ENT)    , LT(NSL,KC_BSPC)    , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    [NAVR] = LAYOUT_ortho_4x12(
        KC_NO              , KC_LGUI            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , CW_TOGG            , TAB_L              , TAB_D              , TAB_U              , TAB_R              , KC_NO,
        KC_NO              , KC_LGUI            , KC_LSFT            , KC_LCTL            , KC_LALT            , KC_TRNS            , KC_CAPS            , KC_LEFT            , KC_DOWN            , KC_UP              , KC_RGHT            , KC_NO,
        KC_NO              , KC_LCTL            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_INS             , KC_HOME            , KC_PGDN            , KC_PGUP            , KC_END             , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , TG(GAME)           , KC_TRNS            , KC_ENT             , KC_ENT             , KC_DEL             , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    [NSL] = LAYOUT_ortho_4x12(
        KC_NO              , LPRN_ALT           , KC_7               , KC_8               , KC_9               , KC_RPRN            , KC_LBRC            , KC_AMPR            , KC_ASTR            , KC_BSLS            , LALT_T(KC_RBRC)    , KC_NO,
        KC_NO              , COLN_SFT           , KC_4               , KC_5               , KC_6               , KC_EQL             , KC_LCBR            , KC_DLR             , KC_PERC            , KC_CIRC            , RCBR_SFT           , KC_NO,
        KC_NO              , LCTL_T(KC_GRV)     , KC_1               , KC_2               , KC_3               , KC_PLUS            , KC_TILD            , KC_EXLM            , KC_COMM            , KC_DOT             , LCTL_T(KC_SLSH)    , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , KC_UNDS            , KC_0               , KC_MINS            , KC_MINS            , KC_TRNS            , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    [NSSL] = LAYOUT_ortho_4x12(
        KC_NO              , LCBR_ALT           , KC_AMPR            , KC_ASTR            , KC_LPRN            , KC_RCBR            , KC_LBRC            , KC_AMPR            , KC_ASTR            , KC_BSLS            , LALT_T(KC_RBRC)    , KC_NO,
        KC_NO              , LSFT_T(KC_SCLN)    , KC_DLR             , KC_PERC            , KC_CIRC            , KC_PLUS            , KC_LCBR            , KC_DLR             , KC_PERC            , KC_CIRC            , RCBR_SFT           , KC_NO,
        KC_NO              , TILD_CTL           , KC_EXLM            , KC_AT              , KC_HASH            , KC_PIPE            , KC_TILD            , KC_EXLM            , KC_COMM            , KC_DOT             , LCTL_T(KC_SLSH)    , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , MO(FUNL)           , KC_SPC             , KC_MINS            , KC_MINS            , KC_LGUI            , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    [FUNL] = LAYOUT_ortho_4x12(
        KC_NO              , KC_F12             , KC_F7              , KC_F8              , KC_F9              , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_LALT            , KC_NO,
        KC_NO              , KC_F11             , KC_F4              , KC_F5              , KC_F6              , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_LSFT            , KC_NO,
        KC_NO              , KC_F10             , KC_F1              , KC_F2              , KC_F3              , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_LCTL            , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    [MOUS] = LAYOUT_ortho_4x12(
        KC_NO              , Y_TERM             , Y_SPOT             , Y_CALE             , Y_WAPP             , Y_MAIL             , BCK                , SL                 , MC                 , MC                 , SR                 , KC_NO,
        KC_NO              , Y_SFW              , KC_TRNS            , KC_TRNS            , KC_TRNS            , Y_RR               , KC_TRNS            , MS_LEFT            , MS_DOWN            , MS_UP              , MS_RGHT            , KC_NO,
        KC_NO              , THR_L              , TD(TD_SCREEN)      , KC_TRNS            , THR_R              , KC_TRNS            , KC_TRNS            , KC_TRNS            , MS_WHLD            , MS_WHLU            , KC_TRNS            , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , KC_TRNS            , KC_TRNS            , KC_TRNS            , MS_BTN1            , MS_BTN3            , MS_BTN2            , KC_NO              , KC_NO              , KC_NO
    ),

    [MEDR] = LAYOUT_ortho_4x12(
        KC_NO              , QK_BOOT            , KC_NO              , KC_NO              , KC_NO              , KC_NO              , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_NO              , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , KC_TRNS            , KC_TRNS            , KC_NO              , KC_TRNS            , KC_MPRV            , KC_VOLD            , KC_VOLU            , KC_MNXT            , KC_NO,
        KC_NO              , KC_F11             , KC_F2              , KC_DEL             , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_BRID            , KC_BRIU            , KC_TRNS            , KC_NO,
        KC_NO              , KC_NO              , KC_NO              , KC_TRNS            , KC_MUTE            , KC_MSTP            , KC_MSTP            , KC_MPLY            , KC_TRNS            , KC_NO              , KC_NO              , KC_NO
    ),

    // Expand gaming to six columns per half, restoring T/G/B to the inner
    // left column and putting Escape/Shift/Ctrl on the outer left edge.
    [GAME] = LAYOUT_ortho_4x12(
        KC_ESC,  KC_Q,    KC_W,   KC_E,   KC_R,        KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LSFT, KC_A,    KC_S,   KC_D,   KC_F,        KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
        KC_LCTL, KC_Z,    KC_X,   KC_C,   KC_V,        KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LALT, KC_LGUI, KC_NO,  KC_TAB, KC_SPC, MO(SECGAME), KC_ENT, KC_BSPC, KC_DEL,  KC_NO,   KC_NO,   KC_RCTL
    ),
    [SECGAME] = LAYOUT_ortho_4x12(
        TG(GAME), KC_7,    KC_8,   KC_9,   KC_R,    KC_T,   KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F12,  KC_TRNS,
        KC_LSFT,  KC_4,    KC_5,   KC_6,   KC_F,    KC_G,   KC_VOLU, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_TRNS,
        KC_LCTL,  KC_1,    KC_2,   KC_3,   KC_V,    KC_B,   KC_VOLD, KC_F1,   KC_F2,   KC_F3,   KC_F10,  KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_NO,  KC_TAB, KC_0, KC_TRNS,   KC_ENT,  KC_BSPC, KC_RALT, KC_NO,   KC_NO,   KC_TRNS
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    // Only ZMK's &mt was customized to 160 ms; &lt retains its 200 ms default.
    return IS_QK_MOD_TAP(keycode) ? 160 : TAPPING_TERM;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // ZMK balanced mod-taps become holds on a nested press/release.
    return IS_QK_MOD_TAP(keycode);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // ZMK's default layer-taps are hold-preferred.
    return IS_QK_LAYER_TAP(keycode);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t tap_keycode;
    switch (keycode) {
        case LPRN_ALT: tap_keycode = KC_LPRN; break;
        case COLN_SFT: tap_keycode = KC_COLN; break;
        case RCBR_SFT: tap_keycode = KC_RCBR; break;
        case LCBR_ALT: tap_keycode = KC_LCBR; break;
        case TILD_CTL: tap_keycode = KC_TILD; break;
        default: return true;
    }
    if (record->tap.count) {
        if (record->event.pressed) {
            tap_code16(tap_keycode);
        }
        return false;
    }
    return true;
}
