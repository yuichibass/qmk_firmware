/* Copyright 2020 monksoffunk
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEACB
#define DEVICE_VER      0x0003
#define MANUFACTURER    monksoffunk
#define PRODUCT         Attack25 rev3
#define DESCRIPTION     5x5 Keyboard Pad

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B7, B6, B5, B4, F7 }
#define MATRIX_COL_PINS { F5, F6, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define LED_ANIMATIONS

/* Blink feature at Windows/Macintosh mode change */
#define MODE_BLINK_ENABLE

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1 // Custom config starts after VIA's EEPROM usage

#define attack25_rev3x

/* for Alps Encoders */
// #define ENCODER_RESOLUTION 2
