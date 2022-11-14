// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include_next <mcuconf.h>

#define RP2040_MCUCONF

#undef RP_PWM_USE_TIM5
#define RP_PWM_USE_TIM5 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE
