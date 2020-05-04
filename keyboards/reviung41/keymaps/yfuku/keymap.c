/* Copyright 2020 gtips
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
#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VD KC__VOLDOWN
#define KC_VU KC__VOLUP

// layer
#define KC_L_SPC LT(_LOWER, KC_SPC)
#define KC_R_ENT LT(_RAISE, KC_ENT)

// shift_t
#define KC_S_EN LSFT_T(KC_LANG2)
#define KC_S_JA LSFT_T(KC_LANG1)

// cmd_t
#define KC_G_F LCMD_T(KC_F)
#define KC_G_J RCMD_T(KC_J)

// ctl_t
#define KC_C_G LCTL_T(KC_G)
#define KC_C_H RCTL_T(KC_H)

// alt_t
#define KC_A_D ALT_T(KC_D)
#define KC_A_K ALT_T(KC_K)

// cmd+shift_t
#define KC_GS_S SCMD_T(KC_S)
#define KC_GS_L SCMD_T(KC_L)

//
#define KC_G_BS LCMD(KC_BSPC)
#define KC_MISS C(KC_UP)
#define KC_LEAD LT(_ADJUST, KC_LEFT)


#define TAPPING_LAYER_TERM 240
uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case KC_GS_S:
      return TAPPING_LAYER_TERM;
    case KC_GS_L:
      return TAPPING_LAYER_TERM;
    case KC_A_D:
      return TAPPING_LAYER_TERM;
    case KC_A_K:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,----+----+----+----+----+----.       ,----+----+----+----+----+----.
      ESC, Q  , W  , E  , R  , T  ,         Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|       |----+----+----+----+----+----|
      TAB, A  ,GS_S,A_D ,G_F ,C_G ,         C_H ,G_J ,A_K ,GS_L,SCLN,ESC ,
  //|----+----+----+----+----+----+       |----+----+----+----+----+----|
     LEAD, Z  , X  , C  , V  , B  ,         N  , M  ,COMM,DOT ,SLSH,RGHT,
  //`----+----+----+----+----+----/       \----+----+----+----+----+----'
                         S_EN,L_SPC, BSPC ,R_ENT,S_JA
  //          `----+----+----+----'       `----+----+----+----'
  ),

  //   \ ! & |      = + * %
  //   # ` " ' ~  ← ↓ ↑ → $
  //       { [ (  ) ] } @ ^

  [_RAISE] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         ,BSLS,EXLM,AMPR,PIPE,XXXX,      XXXX,EQL ,PLUS,ASTR,PERC,MINS,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,HASH,GRV ,DQT ,QUOT,TILD,      LEFT,DOWN, UP ,RGHT,DLR ,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,    ,    ,LCBR,LBRC,LPRN,      RPRN,RBRC,RCBR,AT  ,CIRC,    ,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
                             ,BSPC,     ,    ,RST
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,XXXX,      XXXX,EQL ,PLUS,ASTR,PERC,MINS,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         , 1  , 2  , 3  , 4  , 5  ,       6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,          ,    ,COMM,DOT ,SLSH,    ,
  //`----+----+----+--+-+----+----/     \----+----+----+----+----+----'
                             ,    ,     ,DEL ,     
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

