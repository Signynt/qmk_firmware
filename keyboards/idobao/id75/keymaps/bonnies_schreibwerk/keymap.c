// qmk flash -kb idobao/id75/v2 -km bonnies_schreibwerk

/*

               -+*#%@@@@@%#*+=:
             +@@%**===--===*%@@*
            +@*.              @#
            +%      =*       .@@@#*=-:
             %+     ##        =%@@@@@@@%#*=:
              +#.  .@=            ::-==**#@@@#+:
               -%= -@                      .-+%@@#+-.
                .*#+#                           :=#@@#=
                  -#=                               :+%@#:
                    +%.                                :*@*.                                  .*
                     :@.                                 :*@:                                  +
       :*@@@@%*.      +*                                   -@:                           :.           :=+=.
     .#@%=:.::+%=     .@.                                   =@.  .=#%%%+     +%%%#+  .. #@%@*. .-    =@%*#@
     +@+     :-:%+     +*                                    %= +@@*.  +#  *%@#--+%@ +=*@: :#@ =*    +*  :@
     =@      @@@@#     =@                                    %= @*      *# *@+    .@:=#@+    %-=#   :*%+%@*
      @:     :%@@+     =@                                   *@.-@.      :@:=@     *% .@@:    @+.@-  +@@@%-
      =#.              #%                                 -%#:  +#-:...=%+ :@     +*  @+    .@. %%   -#@@*:
       -#%+-.       .=%@-  :=.                        :=*%#:     .=++*+=:   .         .         .-     --+%@#*=:.
         .-+#%#*+*#%@%+.    =##=.                :=*%%*=-.                                                 .-+#@@@%#*++=--:.
              .:---.           -+************###*+-:                                                             :-=*#%%@@@@+


    Author:  Simon Bonnie
    Date:    24.05.2023

 */
#include QMK_KEYBOARD_H

// Keyboard Layers
enum layer_names {
    BASE,           /* Base Layer */
    CAPS,           /* SHIFT-Key */
    SPECIAL,        /* Funtion-Key */
    MOUSE,          /* Mouse layer */
//    MIDI            /* MIDI-Layer */
};

// Eigene Ausgaben
/*enum macros {
    MY_MAIL1 = SAFE_RANGE,
    MY_MAIL2,
    MY_MAIL3
};*/

/*
void rgb_matrix_indicators_user(void) {
//capslock
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
            if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                rgb_matrix_set_color(i, 255, 255, 255);
            }
        }
    }
}*/

//  RGB LIGHTING
// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 75, HSV_RED}       // Light 20 LEDs, starting with LED 6
);

// Midi RGB
const rgblight_segment_t PROGMEM my_midi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 75, HSV_WHITE}       // Light 20 LEDs, starting with LED 6
);

// Numpad RGB
const rgblight_segment_t PROGMEM my_numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 75, HSV_BLUE}
);
// Mouse RGB
const rgblight_segment_t PROGMEM my_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 75, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_numpad_layer,
//    my_midi_layer,
    my_mouse_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
// Numpad
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, SPECIAL));
//    rgblight_set_layer_state(2, layer_state_cmp(state, MIDI));
    rgblight_set_layer_state(2, layer_state_cmp(state, MOUSE));
    return state;
}

/*bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MY_MAIL1:
                SEND_STRING("sbonnie@bonnies.eu");
                return false; break;
            case MY_MAIL2:
                SEND_STRING("simon.bonnie99@gmail.com");
                return false; break;
            case MY_MAIL3:
                SEND_STRING("simon.bonnie@alumni.fh-aachen.de");
                return false; break;
        }
    }
    return true;
}*/

