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
    _LOWER  = 2,
    _ADJUST = 3,
};

//#define MO(1) // lower
//#define MO(2)  // raise
#define KC_G_JA LGUI_T(KC_LANG1)     // cmd or win
#define KC_G_EN LGUI_T(KC_LANG2)     // cmd or win
#define KC_C_BS LCTL_T(KC_BSPC)      // ctrl
#define KC_A_DEL ALT_T(KC_DEL)       // alt
#define KC_BQ LALT(KC_TILD)          // backquote
#define JA_CLON KC_QUOT  // : and +
#define JA_AT   KC_LBRC  // @ and `
#define JA_HAT  KC_EQL   // ^ and ~
#define JA_ENUN KC_RO    // \ and _ (EN mark and UNder score)
#define JA_ENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define JA_LBRC KC_RBRC  // [ and {
#define JA_RBRC KC_BSLS  // ] and }
#define JP_TILD S(JP_CIRC) // ~

//  RGUI(RALT(KC_5))  take screenshot
//  LGUI(KC_C)        copy
//  LGUI(KC_V)        paste
//  LGUI(KC_X)        cut
//  KC_F6             start and stop playing
//  KC_F11            increase the audio volume
//  KC_F12            decrease the audio volume
//  KC_F16            Start original apple script and show dictionary tool window in Mac OS
//  KC_INT1           backslash


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
       KC_TAB , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_RCTRL, KC_A   , KC_S    , KC_D   , KC_F   , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, KC_QUOT,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
       KC_LALT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_RSFT,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                         MO(2),    KC_SPC, KC_LGUI,   KC_BSPC,     KC_ENT, KC_LSFT,   KC_SPC,  MO(1)
    ),

    [_RAISE] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       JA_AT,   KC_PCMM, KC_7,    KC_8,    KC_9,    KC_PPLS,      KC_JYEN, KC_F11,  KC_F12,   KC_F8, KC_NO, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS, KC_PDOT, KC_4,    KC_5,    KC_6,    KC_PMNS,      KC_RO,  KC_PGUP,  KC_HOME , LGUI(KC_X), KC_NO, KC_ENT,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS,   KC_0,   KC_1,   KC_2,    KC_3,    KC_PEQL,      KC_NUBS, KC_PGDOWN, KC_END , LGUI(KC_C) , LGUI(KC_V),  KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),


   // @     , 7 8 9 +    ¥ F11 F12 F6 No BS
   // ctrl  . 4 5 6 -    _ UP HOME CUT No ENT
   // alt   0 1 2 3 =    § DOWN END COPY PASTE SFT
   

    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS, JA_ENUN, JA_ENVL, KC_KP_SLASH, JP_PERC, JP_LCBR,     JP_RCBR, KC_LEFT, KC_DOWN, KC_RGHT, RGUI(RALT(KC_5)), KC_ENT,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS, KC_INT1, JA_ENUN, KC_TILD, JP_QUES, JP_LBRC,         JP_RBRC, LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), LGUI(KC_S),   KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

       // ESC   ^ _ * ` (    ) F16 UP BS No No
   // ctrl  _ ¥ / % {    } LEFT DOWN RGHT SCRST ENT
   // alt   ] _ ~ ? [    ] COPY PASTE CUT SAVE SFT


    [_ADJUST] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
       KC_1,  JA_HAT,  JA_ENUN, KC_KP_ASTERISK, JP_GRV,  JP_LPRN,  JP_RPRN, KC_F16,  KC_UP,   KC_BSPC, KC_NO, KC_NO,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS, JA_ENUN, JA_ENVL, KC_KP_SLASH, JP_PERC, JP_LCBR,     JP_RCBR, KC_LEFT, KC_DOWN, KC_RGHT, RGUI(RALT(KC_5)), KC_ENT,
    //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
       KC_TRNS, KC_INT1, JA_ENUN, KC_TILD, JP_QUES, JP_LBRC,         JP_RBRC, LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), LGUI(KC_S),   KC_TRNS,
    //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS 
    //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
    ),

       // ESC   ^ _ * ` (    ) F16 UP BS No No
   // ctrl  _ ¥ / % {    } LEFT DOWN RGHT SCRST ENT
   // alt   ] _ ~ ? [    ] COPY PASTE CUT SAVE SFT


};





