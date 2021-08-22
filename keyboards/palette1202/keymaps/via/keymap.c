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






const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_0] = LAYOUT(
      G(KC_0),      S(C(KC_COMM)),          C(KC_M),                           S(C(KC_DOT)),             G(KC_S),
      KC_KP_1,      A(G(KC_DOWN)),          A(G(KC_UP)),                       LSFT(KC_O),               MT(MOD_LALT, KC_JYEN),
                    KC_KP_4,                LT(_2_Mac_P, KC_KP_5),             LT(_1_Mac_P, KC_KP_6),    LT(_SPECIAL, KC_KP_PLUS)
    ),
    [_1] = LAYOUT(
      KC_A,         KC_ENTER,               KC_C,                              KC_V,                     KC_SLSH,
      S(G(KC_K)),   G(KC_K),                KC_BSPC,                           KC_KP_EQUAL,              KC_MUTE,
                    KC_KP_EQUAL ,           TD(TD_CV),                         _______,                  G(KC_V)
    ), 
    [_2] = LAYOUT(
      G(A(KC_M)),   S(G(KC_M)),             S(KC_M),                           KC_M,                     _______,
      S(KC_A),      S(G(KC_G)),             G(KC_G),                           KC_A,                     _______,
                    S(KC_K),                _______,                           G(KC_SPC),                A(KC_K)
    ),
    [_3] = LAYOUT(
      G(A(KC_M)),   S(G(KC_M)),             S(KC_M),                           KC_M,                     _______,
      S(KC_A),      S(G(KC_G)),             G(KC_G),                           KC_A,                     _______,
                    S(KC_K),                _______,                           G(KC_SPC),                A(KC_K)
    )
};

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