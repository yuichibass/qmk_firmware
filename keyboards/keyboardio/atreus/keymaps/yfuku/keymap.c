// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
};

#define L_SPC LT(_LOWER, KC_SPC)
#define R_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
KC_Q,    KC_W,         KC_E,         KC_R,             KC_T,                          KC_Y,           KC_U,             KC_I,         KC_O,         KC_P,
KC_A,    SGUI_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),     LCTL_T(KC_G),                  RCTL_T(KC_H),   RGUI_T(KC_J),     RALT_T(KC_K), SGUI_T(KC_L), KC_SCLN,
KC_Z,    KC_X,         KC_C,         KC_V,             KC_B,          KC_NO,  KC_NO,  KC_N,           KC_M,             KC_COMM,      KC_DOT,       KC_SLSH,
KC_LEFT, KC_DOWN,      KC_NO,        LSFT_T(KC_LANG2), LT(1, KC_SPC), KC_TAB, KC_ESC, LT(2, KC_ENT),  LSFT_T(KC_LANG1), KC_NO,        KC_UP,        KC_RIGHT
    ),
    [_LOWER] = LAYOUT(
KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,                      KC_MINS, KC_EQL,  KC_PLUS,  KC_ASTR, KC_PERC,
KC_1,  KC_2,    KC_3,  KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,     KC_9,    KC_0,
KC_NO, KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_TRNS,  KC_TRNS, KC_NO,   KC_NO,   KC_TRNS,  KC_TRNS, KC_TRNS,
RESET, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS
    ),
    [_RAISE] = LAYOUT(
KC_BSLS, KC_EXLM, KC_AMPR, KC_PIPE, KC_NO,                     KC_MINS,  KC_EQL, KC_PLUS,   KC_ASTR, KC_PERC,
KC_HASH, KC_GRV,  KC_DQUO, KC_QUOT, KC_TILD,                   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, KC_DLR,
KC_NO,   KC_NO,   KC_LCBR, KC_LBRC, KC_LPRN, KC_TRNS, KC_TRNS, KC_RPRN,  KC_RBRC,  KC_RCBR, KC_AT,   KC_CIRC,
KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_BSPC, KC_TRNS, KC_RPRN, KC_RPRN,  KC_RPRN,  KC_RPRN, KC_RPRN, RESET
   ),
};
