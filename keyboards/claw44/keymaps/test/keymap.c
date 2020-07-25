#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_ KC_TRNS
#define KC_RST RESET
#define KC_L_SPC LT(_LOWER, KC_SPC) // lower
#define KC_R_TAB LT(_RAISE, KC_TAB) // raise
#define KC_S_ENT LSFT_T(KC_ENT) // Left Shift
#define KC_A_DOT ALT_T(KC_DOT) // alt
#define KC_R_DEL LT(_RAISE, KC_DEL) // lower
#define KC_AD TG(_ADJUST)
//#define KC_R_DOT LT(_RAISE, KC_DOT) // raise
//#define KC_R_ENT LT(_RAISE, KC_ENT) // raise
//#define KC_L_ALT LT(_LOWER, KC_LALT) // lower
//#define KC_S_0 RSFT_T(KC_0) // Right Shift
//#define KC_C_BS LCTL_T(KC_BSPC) // ctrl
//#define KC_G_JA LGUI_T(KC_LANG1) // cmd or win
//#define KC_G_EN LGUI_T(KC_LANG2) // cmd or win‘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
  //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
     KC_GRV , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , KC_MINS,
  //|--------+--------+---------+--------+---------+--------|   |---w-----+---------+--------+---------+--------+--------|
     KC_LSFT, KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_LBRC, KC_RBRC,
  //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
     KC_LCTL, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, KC_SCLN,
  //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                        KC_LGUI, KC_LALT, KC_L_SPC, KC_R_TAB,    KC_BSPC, KC_S_ENT, KC_RSFT, KC_R_DEL
  //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
  ),

  //   \ ^ ! & |  @ = + * % -
  // ( # $ " ' ~  ← ↓ ↑ → ` )
  //         { [  ] }

  [_LOWER] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_PLUS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL , KC_LPRN, KC_RPRN,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_AD  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_JYEN,     XXXXXXX, XXXXXXX, _______, _______, KC_BSLS, KC_QUOT,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , XXXXXXX,     KC_HOME, XXXXXXX, KC_UP  , XXXXXXX, KC_PGUP, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , XXXXXXX,     KC_END , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_AD  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

 [_ADJUST] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     _______, XXXXXXX, KC_UP  , XXXXXXX, KC_HOME, XXXXXXX,     KC_ASTR, KC_7   , KC_8   , KC_9   , KC_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,     KC_SLSH, KC_4   , KC_5   , KC_6   , KC_PLUS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     KC_AD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL ,     XXXXXXX, KC_1   , KC_2   , KC_3   , KC_EQL , XXXXXXX,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                       _______, _______, _______, _______,     _______, _______, KC_0   , KC_DOT  
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
      break;
  }
  return true;
}
