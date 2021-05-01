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
#include QMK_KEYBOARD_H
#ifdef OLED_DRIVER_ENABLE
  #include <string.h>
  #include "lib/oled_helper.h"
#endif

// Windows/Mac デフォではWin、Premiereスタート
// これを変えたければ以下のフラグと、このあとのenum layerIDでの構造変更をすること
static bool Win_or_Mac = true;
//Premiere or AfterEffects
static bool P_or_AE = true;

// LAYER
//Premiereに3レイヤー、AEに3レイヤー、それぞれWinMac、共通でテンキーとスイッチレイヤー
enum layerID {
  // Win
  _0_Win_P = 0,  // default layer
  _1_Win_P,
  _2_Win_P,
  // ３レイヤーごとにペアになっているので、デフォにしたいものを３レイヤーごとここにもってくるとデフォを変えられるよ
  // 最後の切り替えマクロ200行以降でベースレイヤーをどれにしたかで処理を変えること

  _0_Win_AE,
  _1_Win_AE,
  _2_Win_AE,

  // Mac
  _0_Mac_P,
  _1_Mac_P,
  _2_Mac_P,

  _0_Mac_AE,
  _1_Mac_AE,
  _2_Mac_AE,
  // テンキーと切り替えレイヤー
  _ten,
  _SWITCH,
};

// MACRO
enum custom_keycodes {
  // Win/Mac Premiere/AfrerEffects切り替え用
  MC_Win_P = SAFE_RANGE,
  MC_Mac_P,
  MC_Win_AE,
  MC_Mac_AE,
};


// KEYMAP //////////////////////////////////////////////////////////////
// 一段目 1,2,3,4, 上のエンコのクリック,
// 二段目 1,2,3,4, 下のエンコのクリック,
//    親指  1,2,3, 4
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 注：LT(),MT()の中のキーは、Basic Keycodesでないといけない制約がある。なのでレイヤーキーの単キーは、単純なキーという縛りがあるよ。
    ///////////////////Windows
    // Win Premiere
    [_0_Win_P] = LAYOUT(
      KC_UP,               KC_DOWN,     KC_LEFT,                KC_RGHT,             KC_K,
      LT(_ten, KC_ENTER),  C(KC_Z),     MT(MOD_LCTL, KC_BSPC),  MT(MOD_LSFT, KC_V),  LT(_SWITCH, KC_JYEN),
                           C(S(KC_Z)),  C(KC_K),                LT(_2_Win_P, KC_C),  LT(_1_Win_P, KC_SPC)
    ),
    [_1_Win_P] = LAYOUT(
      S(KC_I),      S(KC_O),     S(KC_LEFT),   S(KC_RGHT),   _______,
      C(KC_C),      C(KC_V),     KC_Q,         KC_W,         _______,
                    C(KC_S),     C(S(KC_A)),   C(KC_A),      _______
    ),
    [_2_Win_P] = LAYOUT(
      KC_I,         KC_O,        C(S(KC_M)),   S(KC_M),   _______,
      C(S(KC_I)),   C(S(KC_O)),  C(A(KC_M)),   KC_M,      _______,
                    KC_MUTE,     KC_F,         _______,   _______
    ),
    // Win AfterEffects
    [_0_Win_AE] = LAYOUT(
      C(S(A(KC_LEFT))),    C(S(A(KC_RGHT))),    C(KC_LEFT),             C(KC_RGHT),          S(KC_SLSH),
      LT(_ten, KC_ENTER),  C(KC_Z),             MT(MOD_LCTL, KC_BSPC),  MT(MOD_LSFT, KC_V),  LT(_SWITCH, KC_SCLN),
                           C(S(KC_Z)),          C(S(KC_D)),             LT(_2_Win_AE, KC_H), LT(_1_Win_AE, KC_SPC)
    ),
    [_1_Win_AE] = LAYOUT(
      KC_J,         KC_K,        C(S(KC_LEFT)), C(S(KC_RGHT)), _______,
      C(KC_C),      C(KC_V),     A(KC_RBRC),    A(KC_BSLS),    _______,
                    C(KC_S),     KC_RBRC,       KC_BSLS,       _______
    ),
    [_2_Win_AE] = LAYOUT(
      KC_R,         KC_S,        KC_P,          KC_A,               _______,
      KC_E,         KC_M,        KC_T,          MT(MOD_LSFT, KC_U), _______,
                    C(A(KC_S)),  C(A(KC_B)),    _______,            C(A(KC_SLSH))
    ),

   /////////////////////Mac
   // Mac Premiere
   [_0_Mac_P] = LAYOUT(
      KC_UP,               KC_DOWN,     KC_LEFT,                KC_RGHT,             KC_K,
      LT(_ten, KC_ENTER),  G(KC_Z),     MT(MOD_LCTL, KC_BSPC),  MT(MOD_LSFT, KC_V),  LT(_SWITCH, KC_JYEN),
                           G(S(KC_Z)),  G(KC_K),                LT(_2_Mac_P, KC_C),  LT(_1_Mac_P, KC_SPC)
    ),
    [_1_Mac_P] = LAYOUT(
      S(KC_I),      S(KC_O),     S(KC_LEFT),   S(KC_RGHT),   _______,
      G(KC_C),      G(KC_V),     KC_Q,         KC_W,         _______,
                    G(KC_S),     G(S(KC_A)),   G(KC_A),      _______
    ),
    [_2_Mac_P] = LAYOUT(
      KC_I,         KC_O,        G(S(KC_M)),   S(KC_M),   _______,
      G(S(KC_I)),   G(S(KC_O)),  G(A(KC_M)),   KC_M,      _______,
                    KC_MUTE,     KC_F,         _______,   _______
    ),
    // Mac AfterEffects
    [_0_Mac_AE] = LAYOUT(
      G(S(A(KC_LEFT))),    G(S(A(KC_RGHT))),    G(KC_LEFT),             G(KC_RGHT),          S(KC_SLSH),
      LT(_ten, KC_ENTER),  G(KC_Z),             MT(MOD_LCTL, KC_BSPC),  MT(MOD_LSFT, KC_V),  LT(_SWITCH, KC_SCLN),
                           G(S(KC_Z)),          G(S(KC_D)),             LT(_2_Mac_AE, KC_H), LT(_1_Mac_AE, KC_SPC)
    ),
    [_1_Mac_AE] = LAYOUT(
      KC_J,         KC_K,        G(S(KC_LEFT)), G(S(KC_RGHT)), _______,
      G(KC_C),      G(KC_V),     A(KC_RBRC),    A(KC_BSLS),    _______,
                    G(KC_S),     KC_RBRC,       KC_BSLS,       _______
    ),
    [_2_Mac_AE] = LAYOUT(
      KC_R,         KC_S,        KC_P,          KC_A,               _______,
      KC_E,         KC_M,        KC_T,          MT(MOD_LSFT, KC_U), _______,
                    G(A(KC_S)),  G(A(KC_B)),    _______,            G(A(KC_SLSH))
    ),

    // テンキー
    [_ten] = LAYOUT(
      KC_DOT,       KC_1,        KC_2,          KC_3,       _______,
      _______,      KC_4,        KC_5,          KC_6,       KC_MINUS,
                    KC_7,        KC_8,          KC_9,       KC_0
    ),
    /////// Switch OS/Aplication
    [_SWITCH] = LAYOUT(
      _______,    _______,     MC_Win_P,     MC_Win_AE,     _______,
      _______,    _______,     MC_Mac_P,     MC_Mac_AE,     _______,
                  _______,     _______,      _______,       _______
    ),

};

