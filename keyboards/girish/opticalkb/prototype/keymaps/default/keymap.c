// Copyright 2022 Girish Palya (@girishji)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_cmd_grv_active = false;
uint16_t cmd_grv_timer = 0;

bool is_cmd_tab_active = false;
uint16_t cmd_tab_timer = 0;

bool led_matrix_on = true;

// clang-format off
// Define the keycodes used by macros in this file
enum custom_keycodes {
    CMD_GRV = SAFE_RANGE,
    CMD_TAB,
    UP_DIR,
    LED_MATRIX_TOGGLE
};
// clang-format on

// Define names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_1, KC_2, KC_3,
        KC_Q, KC_W, KC_E,
        KC_A, KC_S, KC_D,
        KC_Z, KC_X, KC_C,
        KC_U, KC_I, KC_P
    ),
    [_FN]   = LAYOUT(
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    /* [_BASE] = LAYOUT( */
    /*     CMD_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, LGUI(KC_LEFT), LGUI(KC_RIGHT), */
    /*     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, */ 
    /*     OSM(MOD_LCTL), KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_QUOT, KC_UP, */
    /*     LALT(KC_C), OSM(MOD_RSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, OSM(MOD_LSFT), KC_DOWN, */ 
    /*     OSM(MOD_LALT), CMD_GRV, KC_BTN1, OSL(_FN), OSM(MOD_LGUI), KC_SPC, KC_GRV, KC_BSPC, KC_PGDN, KC_PGUP, RCTL(KC_T), OSM(MOD_RALT), KC_LEFT, KC_RIGHT */
    /* ), */
    /* [_FN]   = LAYOUT( */
    /*     _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, BL_DOWN, BL_UP, */
    /*     _______, DYN_REC_START1, _______, DYN_MACRO_PLAY1, DYN_MACRO_PLAY1, _______, _______, _______, LGUI(KC_LEFT), LGUI(KC_RIGHT), _______, _______, _______, _______, */ 
    /*     _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______, _______, _______, */ 
    /*     _______, _______, _______, _______, _______, _______, _______, KC_PGDN, _______, _______, _______, _______, _______, BL_TOGG, */ 
    /*     QK_BOOT, _______, KC_BTN3, _______, _______, _______, LED_MATRIX_TOGGLE, LALT(KC_BSPC), KC_END, KC_HOME, _______, KC_WH_D, KC_WH_U, _______ */ 
    /* ), */
    /* [_LAYER2]   = LAYOUT( */
    /*     _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END, */
    /*     _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_LEFT), LGUI(KC_RIGHT), _______, _______, _______, _______, */ 
    /*     _______, _______, _______, _______, _______, _______, _______, LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RIGHT), _______, _______, _______, _______, */ 
    /*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */ 
    /*     QK_BOOT, _______, _______, _______, _______, _______, _______, _______, KC_END, KC_HOME, _______, _______, _______, _______ */
    /* ) */
};
// clang-format on

/* void is31fl3731_all_led_on(uint8_t brightness_level); */
/* void is31fl3731_all_led_off(void); */

void keyboard_post_init_user(void) {
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each
  // key pressed
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %u, time: %u, interrupt: %u, count: %u\n",
          keycode, record->event.key.col, record->event.key.row,
          record->event.pressed, record->event.time, record->tap.interrupted,
          record->tap.count);
#endif

  switch (keycode) {
  case CMD_GRV:
    if (record->event.pressed) {
      if (!is_cmd_grv_active) {
        is_cmd_grv_active = true;
        register_code(KC_LGUI);
      }
      cmd_grv_timer = timer_read();
      register_code(KC_GRV);
    } else {
      unregister_code(KC_GRV);
    }
    return true;
  case CMD_TAB:
    if (record->event.pressed) {
      if (!is_cmd_tab_active) {
        is_cmd_tab_active = true;
        register_code(KC_LGUI);
      }
      cmd_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    return true;
  case UP_DIR:
    if (record->event.pressed) {
      SEND_STRING("../");
    }
    return false;
  case LED_MATRIX_TOGGLE:
    /* if (record->event.pressed) { */
    /*   if (led_matrix_on) { */
    /*     is31fl3731_all_led_off(); */
    /*   } else { */
    /*     is31fl3731_all_led_on(25); */
    /*   } */
    /*   led_matrix_on = !led_matrix_on; */
    /* } */
    return false;
  default:
    return true; // Process all other keycodes normally
  }
}

