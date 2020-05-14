/* Copyright 2020 yfuku
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

#include "paw3204.h"
#include "pointing_device.h"

bool isScrollMode;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    RGBRST,
    MBTN1,
    MBTN2,
    SCRL
};

#define L_SPC LT(_LOWER, KC_SPC)
#define R_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
	KC_ESC,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,		KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	KC_MINS,
	KC_TAB,	KC_A,	SGUI_T(KC_S),	LALT_T(KC_D),	LGUI_T(KC_F),	LCTL_T(KC_G),	KC_BSPC,	RCTL_T(KC_H),	RGUI_T(KC_J),	RALT_T(KC_K),	SGUI_T(KC_L),	KC_SCLN,	KC_ESC,
	KC_NO,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,		KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLSH,	KC_NO,
				KC_NO,	LSFT_T(KC_LANG2),	LT(1, KC_SPC),		LT(2, KC_ENT),	LSFT_T(KC_LANG1),	KC_NO,			
					KC_A,	KC_B,		KC_C,	KC_D,	KC_E			
    ),
    [_LOWER] = LAYOUT(
	KC_TRNS,	KC_NO,	KC_NO, SCRL,	MBTN2,	MBTN1,		KC_NO,	KC_EQL,	KC_PLUS,	KC_ASTR,	KC_PERC,	KC_TRNS,
	KC_TRNS,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	LCMD(KC_BSPC),	KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_TRNS,
	KC_TRNS,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,		KC_NO,	KC_NO,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
				RESET,	KC_TRNS,	KC_NO,		KC_DEL,	KC_TRNS,	KC_TRNS,			
					KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS			
    ),
    [_RAISE] = LAYOUT(
	KC_TRNS,	KC_BSLS,	KC_EXLM,	KC_AMPR,	KC_PIPE,	KC_NO,		KC_NO,	KC_EQL,	KC_PLUS,	KC_ASTR,	KC_PERC,	KC_TRNS,
	KC_TRNS,	KC_HASH,	KC_GRV,	KC_DQUO,	KC_QUOT,	KC_TILD,	LCMD(KC_BSPC),	KC_LEFT,	KC_DOWN,	KC_UP,	KC_RGHT,	KC_DLR,	KC_TRNS,
	KC_TRNS,	KC_NO,	KC_NO,	KC_LCBR,	KC_LBRC,	KC_LPRN,		KC_RPRN,	KC_RBRC,	KC_RCBR,	KC_AT,	KC_CIRC,	KC_TRNS,
				KC_TRNS,	KC_TRNS,	KC_BSPC,		KC_NO,	KC_TRNS,	RESET,			
					KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,	KC_TRNS			
   ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  report_mouse_t currentReport = {};
  switch (keycode) {
    case MBTN1:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN1;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN1;
      }
      pointing_device_set_report(currentReport);
      pointing_device_send();
      return false;
    case MBTN2:
      currentReport = pointing_device_get_report();
      if (record->event.pressed) {
        currentReport.buttons |= MOUSE_BTN2;
      }
      else {
        currentReport.buttons &= ~MOUSE_BTN2;
      }
      pointing_device_set_report(currentReport);
      pointing_device_send();
      return false;
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
      }
      else {
        isScrollMode = false;
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
    init_paw3204();
    setPinInputHigh(D2);
    setPinInputHigh(D3);
}

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse = true;
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;
    static int  btn1;
    static int  btn2;

    report_mouse_t mouse_rep = pointing_device_get_report();

    btn1 = readPin(D2);
    if (btn1 == 1) {
        mouse_rep.buttons |= MOUSE_BTN1;
    } else {
        mouse_rep.buttons &= ~MOUSE_BTN1;
    }
    btn2 = readPin(D3);
    if (btn2 == 1) {
        mouse_rep.buttons |= MOUSE_BTN2;
    } else {
        mouse_rep.buttons &= ~MOUSE_BTN2;
    }
    pointing_device_set_report(mouse_rep);

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
   }

    if (paw_ready) {

        uint8_t stat;
        int8_t x, y;

        read_paw3204(&stat, &x, &y);

        if (isScrollMode)
        {
            mouse_rep.h = x/6;
            mouse_rep.v = -y/6;
        }
        else
        {
            mouse_rep.x = y;
            mouse_rep.y = -x;
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }

    }
}



/*
    report_mouse_t currentReport = pointing_device_get_report();
    if (isScrollMode)
    {
      currentReport.h = dx/SCROLL_SPEED_DIVIDER;
      currentReport.v = dy/SCROLL_SPEED_DIVIDER;
    }
    else
    {
      currentReport.x = dx * POINTER_SPEED_MULTIPLIER;
      currentReport.y = dy * POINTER_SPEED_MULTIPLIER;
    }

    pointing_device_set_report(currentReport);
    pointing_device_send();

    */

