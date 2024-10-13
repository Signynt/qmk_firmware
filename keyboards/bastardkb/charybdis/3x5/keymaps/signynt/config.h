/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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
#pragma once

/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { F7, C6, D4, B5 }
#define MATRIX_COL_PINS \
    { F5, B6, D7, E6, B4 }

/* Handedness. */
#define MASTER_RIGHT

/* #define FORCE_NKRO */

/* serial.c configuration (for split keyboard). */
#define SOFT_SERIAL_PIN D2

/* RGB settings. */
#define RGB_DI_PIN D3

/* PMW3360 settings. */
#define PMW3360_CS_PIN F0
// #define COMBO_COUNT 8

#define TAPPING_TERM 160
// #define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
// #define BILATERAL_COMBINATIONS

//Trackball settings

#define CHARYBDIS_DRAGSCROLL_DPI 100
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
//#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
//#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 400
//#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 0

// Save space
#undef SPLIT_POINTING_ENABLE
#undef POINTING_DEVICE_RIGHT
//#undef RGB_MATRIX_ENABLE

/* RGB Matrix. */

//      #ifdef RGB_MATRIX_ENABLE
//      // Disable control of RGB matrix by keycodes (must use firmware implementation
//      // to control the feature).
//      #    define RGB_MATRIX_DISABLE_KEYCODES
//      
//      // Limit maximum brightness to keep power consumption reasonable, and avoid
//      // disconnects.
//      #    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
//      #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 64
//      
//      // Rainbow swirl as startup mode.
//      #    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//      #    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
//      
//      // Slow swirl at startup.
//      #    define RGB_MATRIX_STARTUP_SPD 32
//      
//      // Startup values.
//      #    define RGB_MATRIX_STARTUP_HUE 0
//      #    define RGB_MATRIX_STARTUP_SAT 255
//      #    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
//      #    define RGB_MATRIX_STARTUP_HSV RGB_MATRIX_STARTUP_HUE, RGB_MATRIX_STARTUP_SAT, RGB_MATRIX_STARTUP_VAL
//      #endif  // RGB_MATRIX_ENABLE
//      