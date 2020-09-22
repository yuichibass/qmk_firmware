#pragma once

#include "quantum.h"
#define kNN KC_NO

#define LAYOUT( \
    k05, k04, k03, k02, k01, k00,           k40, k41, k42, k43, k44, k45, \
    k15, k14, k13, k12, k11, k10,   kA8,    k50, k51, k52, k53, k54, k55, \
    k25, k24, k23, k22, k21, k20, k86, k87, k60, k61, k62, k63, k64, k65, \
                   k32, k31, k30,    k97,   k70, k71, k72 \
) { \
    { k00, k01, k02, k03, k04, k05, kNN, kNN, kNN }, \
    { k10, k11, k12, k13, k14, k15, kNN, kNN, kNN }, \
    { k20, k21, k22, k23, k24, k25, kNN, kNN, kNN }, \
    { k30, k31, k32, kNN, kNN, kNN, kNN, kNN, kNN }, \
    { k40, k41, k42, k43, k44, k45, kNN, kNN, kNN }, \
    { k50, k51, k52, k53, k54, k55, kNN, kNN, kNN }, \
    { k60, k61, k62, k63, k64, k65, kNN, kNN, kNN }, \
    { k70, k71, k72, kNN, kNN, kNN, kNN, kNN, kNN }, \
    { kNN, kNN, kNN, kNN, kNN, kNN, k86, k87, kNN }, \
    { kNN, kNN, kNN, kNN, kNN, kNN, kNN, k97, kNN }, \
    { kNN, kNN, kNN, kNN, kNN, kNN, kNN, kNN, kA8 }, \
}
