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

// Windows/Mac デフォでは電源オンで、WinかつPremiereになる
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
  // 3レイヤーごとにペアになっているので、デフォにしたいものを３レイヤーごとここにもってくるとデフォを変えられるよ
  // 最後の切り替えマクロ280行以降でベースレイヤーをどれにしたかで処理を変えること
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
  MC_5FL,
  MC_5FR,
};

// KEYMAP overview//////////////////////////////////////////////////////////////
/////Premiere///////////////////
//    Copy    |  Paste   |    選択ツール   | カミソリツール/Shift ||   Undo      (( Save  ))  Redo
//    巻き戻し  |  早送り   |     1F ← /Alt |    1F →  /Ctrl ||   TL Zoom In(( TL全体 )) TL Zoom Out
//            |  Undo    |    前の編集点  |    次の編集点    ||   再生、停止
//
//  Layer 1
//            | マーカー消去 |    In点設定   |    Out点設定    ||             ((       ))
//   前のマーカー | 次のマーカー |     5F ←      |    5F →        ||             ((       ))
//            |   マーク    |    In点へ     |    Out点へ      ||   *****ここを押しながら********
//  Layer 2
//   1F Export|マッチフレーム |  ***********  |        BS      ||             ((       ))  
//            |          |  Clear All    |    Select All  ||   Vol -    ((  Mute  ))   Vol +
//            |          |前の編集点までカット| 次の編集点までカット ||   編集点追加
//
/////After Effects///////////////////
//    Copy    |  Paste   |    選択ツール   |  ハンドツール/Shift ||   Undo      (( Save  ))  Redo
//    前のキーF | 後のキーF  |     1F ← /Alt |    1F →  /Ctrl ||   TL Zoom In(( TL全体 )) TL Zoom Out
//            |  Undo    |    前の編集点  |    次の編集点    ||   再生、停止
//
//  Layer 1
//   T 透明度タブ|P 位置タブ  | ワークIn点設定 | ワークOut点設定   ||             ((M マスクタブ  ))
//   R 回転タブ  |S スケールタブ|     5F ←    |     5F →       ||             ((E エフェクトタブ))
//             |U キーFタブ  |   ワークIn点へ  |   ワークOut点へ   ||   *****ここを押しながら********
//  Layer 2
//   1F Export  |  Dupe   | *********** |        BS      ||            ((       ))  
//   素材の差し替え|         |  レイヤーIn移動 | レイヤーOut移動   ||   Vol -    ((  Mute  ))   Vol +
//              |         |ここからInまで消去|ここからOutまで消去 ||    レイヤー分割
//
/////Ten Key///////////////////
//       0     |     1    |      2      |        3      ||             ((   -    ))
//   **********|     4    |      5      |        6      ||             ((   .    ))
//             |     7    |      8      |        9      ||                Enter
/////切り替え///////////////////
//             |          |    Win P    |     Win AE    ||             ((        ))  
//             |          |    Mac P    |     Mac AE    ||             ((********))
//             |          |             |               ||   

