// Copyright 2022 Girish Palya (@girishji)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 3

/* Tap twice the LEFT shift key to enable caps on the current word being typed */
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

/* Mod tap does not register otherwise */
#define TAP_CODE_DELAY 5

/* https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md */
#define TAPPING_TERM_PER_KEY

/* https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md */
#define RETRO_TAPPING_PER_KEY
#define PERMISSIVE_HOLD

/* Time (in ms) before the one shot key is released */
#define ONESHOT_TIMEOUT 5000

/* Enable 1000hz scan rate */
#define USB_POLLING_INTERVAL_MS 1

/* turn off after debugging */
// #define DEBUG_MATRIX_SCAN_RATE

#ifdef LED_MATRIX_ENABLE
    #define LED_DRIVER_COUNT 1
    #define LED_MATRIX_LED_COUNT 72
    #define LED_DRIVER_ADDR_1 0b1110100
    #define LED_DISABLE_WHEN_USB_SUSPENDED
    /* limits maximum brightness of LEDs (max 256) */
    #define LED_MATRIX_MAXIMUM_BRIGHTNESS 130
    /* limits in milliseconds how frequently an animation will update the LEDs. 16
     * (16ms) is equivalent to limiting to 60fps (increases keyboard
     * responsiveness). At 16ms matrix scan frequency redues from 1000 to 350, at
     * 100ms it is 880 and at 1000ms it is 980 */
    // #define LED_MATRIX_LED_FLUSH_LIMIT 100
    #define LED_MATRIX_LED_FLUSH_LIMIT 16
// #define ENABLE_LED_MATRIX_BREATHING
// #define LED_MATRIX_DEFAULT_MODE LED_MATRIX_BREATHING
    /* i2c */
    #define I2C1_SDA_PIN GP16
    #define I2C1_SCL_PIN GP17
    #define I2C_DRIVER I2CD1
#endif

// #ifdef OLED_ENABLE
//     #define OLED_DISPLAY_128X64
//     #define SPLIT_OLED_ENABLE
//     #define OLED_DISPLAY_ADDRESS     0x3C //0x78
//     #define OLED_BRIGHTNESS 128
//     #define I2C_DRIVER        I2CD3
//     #define I2C1_SCL_PIN     A8  //B10 I2C2 ok // B6 B8 I2C1 has some
//     problems in some aliexpress f401 try to use weact f411 genuine( only
//     boards with bootloaders problem?) #define I2C1_SDA_PIN     B4   //B3 I2C2
//     ok // B7 B9 I2C1 has some problems in some aliexpress f401 try to use
//     weact f411 genuine( only boards with bootloaders problem?) #define
//     I2C1_SCL_PAL_MODE 4 #define I2C1_SDA_PAL_MODE 9 #define I2C1_CLOCK_SPEED
//     400000 #define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
// #endif

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in
 * your rules.mk, and define SOFT_SERIAL_PIN.
 */
// #define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

// #define LED_NUM_LOCK_PIN B0
// #define LED_CAPS_LOCK_PIN B9
// #define LED_SCROLL_LOCK_PIN B2
// #define LED_COMPOSE_PIN B3
// #define LED_KANA_PIN B4

// #define BACKLIGHT_PIN B7
// #define BACKLIGHT_LEVELS 3
// #define BACKLIGHT_BREATHING

// #define RGB_DI_PIN F0
// #define RGBLIGHT_LAYERS
// #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
// #ifdef RGB_DI_PIN
// #    define RGBLED_NUM 16
// #    define RGBLIGHT_HUE_STEP 8
// #    define RGBLIGHT_SAT_STEP 8
// #    define RGBLIGHT_VAL_STEP 8
// #    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
// #    define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched
// off when the host goes to sleep */
/*== all animations enable ==*/
// #    define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
// #    define RGBLIGHT_EFFECT_BREATHING
// #    define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #    define RGBLIGHT_EFFECT_SNAKE
// #    define RGBLIGHT_EFFECT_KNIGHT
// #    define RGBLIGHT_EFFECT_CHRISTMAS
// #    define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #    define RGBLIGHT_EFFECT_RGB_TEST
// #    define RGBLIGHT_EFFECT_ALTERNATING
/*== customize breathing effect ==*/
/*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
// #    define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
/*==== use exp() and sin() ====*/
// #    define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
// #    define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
// #endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is
 * not needed */
// #define DEBOUNCE 0

/* define if matrix has ghost (lacks anti-ghosting diodes) */
// #define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* If defined, GRAVE_ESC will always act as ESC when CTRL is held.
 * This is useful for the Windows task manager shortcut (ctrl+shift+esc).
 */
// #define GRAVE_ESC_CTRL_OVERRIDE

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in
 * the makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during
 * a power-up.
 *
 */
// #define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
