// Copyright 2022 Girish Palya (@girishji)
// SPDX-License-Identifier: GPL-2.0-or-later

// see https://github.com/qmk/qmk_firmware/blob/e1203a222bb12ab9733916164a000ef3ac48da93/keyboards/alu84/keymaps/default/keymap.c
// 

#include QMK_KEYBOARD_H

bool is_cmd_grv_active = false; 
uint16_t cmd_grv_timer = 0;    

bool is_cmd_tab_active = false; 
uint16_t cmd_tab_timer = 0;    

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  CMD_GRV,
  CMD_TAB
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base */
  [_BASE] = LAYOUT(
    CMD_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_PGUP, KC_PGDN,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, LGUI(KC_LEFT), 
    OSM(MOD_LCTL), KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, OSM(MOD_RALT),
    OSM(MOD_LSFT), KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_UP, OSM(MOD_RSFT),
    OSM(MOD_LALT), KC_BTN1, KC_CAPS, OSM(MOD_LGUI), KC_BSPC, OSL(_FN), KC_SPC, LGUI(KC_RIGHT), OSM(MOD_RALT), OSM(MOD_RCTL), KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSLS 
  ),
  [_FN] = LAYOUT(
    _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HOME, KC_END,
    _______, DYN_REC_STOP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LCMD(KC_LEFT), LCMD(KC_RIGHT),
    _______, _______, DYN_REC_START1, DYN_MACRO_PLAY1, _______, _______, _______, LCMD(KC_LEFT), KC_PGDN, KC_PGUP, LCMD(KC_RIGHT), _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, DYN_REC_START2, DYN_MACRO_PLAY2, _______, _______, _______, _______, KC_WH_U, _______,
    RESET, KC_BTN3, _______, _______, BL_TOGG, _______, _______, _______, _______, _______, BL_DEC, KC_WH_D, BL_INC, RESET
  )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  ////debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      return false;  // no more processing necessary

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
    default:
      return true; // Process all other keycodes normally
  }

}

void matrix_scan_user(void) { // The very important timer.  
  if (is_cmd_grv_active) {    
    if (timer_elapsed(cmd_grv_timer) > 700) {      
      unregister_code(KC_LGUI);      
      is_cmd_grv_active = false;    
    }  
  } else if (is_cmd_tab_active) {    
    if (timer_elapsed(cmd_tab_timer) > 700) {      
      unregister_code(KC_LGUI);      
      is_cmd_tab_active = false;    
    }  
  }
}

/* Enable some leds when capslock is on */
void led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                led_matrix_set_value(i, 0xc0);
            }
        }
    }
}

#if 1
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_9  }, { 0, C1_10  }, { 0, C1_11  }, { 0, C1_12  }, { 0, C1_13  }, { 0, C1_14  }, { 0, C1_15  }, { 0, C1_16  },
    { 0, C2_9  }, { 0, C2_10  }, { 0, C2_11  }, { 0, C2_12  }, { 0, C2_13  }, { 0, C2_14  }, { 0, C2_15  }, { 0, C2_16  },
    { 0, C3_9  }, { 0, C3_10  }, { 0, C3_11  }, { 0, C3_12  }, { 0, C3_13  }, { 0, C3_14  }, { 0, C3_15  }, { 0, C3_16  },
    { 0, C4_9  }, { 0, C4_10  }, { 0, C4_11  }, { 0, C4_12  }, { 0, C4_13  }, { 0, C4_14  }, { 0, C4_15  }, { 0, C4_16  },
    { 0, C5_9  }, { 0, C5_10  }, { 0, C5_11  }, { 0, C5_12  }, { 0, C5_13  }, { 0, C5_14  }, { 0, C5_15  }, { 0, C5_16  },
    { 0, C6_9  }, { 0, C6_10  }, { 0, C6_11  }, { 0, C6_12  }, { 0, C6_13  }, { 0, C6_14  }, { 0, C6_15  },
    { 0, C7_9  }, { 0, C7_10  }, { 0, C7_11  }, { 0, C7_12  }, { 0, C7_13  }, { 0, C7_14  }, 
    { 0, C8_9  }, { 0, C8_10  }, { 0, C8_11  }, { 0, C8_12  }, { 0, C8_13  }, { 0, C8_14  }, { 0, C8_15  },
    { 0, C9_9  }, { 0, C9_10  }, { 0, C9_11  }, { 0, C9_12  }, { 0, C9_13  }, { 0, C9_14  }
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  0,  5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 19 },
  {  1,  NO_LED, 11, 16, 21, 26, 31, 36, 41, 46, 51, 56, 61, 44, 24 },
  {  2,  7, 12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 6, 34 },
  {  3,  8, 13, 18, 23, 28, 33, 38, 43, 48, 53, 58, 63, NO_LED, 39 },
  {  NO_LED,  9, 14, NO_LED, NO_LED, 29, NO_LED, NO_LED, 49, 54, 59, 64, 4 },
}, {
  // LED Index to Physical Position
  {   0,   0 }, {  16,   0 }, {  32,   0 }, {  48,   0 }, {  64,   0 }, {  80,   0 }, {  96,   0 }, { 112,   0 }, { 128,   0 }, { 144,   0 }, { 160,   0 }, { 176,   0 }, { 192,   0 }, { 208,   0 }, { 224,   0 }, 
  {   0,  12 }, {  32,  12 }, {  48,  12 }, {  64,  12 }, {  80,  12 }, {  96,  12 }, { 112,  12 }, { 128,  12 }, { 144,  12 }, { 160,  12 }, { 176,  12 }, { 192,  12 }, { 208,  12 }, { 224,  12 }, 
  {   0,  24 }, {  16,  24 }, {  32,  24 }, {  48,  24 }, {  64,  24 }, {  80,  24 }, {  96,  24 }, { 112,  24 }, { 128,  24 }, { 144,  24 }, { 160,  24 }, { 176,  24 }, { 192,  24 }, { 208,  24 }, { 224,  24 }, 
  {   0,  36 }, {  16,  36 }, {  32,  36 }, {  48,  36 }, {  64,  36 }, {  80,  36 }, {  96,  36 }, { 112,  36 }, { 128,  36 }, { 144,  36 }, { 160,  36 }, { 176,  36 }, { 192,  36 }, { 224,  36 }, 
  {  16,  48 }, {  32,  48 }, {  48,  48 }, {  96,  48 }, { 160,  48 }, { 176,  48 }, { 192,  48 }, { 208,  48 }, 
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
} };

#endif