// KEYMAP 本体//////////////////////////////////////////////////////////////
// 一段目 1,2,3,4, 上のエンコのクリック,
// 二段目 1,2,3,4, 下のエンコのクリック,
//    親指  1,2,3, 4
// エンコーダーの回転はキーマップ以外で定義（196行以降）
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 注：LT(),MT()の中のキーは、Basic Keycodesでないといけない制約がある。なのでレイヤーキーの単キーは、単純なキーという縛りがあるよ。
    ///////////////////Windows
    // Win Premiere
    [_0_Win_P] = LAYOUT(
      C(KC_C),         C(KC_V),  LT(_2_Win_P, KC_V),     MT(MOD_LSFT, KC_C),     C(KC_S),
      LT(_ten, KC_J),  KC_L,     MT(MOD_LALT, KC_LEFT),  MT(MOD_LCTL, KC_RGHT),  LT(_SWITCH, KC_JYEN),
                       C(KC_Z),  KC_UP,                  KC_DOWN,                LT(_1_Win_P, KC_SPC)
    ),
    [_1_Win_P] = LAYOUT(
      XXXXXXX,      C(A(KC_M)),  KC_I,         KC_O,       XXXXXXX,
      S(C(KC_M)),   S(KC_M),     S(KC_LEFT),   S(KC_RGHT), XXXXXXX,
                    KC_M,        S(KC_I),      S(KC_O),    _______
    ),
    [_2_Win_P] = LAYOUT(
      S(C(KC_E)),   KC_F,        _______,      KC_BSPC,    XXXXXXX,
      XXXXXXX,      XXXXXXX,     C(S(KC_A)),   C(KC_A),    KC_MUTE,
                    XXXXXXX,  KC_Q,         KC_W,       C(KC_K)
    ),

    // Win AfterEffects
    [_0_Win_AE] = LAYOUT(
      C(KC_C),         C(KC_V),  LT(_2_Win_AE, KC_V),     MT(MOD_LSFT, KC_H),     C(KC_S),
      LT(_ten, KC_J),  KC_K,     MT(MOD_LALT, KC_PGUP),   MT(MOD_LCTL, KC_PGDN),  LT(_SWITCH, KC_SCLN),
                       C(KC_Z),  C(S(A(KC_LEFT))),        C(S(A(KC_RGHT))),       LT(_1_Win_AE, KC_SPC)
    ),
    [_1_Win_AE] = LAYOUT(
      KC_T,         KC_P,        KC_B,          KC_N,           KC_M,
      KC_R,         KC_S,        MC_5FL,        MC_5FR,         KC_E,
                    KC_U,        S(KC_HOME),    S(KC_END),      _______
    ),
    [_2_Win_AE] = LAYOUT(
      C(A(KC_S)),    C(KC_D),    _______,       MT(MOD_LSFT, KC_BSPC), XXXXXXX,
      C(A(KC_SLSH)), XXXXXXX,    KC_RBRC,       KC_BSLS,               KC_MUTE,
                     XXXXXXX,    A(KC_RBRC),    A(KC_BSLS),            C(S(KC_D))
    ),

   /////////////////////Mac
   // Mac Premiere
    [_0_Mac_P] = LAYOUT(
      G(KC_C),         G(KC_V),  LT(_2_Mac_P, KC_V),     MT(MOD_LSFT, KC_C),     G(KC_S),
      LT(_ten, KC_J),  KC_L,     MT(MOD_LALT, KC_LEFT),  MT(MOD_LCTL, KC_RGHT),  LT(_SWITCH, KC_JYEN),
                       G(KC_Z),  KC_UP,                  KC_DOWN,                LT(_1_Mac_P, KC_SPC)
    ),
    [_1_Mac_P] = LAYOUT(
      XXXXXXX,      G(A(KC_M)),  KC_I,         KC_O,       XXXXXXX,
      S(G(KC_M)),   S(KC_M),     S(KC_LEFT),   S(KC_RGHT), XXXXXXX,
                    KC_M,        S(KC_I),      S(KC_O),    _______
    ),
    [_2_Mac_P] = LAYOUT(
      S(G(KC_E)),   KC_F,        _______,      KC_BSPC,    XXXXXXX,
      XXXXXXX,      XXXXXXX,     G(S(KC_A)),   G(KC_A),    KC_MUTE,
                    XXXXXXX,     KC_Q,         KC_W,       G(KC_K)
    ),

    // Mac AfterEffects
    [_0_Mac_AE] = LAYOUT(
      G(KC_C),         G(KC_V),  LT(_2_Mac_AE, KC_V),     MT(MOD_LSFT, KC_H),     G(KC_S),
      LT(_ten, KC_J),  KC_K,     MT(MOD_LALT, KC_PGUP),   MT(MOD_LCTL, KC_PGDN)
,  LT(_SWITCH, KC_SCLN),
                       G(KC_Z),  G(S(A(KC_LEFT))),        G(S(A(KC_RGHT))),       LT(_1_Mac_AE, KC_SPC)
    ),
    [_1_Mac_AE] = LAYOUT(
      KC_T,         KC_P,        KC_B,          KC_N,           KC_M,
      KC_R,         KC_S,        MC_5FL,        MC_5FR,         KC_E,
                    KC_U,        S(KC_HOME),    S(KC_END),      _______
    ),
    [_2_Mac_AE] = LAYOUT(
      G(A(KC_S)),    G(KC_D),    _______,       MT(MOD_LSFT, KC_BSPC), XXXXXXX,
      G(A(KC_SLSH)), XXXXXXX,    KC_RBRC,       KC_BSLS,               KC_MUTE,
                     XXXXXXX,    A(KC_RBRC),    A(KC_BSLS),            G(S(KC_D))
    ),

    // テンキー
    [_ten] = LAYOUT(
      KC_0,       KC_1,        KC_2,         KC_3,         KC_MINUS,
      _______,    KC_4,        KC_5,         KC_6,         KC_DOT,
                  KC_7,        KC_8,         KC_9,         KC_ENTER
    ),

    /////// 切り替え
    [_SWITCH] = LAYOUT(
      XXXXXXX,    XXXXXXX,     MC_Win_P,     MC_Win_AE,     XXXXXXX,
      XXXXXXX,    XXXXXXX,     MC_Mac_P,     MC_Mac_AE,     _______,
                  XXXXXXX,     XXXXXXX,      XXXXXXX,       XXXXXXX
    ),
};