// Timer for cmd_grv
void matrix_scan_user(void) {
  if (is_cmd_grv_active) {
    if (timer_elapsed(cmd_grv_timer) > 990) {
      unregister_code(KC_LGUI);
      is_cmd_grv_active = false;
    }
  } else if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 990) {
      unregister_code(KC_LGUI);
      is_cmd_tab_active = false;
    }
  }
}

// Returns time interval for double tap
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LSFT:
  case OSM(MOD_LSFT):
    return TAPPING_TERM + 400;
  default:
    return TAPPING_TERM;
  }
}

/* https://github.com/qmk/qmk_firmware/blob/master/docs/tap_hold.md */
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LT(_FN, KC_ESC):
    return true;
  default:
    return false;
  }
}

#if 0
/* Brighten leds when capslock is on */
bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                led_matrix_set_value(i, 0xc0);
            }
        }
    }
    return true;
}

const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_1  }, { 0, C1_2  }, { 0, C1_3  }, { 0, C1_4  }, { 0, C1_5  }, { 0, C1_6  }, { 0, C1_7  }, { 0, C1_8  }, { 0, C1_9  }, { 0, C1_10 }, { 0, C1_11 }, { 0, C1_12 }, { 0, C1_13 }, { 0, C1_14 }, { 0, C1_15 },
    { 0, C2_1  }, { 0, C2_2  }, { 0, C2_3  }, { 0, C2_4  }, { 0, C2_5  }, { 0, C2_6  }, { 0, C2_7  }, { 0, C2_8  }, { 0, C2_9  }, { 0, C2_10 }, { 0, C2_11 }, { 0, C2_12 }, { 0, C2_13 }, { 0, C2_14 },
    { 0, C3_1  }, { 0, C3_2  }, { 0, C3_3  }, { 0, C3_4  }, { 0, C3_5  }, { 0, C3_6  }, { 0, C3_7  }, { 0, C3_8  }, { 0, C3_9  }, { 0, C3_10 }, { 0, C3_11 }, { 0, C3_12 }, { 0, C3_13 }, { 0, C3_14 }, { 0, C3_15 },
    { 0, C4_1  }, { 0, C4_2  }, { 0, C4_3  }, { 0, C4_4  }, { 0, C4_5  }, { 0, C4_6  }, { 0, C4_7  }, { 0, C4_8  }, { 0, C4_9  }, { 0, C4_10 }, { 0, C4_11 }, { 0, C4_12 }, { 0, C4_13 }, { 0, C4_14 }, 
    { 0, C7_9  }, { 0, C7_10  }, { 0, C7_11  }, { 0, C7_12  }, { 0, C6_12  }, { 0, C6_11  }, { 0, C6_10  }, { 0, C6_9  }, { 0, C5_9  }, { 0, C5_10 }, { 0, C5_11 }, { 0, C5_12 }, { 0, C5_13 }, { 0, C5_14 },
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14 },
  { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28     },
  { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 },
  { 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 },
  { 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 58 },
}, {
  // LED Index to Physical Position
  {   0,   0  }, {  16,   0  }, {  32,   0  }, {  48,   0  }, {  64,   0  }, {  80,   0  }, {  96,   0  }, { 112,   0  }, { 128,   0  }, { 144,   0  }, { 160,   0  }, { 176,   0  }, { 192,   0  }, { 208,   0  }, { 224,   0  }, 
  {   0,   12 }, {  16,   12 }, {  32,   12 }, {  48,   12 }, {  64,   12 }, {  80,   12 }, {  96,   12 }, { 112,   12 }, { 128,   12 }, { 144,   12 }, { 160,   12 }, { 176,   12 }, { 192,   12 }, { 208,   12 },
  {   0,   24 }, {  16,   24 }, {  32,   24 }, {  48,   24 }, {  64,   24 }, {  80,   24 }, {  96,   24 }, { 112,   24 }, { 128,   24 }, { 144,   24 }, { 160,   24 }, { 176,   24 }, { 192,   24 }, { 208,   24 }, { 224,   24 }, 
  {   0,   36 }, {  16,   36 }, {  32,   36 }, {  48,   36 }, {  64,   36 }, {  80,   36 }, {  96,   36 }, { 112,   36 }, { 128,   36 }, { 144,   36 }, { 160,   36 }, { 176,   36 }, { 192,   36 }, { 208,   36 }, 
  {   0,   48 }, {  16,   48 }, {  32,   48 }, {  48,   48 }, {  64,   48 }, {  80,   48 }, {  96,   48 }, { 112,   48 }, { 128,   48 }, { 144,   48 }, { 160,   48 }, { 176,   48 }, { 192,   48 }, { 208,   48 }, 
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
} };
#endif