// エンコーダ― Premiere/AfterEffectsでキーバインド切り替える
void encoder_update_user(uint8_t index, bool clockwise) {
  if (P_or_AE) {
  ///// Premiere
    if (index == 0) { /* the upper encoder */
      if (clockwise) {
        SEND_STRING(SS_TAP(X_L));
        // clockwise: KC_L
      } else {
        SEND_STRING(SS_TAP(X_J));
        // couterclockwise: KC_J
      }
    } else if (index == 1) { /* the lower encoder */
      if (clockwise) {
        SEND_STRING("'");
        // clockwise: timeline scale +
        // 日本語の:キーをUSで打っているので。
      } else {
        SEND_STRING("-");
        //counterclockwise: timeline scale -
      }
    }
  } else {
  ////// AfterEffects
    if (index == 0) { /* the upper encoder */
      if (clockwise) {
        SEND_STRING(SS_TAP(X_DOT));
        // clockwise: KC_DOT
      } else {
        SEND_STRING(SS_TAP(X_COMMA));
        // couterclockwise: KC_COMMA
      }
    } else if (index == 1) { /* the lower encoder */
      if (clockwise) {
        SEND_STRING("=");
        // clockwise: timeline scale +
        // 日本語の^キーをUSで打っているので。
      } else {
        SEND_STRING("-");
        //counterclockwise: timeline scale -
      }
    }
  }
}

// Macros ///////////////////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Win/Mac, Premiere/AfterEffectsのレイヤーの切り替え
    case MC_Win_P:
      if (record->event.pressed) {
        layer_clear();
        //Windows/Premiereはベースレイヤーなのでクリアするだけでよい
        // もしベースレイヤーを変更したら以下を生かしてね
        // layer_on(_0_Win_P);
        Win_or_Mac = true;
        P_or_AE = true;
      }
      break;
    case MC_Win_AE:
      if (record->event.pressed) {
        layer_clear();
        layer_on(_0_Win_AE);
        Win_or_Mac = true;
        P_or_AE = false;
      }
      break;
    case MC_Mac_P:
      if (record->event.pressed) {
        layer_clear();
        layer_on(_0_Mac_P);
        Win_or_Mac = false;
        P_or_AE = true;
      }
      break;
    case MC_Mac_AE:
      if (record->event.pressed) {
        layer_clear();
        layer_on(_0_Mac_AE);
        Win_or_Mac = false;
        P_or_AE = false;
      }
      break;
  }
  return true;
};