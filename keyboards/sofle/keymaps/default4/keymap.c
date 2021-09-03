#include QMK_KEYBOARD_H

#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

#include "keymap_jp.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
// 薙刀式
    _NAGINATA,  // 薙刀式入力レイヤー
// 薙刀式
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_QWERTY = NG_SAFE_RANGE,
    KC_COLEMAK,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTRT,
    KC_LEND,
    KC_DLINE,
    EISU,
    KANA2,
    LCTOGL, // Macのライブ変換対応オンオフ
};

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
#define CTLSPC  CTL_T(KC_SPC)
#define CTLENT  CTL_T(KC_ENT)

//  RGUI(RALT(KC_5))  take screenshot
//  LGUI(KC_C)        copy
//  LGUI(KC_V)        paste
//  LGUI(KC_X)        cut
//  KC_F6             start and stop playing
//  KC_F11            increase the audio volume
//  KC_F12            decrease the audio volume
//  KC_F16            Start original apple script and show dictionary tool window in Mac OS
//  KC_INT1           backslash

// built                qmk compile -kb sofle -km default2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ESC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  :   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Lalt |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ESC, \
  KC_Q,   KC_TAB,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LALT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    G(KC_R),KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_F17,KC_LOWER,KC_LGUI, KC_SPC, KC_BSPC,      KC_ENT,  KC_SPC, KC_LSFT, KC_RAISE, KC_Q \
),
/*
 * COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   D  |   F  |   K  |                    |   Y  |   U  |   I  |   L  |   ;  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   T  |   R  |   G  |-------.    ,-------|   H  |   N  |   E  |   O  |   P  |  :   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   J  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_COLEMAK] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ESC, \
  KC_ESC,   KC_Q,   KC_W,    KC_D,    KC_F,    KC_K,                      KC_Y,    KC_U,    KC_I,    KC_L, KC_SCLN,  KC_MINS, \
  KC_TAB,   KC_A,   KC_S,    KC_T,    KC_R,    KC_G,                      KC_H,    KC_N,    KC_E,    KC_O,    KC_P,  KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     XXXXXXX,KC_J,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
),

/*
 * NAGINATA
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ESC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  :   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | Lalt |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_NAGINATA] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ESC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT, \
  KC_LALT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    G(KC_R),KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT, \
                 KC_F18,KC_LOWER,KC_LGUI, KC_SPC, KC_BSPC,      KC_ENT,  KC_SPC, KC_LSFT, KC_RAISE, KC_F17 \
),


/* 
 *  LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   ^  |   _  |   *  |   `  |  (   |                    |   )  |  F16 |  UP  | "    |  $   | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   .  |   ¥  |   /  |   %  |   {  |-------.    ,-------|   }  | LEFT | DOWN | RGHT | SCRN |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  !   |   ?  |  ~   |   #  |   [  |-------|    |-------|   ]  | COPY | PAST | CUT  | SAVE | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_LOWER] = LAYOUT( \
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,                                  KC_F6,  KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  KC_ESC,    JA_HAT,    JA_ENUN,  KC_KP_ASTERISK,  JP_GRV,    JP_LPRN,                 JP_RPRN, KC_F16,  KC_UP,    JP_DQUO,    JP_DLR,  KC_F12, \
  KC_LSFT, JA_ENUN,    JA_ENVL,   KC_KP_SLASH,  JP_PERC, JP_LCBR,                      JP_RCBR, KC_LEFT, KC_DOWN, KC_RGHT, RGUI(RALT(KC_5)), JP_PIPE, \
  KC_TRNS,  JP_EXLM,   JP_QUES,    KC_TILD,     JP_HASH, JP_LBRC, _______,    _______, JP_RBRC, LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), LGUI(KC_S), _______, \
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS\
),

/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  @   | ,    | 7    | 8    |  9   |  +   |                    |   ¥  | F11  | F12  |  F20  |   #  |   ^   |
 * |-------------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | .    | 4    | 5    |   6  |  -   | -------.    ,------|   _  |PGUP  | HOME |  CUT | *     |  |  
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |　　 　| 0    | 1    | 2    | 3    |  =   |-------|    |-------|   §  |PGDN  | END  | COPY  PASTE | Shift |
 * `-----------------------------------------/       /     \      \----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_QUOTE, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______, \
  JP_AT,  KC_PCMM,  KC_7,   KC_8,  KC_9, KC_PPLS,                           KC_JYEN, KC_F11,   KC_F12, KC_F20,KC_HASH, KC_AMPR, \
  KC_LSFT, KC_PDOT,  KC_4,  KC_5,  KC_6, KC_PMNS,                           KC_RO,  KC_PGUP, KC_HOME, LGUI(KC_X),  KC_ASTR , KC_PIPE, \
  KC_TRNS, KC_0,    KC_1, KC_2, KC_3,  KC_PEQL,  KC_0,             _______, KC_NUBS, KC_PGDOWN, KC_END, LGUI(KC_C),   LGUI(KC_V), _______, \
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RESET|      |QWERTY|Minimak|      |      |                   | F19  | F20  |  F21 | F22  | F23  | F24 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MACWIN|      |      |      |-------.    ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | F18 | LOWER | CMD  | SPC |  /Bspc  /       \Enter \  | SPC | Lshift | RAISE | F17 |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX , XXXXXXX,  XXXXXXX ,  XXXXXXX , XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET  , XXXXXXX,KC_QWERTY,KC_COLEMAK,CG_TOGG,XXXXXXX,                     LGUI(KC_F19), KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, \
  XXXXXXX , XXXXXXX,CG_TOGG, XXXXXXX,    XXXXXXX,  XXXXXXX,                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, \
  XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, \
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
  ),
};

// #ifdef OLED_DRIVER_ENABLE

// static void render_logo(void) {
//     static const char PROGMEM qmk_logo[] = {
//         0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//         0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//         0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
//     };

//     oled_write_P(qmk_logo, false);
// }

// static void print_status_narrow(void) {
//     // Print current mode
//     oled_write_P(PSTR("\n\n"), false);
//     oled_write_ln_P(PSTR("MODE"), false);
//     oled_write_ln_P(PSTR(""), false);
//     if (keymap_config.swap_lctl_lgui) {
//         oled_write_ln_P(PSTR("MAC"), false);
//     } else {
//         oled_write_ln_P(PSTR("WIN"), false);
//     }

//     switch (get_highest_layer(default_layer_state)) {
//         case _QWERTY:
//             oled_write_ln_P(PSTR("Qwrt"), false);
//             break;
//         case _COLEMAK:
//             oled_write_ln_P(PSTR("Clmk"), false);
//             break;
//         default:
//             oled_write_P(PSTR("Undef"), false);
//     }
//     oled_write_P(PSTR("\n\n"), false);
//     // Print current layer
//     oled_write_ln_P(PSTR("LAYER"), false);
//     switch (get_highest_layer(layer_state)) {
//         case _COLEMAK:
//         case _QWERTY:
//             oled_write_P(PSTR("Base\n"), false);
//             break;
//         case _RAISE:
//             oled_write_P(PSTR("Raise"), false);
//             break;
//         case _LOWER:
//             oled_write_P(PSTR("Lower"), false);
//             break;
//         case _ADJUST:
//             oled_write_P(PSTR("Adj\n"), false);
//             break;
//         default:
//             oled_write_ln_P(PSTR("Undef"), false);
//     }
//     oled_write_P(PSTR("\n\n"), false);
//     led_t led_usb_state = host_keyboard_led_state();
//     oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
// }

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     if (is_keyboard_master()) {
//         return OLED_ROTATION_270;
//     }
//     return rotation;
// }

// void oled_task_user(void) {
//     if (is_keyboard_master()) {
//         print_status_narrow();
//     } else {
//         render_logo();
//     }
// }

// #endif

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);

  #ifdef NAGINATA_EDIT_MAC
  set_unicode_input_mode(UC_OSX);
  #endif
  // #ifdef NAGINATA_EDIT_WIN
  // set_unicode_input_mode(UC_WINC);
  // #endif
  // 薙刀式
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case EISU:
            if (record->event.pressed) {
        // 薙刀式
             naginata_off();
        // 薙刀式
        }
              return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
            naginata_on();
        // 薙刀式
      }
      return false;
      break;
    case LCTOGL:
      if (record->event.pressed) {
        mac_live_conversion_toggle();
      }
      return false;
      break;


    // 薙刀式
    if (!process_naginata(keycode, record))
      return false;
    // 薙刀式


        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTRT:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_DLINE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_BSPC);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_BSPC);
            }
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
    // update_led();
  }
  if (a == false) return false;
  // 薙刀式

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
        } else {
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
        }
    }
    return true;
}

#endif
