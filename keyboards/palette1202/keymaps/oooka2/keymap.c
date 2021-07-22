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
// PAE ver 3.00 by OOOKA Toshihiko
///////////////////////////////////
// Adobe PremiereとAfter Effectsをどちらも似た操作感で使う為の左手マクロパッド配列
// Win/Mac, Premiere/After Effectsを都度切り替えて使います
// ver 3の新しい考え方は、小指を不使用にしたこと。中段真ん中の2キーを中指人差し指ホームポジションとして、
// 親指のメインを角ではなく、ひとつ左のキーにしたこと。このことで使用感がガラリと変わった。

#include QMK_KEYBOARD_H
#ifdef OLED_DRIVER_ENABLE
  #include <string.h>
  #include "lib/oled_helper.h"
#endif

// Windows/Mac デフォでは電源オンで、Win/Premiere
// これを変えたければ以下のフラグと、このあとのenum layerIDでの構造変更をすること
// Win or Mac
static bool Win_or_Mac = true;
//Premiere or AfterEffects
static bool P_or_AE = true;

// LAYER
//Premiereに3レイヤー、AEに3レイヤー、それぞれWinMacで計12レイヤー。あとテンキーとスペシャル（切り替え用）レイヤー
enum layerID {
  // Win
  _0_Win_P = 0,  // default layer
  _1_Win_P,
  _2_Win_P,
  // 3レイヤーごとにペアになっているので、デフォにしたいものを３レイヤーごとここにもってくるとデフォを変えられるよ
  // 最後の切り替えマクロ321行以降でベースレイヤーをどれにしたかで処理を変えること
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
  // 切り替えレイヤーとテンキーレイヤー
  _SPECIAL,
  _ten,
};

// keymap内にしこむマクロ
enum custom_keycodes {
  // Win/Mac Premiere/AfrerEffects切り替えマクロ
  MC_Win_P = SAFE_RANGE,
  MC_Mac_P,
  MC_Win_AE,
  MC_Mac_AE,
  // テンキーオン
  MC_tenON,
  // 5F進むマクロ
  MC_5FL,
  MC_5FR,
};

// Tap Dance
enum {
  // シングルでc(カミソリツール)、ダブルタップでv（選択ツール）
  TD_CV,
  // シングルでエンター、ダブルでエンター＋テンキーオフ
  TD_ENT,
};
// Tap Dance Def
void ten_enter_finished(qk_tap_dance_state_t *state, void *user_data) {
    register_code(KC_ENTER);
}
void ten_enter_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_ENTER);
  if (state->count == 1) {
  } else {
    layer_off(_ten);
  }
}
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CV] = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_V),
  [TD_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ten_enter_finished, ten_enter_reset),
};


// KEYMAP overview//////////////////////////////////////////////////////////////
/////Premiere///////////////////
//  Default: 基本的な移動と再生。エンコーダーはタイムラインの拡大と縮小、アンドゥリスト
//    In点へ        |  5F ←          |  5F →        | Out点へ      ||   Undo      (( Save  ))  Redo
//    前の編集点     |  1F ← /Ctrl    |  1F → /Shift |次の編集点 /Alt||   TL Zoom In(( TL全体 )) TL Zoom Out
//                 |  Undo          |  巻き戻し       | 再生、停止    ||   早送り 
//
//  Layer 1: 基本的な編集機能。InOutベース、カミソリベースの編集機能
//  //はシングルタップ、ダブルタップで機能が変わるもの
//   In点設定       |前の編集点までカット|次の編集点までカット|  Out点設定    ||          ((このレイヤーでInOut))
//   全レイヤーに編集点 |   編集点追加   |     BS        |   マッチフレーム   ||    Vol -    ((  Mute  ))   Vol +  
//                  |   Copy       |  カミソリ//選択   |**ここを押しながら**||    Paste
//  Layer 2: 補助的なものたち
//   マーカー消去      |  前のマーカー     |   次のマーカー    |    マーク      ||             ((       ))  
//   前方全選択      |  UnGroup      |  Group        |  後方全選択   ||             ((       ))
//                  |    前後再生    |**ここを押しながら**|ここからOutまで再生||  InOut再生     
//
/////After Effects///////////////////
//  Dfault: Premiereと同様、基本的な移動と再生。同じ機能で使えるようにした。タブとパネルを開いてコントロールしやすく。
//    ワークIn点へ    |  5F ←         | 5F →          | ワークOut点へ   ||   Undo      (( Save  ))  Redo
//    前の編集点     | 1F ← /Ctrl   | 1F → /Shift    |次の編集点 /Alt||   TL Zoom In(( TL全体 )) TL Zoom Out
//                 |  Undo        | 全キーフレームタブ    |   再生、停止  ||   コントロールパネル
//
//  Layer 1: 基本的なレイヤーの編集機能。
//    ワークIn点設定   |Inからここまで消去|ここからOutまで消去 | ワークOut点設定 ||         ((このレイヤーでInOut))
//    Inをここへ移動   | レイヤー分割    |   BS          | Outをここへ移動 ||    Vol -    ((  Mute  ))   Vol +
//                  | Copy        |   Dupe        |**ここを押しながら**||    Paste
//  Layer 2: タブを開いたり閉じたり、スナップショットしたり。
//   A アンカータブ     | 前のキーF      | 次のキーF      |  M マスクタブ    ||            ((       ))  
//    R 回転タブ      | P 位置タブ    | T 透明度タブ   | S スケールタブ    ||            ((       ))
//                  | スナップショット  |**ここを押しながら**|スナップショット表示||  E エフェクトタブ
//
/////SPECIAL/////////////////// Ten ONで恒久的にテンキーになる。（数値は連続で入力することが多いので）
//     Mac P   |  Mac AE  |   Win P     |  Win AE       ||   ((        ))  
//             |          |   ten ON    |               ||   ((        ))
//             |          |             |               ||*************
/////Ten Key/////////////////// Enterダブルクリックで、エンター+テンキー終了してDefaultレイヤーになる
//       BS    |     7    |      8      |        9      ||   ((   -    ))
//       0     |     4    |      5      |        6      ||   ((   .    ))
//             |     1    |      2      |        3      ||    Enter//Ent+終了

