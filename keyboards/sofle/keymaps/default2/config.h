#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/



// 薙刀式
//#define NAGINATA_TATEGAKI
#define NAGINATA_YOKOGAKI
//#define NAGINATA_EDIT_WIN // JP106
#define NAGINATA_EDIT_MAC // JP106
#define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合
// #define COMBO_COUNT 2

#define remapez
// 薙刀式

/* Select hand configuration */

#define MASTER_LEFT
#define USE_SERIAL_PD2

#define USB_MAX_POWER_CONSUMPTION 100 


#define PERMISSIVE_HOLD
#define RETRO_TAPPING