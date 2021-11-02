/* Copyright 2019 niltea
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
///////////////////////////////////



#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
// enum layer_names {
//     _0,
//     _1,
//     _2,
//     _3
// };



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
      G(KC_0),      S(C(KC_COMM)),          C(KC_M),                           S(C(KC_DOT)),            G(KC_S),                  KC_NO,  KC_NO,
      KC_KP_1,      A(G(KC_DOWN)),          A(G(KC_UP)),                       LSFT(KC_O),              MT(MOD_LALT, KC_JYEN),    KC_NO,  KC_NO,
                    KC_KP_4,                KC_KP_5,                           KC_KP_6,                 KC_KP_PLUS                
                  
    ),
  
    [1] = LAYOUT(
      KC_A,         KC_ENTER,               KC_C,                              KC_A,                    KC_NO,                    KC_NO,  KC_NO,
      S(G(KC_K)),   G(KC_K),                KC_BSPC,                           KC_KP_EQUAL,             KC_NO,                    KC_NO,  KC_NO,
                    KC_NO,                  KC_NO,                             KC_NO,                   KC_NO
                
    ), 
  
    [2] = LAYOUT(
      G(A(KC_M)),   S(G(KC_M)),             S(KC_M),                           KC_A,                    KC_NO,                    KC_NO,  KC_NO,
      S(KC_A),      S(G(KC_G)),             G(KC_G),                           KC_A,                    KC_NO,                    KC_NO,  KC_NO,
                    KC_NO,                  KC_NO,                             KC_NO,                   KC_NO
                   
    ),
  
    [3] = LAYOUT(
      G(A(KC_M)),   S(G(KC_M)),             S(KC_M),                           KC_A,                    KC_NO,                    KC_NO,  KC_NO,
      S(KC_A),      S(G(KC_G)),             G(KC_G),                           KC_A,                    KC_NO,                    KC_NO,  KC_NO,
                    KC_NO,                  KC_NO,                             KC_NO,                   KC_NO
                 
    )
};


keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 0, .col = 5},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 0, .col = 6},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 1, .col = 5},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 1, .col = 6},
    .pressed = false
};



void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (IS_PRESSED(encoder2_ccw)) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }

}

void led_set_user(uint8_t usb_led) {

}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }

    
}
return true;
}