// KEYMAP 本体//////////////////////////////////////////////////////////////
// 一段目 1,2,3,4, 上のエンコのクリック,
// 二段目 1,2,3,4, 下のエンコのクリック,
// 親指     1,2,3, 4
// エンコーダーの回転はキーマップ以外で定義（234行以降）
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 注：LT(),MT()の中のキーは、Basic Keycodesでないといけない制約がある。なのでレイヤーキーの単キーは、単純なキーという縛りがあるよ。

    ///////////////////Windows
    // Win Premiere
    [_0_Win_P] = LAYOUT(
      S(KC_I),      S(KC_LEFT),             S(KC_RGHT),             S(KC_O),               C(KC_S),
      KC_UP,        MT(MOD_LCTL, KC_LEFT),  MT(MOD_LSFT, KC_RGHT),  KC_DOWN,               MT(MOD_LALT, KC_JYEN),
                    C(KC_Z),                LT(_2_Win_P, KC_J),     LT(_1_Win_P, KC_SPC),  LT(_SPECIAL, KC_L)
    ),
    [_1_Win_P] = LAYOUT(
      KC_I,         KC_Q,                   KC_W,                   KC_O,                KC_SLSH,
      S(C(KC_K)),   C(KC_K),                KC_BSPC,                KC_F,                KC_MUTE,
                    C(KC_C) ,               TD(TD_CV),              _______,             C(KC_V)
    ),
    [_2_Win_P] = LAYOUT(
      C(A(KC_M)),   S(C(KC_M)),             S(KC_M),                KC_M,                _______,
      S(KC_A),      S(C(KC_G)),             C(KC_G),                KC_A,                _______,
                    S(KC_K),                _______,                C(KC_SPC),           C(S(KC_SPC))
    ),
    // Win AfterEffects
    [_0_Win_AE] = LAYOUT(
      S(KC_HOME),       MC_5FL,                 MC_5FR,                 S(KC_END),             C(KC_S),
      C(S(A(KC_LEFT))), MT(MOD_LCTL, KC_PGUP),  MT(MOD_LSFT, KC_PGDN),  C(S(A(KC_RGHT))) ,     MT(MOD_LALT, KC_SCLN),
                        C(KC_Z),                LT(_2_Win_AE, KC_U) ,   LT(_1_Win_AE, KC_SPC), LT(_SPECIAL, KC_F3)
    ),
    [_1_Win_AE] = LAYOUT(
      KC_B,             A(KC_RBRC),             A(KC_BSLS),             KC_N,             C(A(KC_B)),
      KC_RBRC,          C(S(KC_D)),             KC_BSPC,                KC_BSLS,          KC_MUTE,
                        C(KC_C),                C(KC_D),                _______,          C(KC_V)
    ),
    [_2_Win_AE] = LAYOUT(
      KC_A,             KC_J,                   KC_K,                   KC_M,             _______,
      KC_R,             KC_P,                   KC_T,                   KC_S,             _______,
                        S(KC_F5),               _______,                KC_F5,            KC_E
    ),

   /////////////////////Mac
   // Mac Premiere
    [_0_Mac_P] = LAYOUT(
      S(KC_I),      S(KC_LEFT),             S(KC_RGHT),             S(KC_O),               G(KC_S),
      KC_UP,        MT(MOD_LGUI, KC_LEFT),  MT(MOD_LSFT, KC_RGHT),  LSFT(KC_O),               MT(MOD_LALT, KC_JYEN),
                    KC_KP_4,                KC_KP_5,                KC_KP_6,               KC_KP_PLUS
    ),
    [_1_Mac_P] = LAYOUT(
      KC_I,         KC_Q,                   KC_W,                   KC_O,                KC_SLSH,
      S(G(KC_K)),   G(KC_K),                KC_BSPC,                KC_F,                KC_MUTE,
                    G(KC_C) ,               TD(TD_CV),              _______,             G(KC_V)
    ),
    [_2_Mac_P] = LAYOUT(
      G(A(KC_M)),   S(G(KC_M)),             S(KC_M),                KC_M,                _______,
      S(KC_A),      S(G(KC_G)),             G(KC_G),                KC_A,                _______,
                    S(KC_K),                _______,                G(KC_SPC),           A(KC_K)
    ),
    // InOut再生だけWinとMacでショートカットが違う(Op+K)

    // Mac AfterEffects
    [_0_Mac_AE] = LAYOUT(
      S(KC_HOME),       MC_5FL,                 MC_5FR,                 S(KC_END),             C(KC_S),
      G(S(A(KC_LEFT))), MT(MOD_LCTL, KC_PGUP),  MT(MOD_LSFT, KC_PGDN),  G(S(A(KC_RGHT))) ,     MT(MOD_LALT, KC_SCLN),
                        G(KC_Z),                LT(_2_Mac_AE, KC_U) ,   LT(_1_Mac_AE, KC_SPC), LT(_SPECIAL, KC_F3)
    ),
    [_1_Mac_AE] = LAYOUT(
      KC_B,             A(KC_RBRC),             A(KC_BSLS),             KC_N,             G(A(KC_B)),
      KC_RBRC,          G(S(KC_D)),             KC_BSPC,                KC_BSLS,          KC_MUTE,
                        G(KC_C),                G(KC_D),                _______,          G(KC_V)
    ),
    [_2_Mac_AE] = LAYOUT(
      KC_A,             KC_J,                   KC_K,                   KC_M,             _______,
      KC_R,             KC_P,                   KC_T,                   KC_S,             _______,
                        S(KC_F5),               _______,                KC_F5,            KC_E
    ),

    /////// Win/Mac Premiere/After Effects切り替え、テンキーに切り替え
    [_SPECIAL] = LAYOUT(
      MC_Mac_P,   MC_Mac_AE,  MC_Win_P,     MC_Win_AE,   XXXXXXX,
     XXXXXXX,     XXXXXXX,    MC_tenON,     XXXXXXX,     XXXXXXX,
                  XXXXXXX,    XXXXXXX,      XXXXXXX,     _______
    ),
    // テンキー 数値入力しやすいように、一回オンにしたらオフにするまでテンキー。オフはエンターダブルクリック（エンター＋もとに戻る）
    [_ten] = LAYOUT(
      KC_BSPC,    KC_7,        KC_8,        KC_9,         KC_MINUS,
      KC_0,       KC_4,        KC_5,        KC_6,         KC_DOT,
                  KC_1,        KC_2,        KC_3,         TD(TD_ENT)
    ),
};

