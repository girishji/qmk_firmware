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
    _FN,
    _L2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        CMD_TAB, LGUI(KC_LEFT), LGUI(KC_RIGHT), KC_2, KC_3, KC_COPY, KC_PASTE, KC_MINS, KC_EQL, KC_8, KC_9, KC_0, KC_UP, KC_BSLS,
	CMD_GRV, KC_GRV, KC_1, KC_W, KC_E, KC_4, KC_5, KC_6, KC_7, KC_I, KC_O, KC_LEFT, KC_DOWN, KC_RIGHT, 
	KC_TAB, KC_TAB, KC_Q, KC_S, KC_D, KC_R, KC_T, KC_Y, KC_U, KC_K, KC_L, KC_P, KC_BSPC, KC_PGUP, 
	KC_CAPS, KC_ESC, KC_A, KC_X, KC_C, KC_F, KC_G, KC_H, KC_J, KC_COMM, KC_DOT, KC_SCLN, KC_ENT, KC_PGDN,
	KC_CAPS, OSM(MOD_LSFT), KC_Z, MO(_FN), KC_NO, KC_V, KC_B, KC_N, KC_M, KC_LBRC, KC_RBRC, KC_SLSH, OSM(MOD_RSFT), KC_QUOT,
        MO(_FN), KC_BTN1, OSM(MOD_LALT), OSM(MOD_LCTL), KC_SPC, OSM(MOD_LGUI), OSM(MOD_RGUI), KC_SPC, OSM(MOD_RCTL), OSM(MOD_RALT), KC_BTN2, MO(_FN)
        ),
    [_FN] = LAYOUT(
        RGB_TOG, RGB_VAD, RGB_VAI, KC_F2, KC_F3, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
        RGB_MODE_FORWARD, RGB_MODE_REVERSE, KC_F1, _______, _______, KC_F4, KC_F5, _______, _______, KC_5, KC_6, _______, _______, _______,
        RGB_HUI, RGB_HUD, _______, _______, _______, _______, _______, _______, KC_4, KC_2, KC_3, _______, _______, KC_HOME, 
        RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, _______, KC_1, KC_0, KC_EQL, _______, _______, KC_END, 
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, _______, _______, _______, _______, _______,
        _______, _______, MO(_L2), _______, _______, _______, _______, _______, _______, MO(_L2), _______, _______
    ),
    [_L2] = LAYOUT(
        _______, KC_F14, KC_F15, _______, _______, _______, _______, _______, _______, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        _______, _______, _______, _______, _______, _______, _______, KC_F6, KC_F7, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, RESET, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ) 
};


/* lighting layers */
// Light LEDs red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED},
    {8, 8, HSV_RED}
);
// Light some LEDs cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_CYAN},
    {8, 8, HSV_CYAN}
);
// Light LEDs in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_PURPLE},       // Light 16 LEDs, starting with LED 0
    {8, 8, HSV_PURPLE}       // Light 16 LEDs, starting with LED 0
);
// Light LEDs in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_GREEN},
    {8, 8, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

/*
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
    return state;
}
*/

layer_state_t layer_state_set_user(layer_state_t state) {
    // comment out since you cannot see effect of RGB_XX command keys
    //rgblight_set_layer_state(2, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(3, layer_state_cmp(state, _L2));
    return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;

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
      break;
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
      break;
  }

  return true;
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
