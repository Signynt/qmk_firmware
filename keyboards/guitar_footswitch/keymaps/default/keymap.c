/*
qmk compile -kb guitar_footswitch -km default
*/

#include QMK_KEYBOARD_H

extern MidiDevice midi_device;

#define MIDI_CC_OFF 0
#define MIDI_CC_ON  127

#define PEDAL_1  24
#define PEDAL_2  25
#define PEDAL_3  26
#define PEDAL_4  27
#define PEDAL_5  28
#define PEDAL_6  29
#define PEDAL_7  30
#define PEDAL_8  31

enum custom_keycodes {
    MIDI_SWITCH_1 = SAFE_RANGE,
    MIDI_SWITCH_2, 
    MIDI_SWITCH_3, 
    MIDI_SWITCH_4, 
    MIDI_SWITCH_5, 
    MIDI_SWITCH_6, 
    MIDI_SWITCH_7, 
    MIDI_SWITCH_8, 
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){

        case MIDI_SWITCH_1:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_1, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_1, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_2:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_2, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_2, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_3:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_3, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_3, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_4:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_4, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_4, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_5:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_5, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_5, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_6:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_6, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_6, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_7:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_7, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_7, MIDI_CC_OFF);
                }
            }
            break;

        case MIDI_SWITCH_8:
            if (record->event.pressed) {
                static bool is_toggled;
                is_toggled ^= 1;
                if (is_toggled) { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_8, MIDI_CC_ON);
                } else { 
                    midi_send_cc(&midi_device, midi_config.channel, PEDAL_8, MIDI_CC_OFF);
                }
            }
            break;

    }
    return true;

};

//define layers
enum layers {UPPER, MID, LOWER};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [UPPER] = LAYOUT(
        TO(UPPER),   MIDI_SWITCH_2,   MIDI_SWITCH_3,    MIDI_SWITCH_4,
        TO(MID),     MIDI_SWITCH_6,   MIDI_SWITCH_7,    MIDI_SWITCH_8
    ),
    [MID] = LAYOUT(
        TO(UPPER),    MI_C,    MI_D,   MI_E,
        TO(MID),    MI_F,    MI_G,   MI_A
    ),
    [LOWER] = LAYOUT(
        TO(MID),    MI_C,    MI_D,   MI_E,
        TO(UPPER),  MI_F,    MI_G,   MI_A
    )
};
