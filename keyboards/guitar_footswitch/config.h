// Copyright 2022 Vincenzo Mitchell Barroso (@Signynt)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MIDI_ADVANCED

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4321
#define PRODUCT_ID      0x1234
#define DEVICE_VER      0x0001
#define MANUFACTURER    Signynt
#define PRODUCT         QMK_footswitch

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define DIRECT_PINS { { B1, F4, C6, E6 }, { B2, B6, B5, B4 } }
// #define DIODE_DIRECTION COL2ROW
// wiring of each half
// #define MATRIX_ROW_PINS { B0, B1 }
// #define MATRIX_COL_PINS { B2, B3, B4, B5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
