/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_jp.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE  = 1,
    _LOWER = 2,
};

//#define MO(1) // lower
//#define MO(2)  // raise
#define KC_G_JA LGUI_T(KC_LANG1)     // cmd or win
#define KC_G_EN LGUI_T(KC_LANG2)     // cmd or win
#define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
#define KC_A_DEL ALT_T(KC_DEL)       // alt
#define KC_BQ LALT(KC_TILD)          // backquote

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
       KC_TAB , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_RCTRL, KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_LALT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                         MO(1), KC_SPC, KC_BSPC, KC_LGUI, KC_RSFT, KC_ENT, KC_SPC, MO(2)
    ),

    [_RAISE] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       KC_ESC, KC_F16,  KC_UP,   KC_NO,   JP_GRV,   JP_LPRN,     JP_RPRN, KC_F16,  KC_UP,    KC_BSPC, KC_NO, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT, JP_PERC, JP_LCBR,     JP_RCBR, JP_RCBR, KC_DOWN, KC_RGHT, RGUI(RALT(KC_5)), KC_ENT,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_LSFT, KC_NO,   KC_LSFT, KC_NO,   JP_QUES, JP_LBRC,     JP_RBRC, LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), KC_NO,   KC_RSFT,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_SPC, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_SPC, KC_TRNS 
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       JP_AT,   KC_PDOT, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,     KC_JYEN, KC_F11,   KC_F12,  KC_PGUP, RGUI(KC_S), KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_LGUI, KC_PCMM, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,     KC_RO,   KC_PGUP,  KC_HOME , LGUI(KC_X), UNICODE_MODE_MAC, KC_ENT,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_LSFT,   KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PPLS,   KC_NUBS, KC_PGDOWN, KC_END , LGUI(KC_C) , LGUI(KC_V),  KC_RSFT,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_LCTL, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_RSFT, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),
};

/* Shifted symbols
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │ ! │ " │ # │ $ │ % │ & │ ' │ ( │ ) │   │ = │ ~ │ | │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │   │   │   │   │   │   │   │   │   │ ` │ { │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │ Caps │   │   │   │   │   │   │   │   │   │ + │ * │ } │    │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤
 * │        │   │   │   │   │   │   │   │ < │ > │ ? │ _ │      │
 * ├─────┬──┴┬──┴──┬┴───┴┬──┴───┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬─────┤
 * │     │   │     │     │         │     │   │   │   │   │     │
 * └─────┴───┴─────┴─────┴─────────┴─────┴───┴───┴───┴───┴─────┘
 */