// エンコーダ― Mac/Win, Premiere/AfterEffectsでキーバインド切り替える
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* the upper encoder */
//////////
// 上のエンコーダ―(P/AEで、Undo/Redo共通)
      if (Win_or_Mac) {
         if (clockwise) {
         // clockwise: Redo
            SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_Z))));
         } else {
         // couterclockwise: Undo
            SEND_STRING(SS_LCTL(SS_TAP(X_Z)));
         }
      } else {
         if (clockwise) {
         // clockwise: Redo
            SEND_STRING(SS_LSFT(SS_LGUI(SS_TAP(X_Z))));
         } else {
         // couterclockwise: Undo
            SEND_STRING(SS_LGUI(SS_TAP(X_Z)));
         }
      }
  } else if (index == 1) { /* the lower encoder */
//////////
//下のエンコーダー
    if (layer_state_is(_2_Win_P) ==1 || layer_state_is(_2_Win_AE) ==1 || layer_state_is(_2_Mac_P) ==1 || layer_state_is(_2_Mac_AE) ==1) {
      // layer 2 on のときはVolつまみになる
      if (clockwise) {
            SEND_STRING(SS_TAP(X_VOLU));
            // clockwise
      } else {
            SEND_STRING(SS_TAP(X_VOLD));
            //counterclockwise
      }
    } else {
      // それ以外はタイムラインの拡大縮小
      if (P_or_AE) {
      ///// Premiere
        if (clockwise) {
            SEND_STRING("'");
            // clockwise: timeline scale +
            // 日本語の:キーをUSで打っているので。
        } else {
            SEND_STRING("-");
            //counterclockwise: timeline scale -
        }
      } else {
      ////// AfterEffects
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
}

// Macros ///////////////////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // AEで5F移動(デフォルトのショートカットが10Fしかないので、Premireと合わせる)
    case MC_5FL:
      if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_PGUP));
            SEND_STRING(SS_TAP(X_PGUP));
            SEND_STRING(SS_TAP(X_PGUP));
            SEND_STRING(SS_TAP(X_PGUP));
            SEND_STRING(SS_TAP(X_PGUP));
     }
      break;
    case MC_5FR:
      if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_PGDOWN));
            SEND_STRING(SS_TAP(X_PGDOWN));
            SEND_STRING(SS_TAP(X_PGDOWN));
            SEND_STRING(SS_TAP(X_PGDOWN));
            SEND_STRING(SS_TAP(X_PGDOWN));
     }
      break;

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