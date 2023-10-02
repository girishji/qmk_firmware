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
	K000, K001, K002, \
	K100, K101, K102, \
	K200, K201, K202, \
	K300, K301, K302, \
	K400, K401, K402  \
) { \
	{ K000,  K001,  K002 }, \
	{ K100,  K101,  K102 }, \
	{ K200,  K201,  K202 }, \
	{ K300,  K301,  K302 }, \
	{ K400,  K401,  K402 }  \
}

