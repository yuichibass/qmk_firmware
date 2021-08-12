#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/



//#define NAGINATA_TATEGAKI
#define NAGINATA_YOKOGAKI

//#define NAGINATA_EDIT_WIN // JP106
//#define UNICODE_SELECTED_MODES UC_WINC

#define NAGINATA_EDIT_MAC // US101
// Macはunicode入力を使わない
#define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合

// #define NAGINATA_EDIT_LINUX
// #define UNICODE_SELECTED_MODES UC_LNX

#define NAGINATA_KOUCHI_SHIFT // シフトを後置でも有効にする
/* Select hand configuration */

#define MASTER_LEFT
// #define USE_SERIAL_PD2

//#define USE_I2C

#define USB_MAX_POWER_CONSUMPTION 100 


#define PERMISSIVE_HOLD
#define RETRO_TAPPING