// エンコーダ― Mac/Win, Premiere/AfterEffectsでキーバインド切り替える
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
///////
// 上のエンコーダ―(P/AEで、Undo/Redo共通)
      if (Win_or_Mac) {
         // Win
         if (clockwise) {
            // clockwise: Redo
            SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_Z))));
         } else {
            // couterclockwise: Undo
            SEND_STRING(SS_LCTL(SS_TAP(X_Z)));
         }
      } else {
         // Mac
         if (clockwise) {
            // clockwise: Redo
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
         } else {
            // couterclockwise: Undo
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
         }
      }
  } else if (index == 1) {
//////////
//下のエンコーダー
      if (layer_state_is(_1_Win_P) ==1 || layer_state_is(_1_Win_AE) ==1 || layer_state_is(_1_Mac_P) ==1 || layer_state_is(_1_Mac_AE) ==1) {
        // layer 1 on のときはVolつまみになる（Win/Mac共通）
        if (clockwise) {
              SEND_STRING(SS_TAP(X_VOLU));
              // clockwise
        } else {
              SEND_STRING(SS_TAP(X_VOLD));
              //counterclockwise
        }
      } else {
        // タイムラインの拡大縮小(Win/Mac共通)
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
    // テンキーのオン
    case MC_tenON:
      if (record->event.pressed) {        
      } else {
      // キーリリースのときにレイヤーチェンジにしないと5がでちゃうっぽい
        layer_on(_ten);
      }
      break;
  }
  return true;
};