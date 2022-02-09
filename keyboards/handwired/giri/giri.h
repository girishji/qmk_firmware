// Copyright 2022 Girish Palya (@girishji)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k05, k06, \
      k15,  k16,    \
      k25,  k16,    \
      k35,  k16,    \
      k45,  k16    \
) { \
    { k05, k06 }, \
    { k15, k16 }, \
    { k25, k26 }, \
    { k35, k36 }, \
    { k45, k46 }  \
}


//    { k10, KC_NO, k12 }  \