// Tastatur Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default Layer
    [BASE] = LAYOUT_ortho_5x15(
        KC_ESC,             KC_GRV,     KC_QUOT,	KC_BSLS,        XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_MINS,    KC_EQL,         KC_LBRC,    KC_RBRC,    KC_DEL,             KC_7,       KC_8,       KC_9,       \
        KC_TAB,             KC_Q,       KC_W,	    KC_E,           KC_R,       KC_T,       KC_Z,       KC_U,       KC_I,           KC_O,       KC_P,       KC_ENT, 	        KC_4,       KC_5,       KC_6,       \
        LM(CAPS, MOD_LSFT), KC_A,       KC_S,	    KC_D,           KC_F,       KC_G,       KC_H,       KC_J,       KC_K,           KC_L,       KC_SCLN,    LM(CAPS, MOD_RSFT), KC_1,       KC_2,       KC_3,       \
        KC_LCTL,	        KC_COMM,    KC_Y,       KC_X,           KC_C,       KC_V,       KC_B,       KC_N,       KC_M,           KC_DOT, 	KC_SLSH,    KC_RCTL,            KC_0,       KC_UP,   	KC_PENT,    \
        KC_LGUI,            KC_VOLD,    KC_VOLU,    TT(SPECIAL),    KC_LALT,    KC_SPC,     KC_BSPC,    KC_RALT,    TT(SPECIAL),    KC_HOME,    KC_END,     KC_RGUI, 	        KC_LEFT,    KC_DOWN, 	KC_RGHT     \
    ),
    // Shift-Layer
    [CAPS] = LAYOUT_ortho_5x15(
        _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    KC_KP_7,    KC_KP_8,    KC_KP_9,    \
        _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    KC_KP_4,    KC_KP_5,    KC_KP_6,    \
        KC_CAPS,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,                _______,    _______,    KC_CAPS,    KC_KP_1,    KC_KP_2,    KC_KP_3,    \
        _______,    _______,    _______,    _______,                _______,    _______,    _______,    _______,    _______,                _______,    _______,    _______,    KC_KP_0,    _______,    _______,    \
        _______,    _______,    _______,    LM(SPECIAL, MOD_LSFT),  _______,    _______,    _______,    _______,    LM(SPECIAL, MOD_RSFT),  _______,    _______,    _______,    _______,    _______,    _______     \
    ),
    // FN-Reihe
    [SPECIAL] = LAYOUT_ortho_5x15(
        TO(BASE),               KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,   KC_PERC,  KC_CIRC,    KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,    QK_BOOT,                KC_F7,      KC_F8,      KC_F9,    \
        TG(BASE),               _______,    _______,    KC_UP,      _______,  _______,  _______,    KC_KP_7,  KC_KP_8,  KC_KP_9,  _______,    KC_PENT,                KC_F4,      KC_F5,      KC_F6,    \
        LM(SPECIAL, MOD_LSFT),  _______,    KC_LEFT,    KC_DOWN,    KC_RIGHT, _______,  _______,    KC_KP_4,  KC_KP_5,  KC_KP_6,  _______,    LM(SPECIAL, MOD_RSFT),  KC_F1,      KC_F2,      KC_F3,    \
        _______,                _______,    _______,    _______,    _______,  _______,  _______,    KC_KP_1,  KC_KP_2,  KC_KP_3,  _______,    _______,                KC_F10,     KC_F11,     KC_F12,   \
        _______,                KC_BRID,    KC_BRIU,    _______,    _______,  KC_MPLY,  KC_DEL,     KC_KP_0,  _______,  KC_PGUP,  KC_PGDN,    MO(MOUSE),              KC_MPRV,    KC_MUTE,    KC_MNXT   \
    ),
    // Mouse-Layer
    [MOUSE] = LAYOUT_ortho_5x15(
        TO(BASE),   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_WH_U,    _______,    KC_WH_D,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BTN1,    KC_MS_U,    KC_BTN2,    \
        RGB_TOG,    RGB_RMOD,   RGB_MOD,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    RGB_HUD,    RGB_HUI,    KC_MS_L,    KC_MS_D,    KC_MS_R     \
    ),
/*    [MIDI] = LAYOUT_ortho_5x15(
        TG(MIDI),   MI_Cs_3,    MI_Ds_3,    XXXXXXX,    MI_Fs_3,    MI_Gs_3,    MI_As_3,    XXXXXXX,    MI_Cs_4,    MI_Ds_4,    XXXXXXX,    MI_Fs_4,    MI_Gs_4,    MI_As_4,    XXXXXXX,    \
        MI_B_2,     MI_C_3,     MI_D_3,     MI_E_3,     MI_F_3,     MI_G_3,     MI_A_3,     MI_B_3,     MI_C_4,     MI_D_4,     MI_E_4,     MI_F_4,     MI_G_4,     MI_A_4,     MI_B_4,     \
        XXXXXXX,    MI_Cs_1,    MI_Ds_1,    XXXXXXX,    MI_Fs_1,    MI_Gs_1,    MI_As_1,    XXXXXXX,    MI_Cs_2,    MI_Ds_2,    XXXXXXX,    MI_Fs_2,    MI_Gs_2,    MI_As_2,    XXXXXXX,    \
        MI_B,       MI_C_1,     MI_D_1,     MI_E_1,     MI_F_1,     MI_G_1,     MI_A_1,     MI_B_1,     MI_C_2,     MI_D_2,     MI_E_2,     MI_F_2,     MI_G_2,     MI_A_2,     MI_B_2,     \
        MI_OCTD,    MI_VELD,    MI_VEL_8,   MI_LEG,     MI_SUS,     MI_SUS,     MI_ALLOFF,  MI_SUS,     MI_LEG,     MI_OCT_2,   XXXXXXX,    MI_OCTU,    MI_TRNSD,   MI_TRNS_0,  MI_TRNSU    \
)*/
};
/*
[LAYER] = LAYOUT_ortho_5x15(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    \
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______     \
    )
*/
