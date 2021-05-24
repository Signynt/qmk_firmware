// qmk flash -kb bm43a -km fuerEmily

#include QMK_KEYBOARD_H

#define KC_RST RESET
#define KC_TOG RGB_TOG
#define KC_MOD RGB_MOD
#define KC_HUI RGB_HUI
#define KC_SAI RGB_SAI
#define KC_VAI RGB_VAI

enum layers {BASE, LAYER1, LAYER2};

/*

void rgb_matrix_indicators_user(void) {

if (host_keyboard_led_state().caps_lock) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
    if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
          rgb_matrix_set_color(i, 255, 255, 255);
    }
  }
}

}

*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT,          KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH,
        KC_LCTL, KC_LALT, KC_LGUI,   LT(LAYER2, KC_SPC)  ,    LT(LAYER1, KC_SPC)    ,KC_NO,C(KC_SPC), KC_SCLN, KC_QUOT
    ),
    [LAYER1] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,    KC_EXLM, KC_AT,   KC_HASH, A(S(KC_2)),  KC_PERC,  KC_CIRC, KC_AMPR,KC_ASTR,  KC_L,   KC_ENT,
        KC_LSFT,          KC_PLUS, KC_MINS, KC_EQL,  KC_UNDS, KC_LCBR, KC_RCBR, KC_CLCK,    KC_LPRN, KC_RPRN, KC_SLASH,
        KC_LCTL, KC_LALT, KC_LGUI,   LT(LAYER2, KC_SPC)  ,    LT(LAYER1, KC_SPC)    ,KC_NO,C(KC_SPC), KC_SCLN, KC_QUOT
    ),
    [LAYER2] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        KC_TAB,    KC_TOG,  KC_MOD,    KC_HUI,    KC_SAI,    KC_VAI,    KC_H,    KC_VOLU,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_MPRV, KC_VOLD,    KC_MNXT,  KC_COMM, KC_UP,  KC_SLASH,
        KC_RST, KC_LALT, KC_LGUI,   LT(LAYER2, KC_SPC)   ,            KC_MPLY       ,KC_NO,KC_LEFT, KC_DOWN, KC_RIGHT
    ),

};
