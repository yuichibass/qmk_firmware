#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define TAPPING_TERM 0
#define PERMISSIVE_HOLD
#define RETRO_TAPPING

// 薙刀式
#define NAGINATA_JDOUJI // 順序つきの同時押しに対応する
#define DQWERTY
// #define DEUCALYN
// #define DWORKMAN
// #define NAGINATA_EDIT_WIN // JP106
#define NAGINATA_EDIT_MAC // JP106
#define COMBO_COUNT 2
#define COMBO_TERM 300
// 薙刀式