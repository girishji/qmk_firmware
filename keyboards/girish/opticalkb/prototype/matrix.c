/*
 * Copyright (c) 2022 Girish Palya
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

// #include "print.h"
#include "quantum.h"
#include "wait.h"

#define DEBOUNCE 0

#ifndef WAIT_AFTER_COL_SELECT
/* #define WAIT_AFTER_COL_SELECT 25 // 17 works */
#define WAIT_AFTER_COL_SELECT 20
#endif

/* Debounce interval, count of scan frequency, max 65535.
 *   Debounce value is approximately (OPT_DEBOUNCE * WAIT_AFTER_COL_SELECT * 8) usec.
 */
/* #define OPT_DEBOUNCE 30 // 10 works */

// #define ROW_COUNT 5
// #define COL_COUNT 3
#define ROW_COUNT 29
#define COL_COUNT 1

/* #define COL_COUNT 9 */
/* #define ROW_COUNT 4 */
/* #define MATRIX_COUNT 2 */

// static const pin_t row_pins[ROW_COUNT] = { GP0, GP1, GP2, GP3, GP4 };
static const pin_t row_pins[ROW_COUNT] = { 
    GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9,
    GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19,
    GP20, GP21, GP22, GP23, GP24, GP25, GP26, GP27, GP28
};

// static const pin_t col_pins[COL_COUNT] = { GP5, GP6, GP7 };
static const pin_t col_pins[COL_COUNT] = { GP29 };

/* void is31fl3731_init(void); */
/* void is31fl3731_all_led_on(uint8_t brightness_level); */

void matrix_init_custom(void)
{
    /* Initialize column pins to be Input. */
    for (uint8_t col = 0; col < COL_COUNT; col++) {
        pin_t pin = col_pins[col];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON
            {
                setPinInput(pin);
            }
        }
    }

    /* initialize row pins to be output and set them low. */
    for (uint8_t row = 0; row < ROW_COUNT; row++) {
        pin_t pin = row_pins[row];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON
            {
                setPinOutput(pin);
                writePinLow(pin);
            }
        }
    }

    /* for (uint8_t i = 0; i < MATRIX_COUNT; i++) { */
    /*     /1* Initialize column pins to be Input. *1/ */
    /*     for (uint8_t col = 0; col < COL_COUNT; col++) { */
    /*         pin_t pin = (i == 0) ? col_pins_a[col] : col_pins_b[col]; */
    /*         if (pin != NO_PIN) { */
    /*             ATOMIC_BLOCK_FORCEON */
    /*             { */
    /*                 setPinInput(pin); */
    /*             } */
    /*         } */
    /*     } */
    /*     /1* initialize row pins to be output and set them low. *1/ */
    /*     for (uint8_t row = 0; row < row_count; row++) { */
    /*         pin_t pin = (i == 0) ? row_pins_a[row] : row_pins_b[row]; */
    /*         if (pin != no_pin) { */
    /*             atomic_block_forceon */
    /*             { */
    /*                 setpinoutput(pin); */
    /*                 writepinlow(pin); */
    /*             } */
    /*         } */
    /*     } */
    /* } */

    /* is31fl3731_init(); */
    /* is31fl3731_all_led_on(25); */
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[])
{
    matrix_row_t scan_matrix[MATRIX_ROWS] = { 0 };

    // uprintf("-------\n");
    for (uint8_t row = 0; row < ROW_COUNT; row++) {
        if (row == 0) {
            writePinHigh(row_pins[row]);
        }
            uprintf("In scan matrix \n");
        // wait_us(WAIT_AFTER_COL_SELECT);
        wait_us(50);
        // uint32_t col_values = palReadPort(0);
        // writePinLow(row_pins[row]);
        wait_ms(500);
        // wait_us(WAIT_AFTER_COL_SELECT);
        // scan_matrix[row] |= (matrix_row_t)((col_values & 0x000000e0) >> 5);
        // uprintf("%x\n", scan_matrix[row]);
    }

    /* for (uint8_t row = 0; row < ROW_COUNT; row++) { */
    /*     /1* Matrix A *1/ */
    /*     writePinHigh(row_pins_a[row]); */
    /*     wait_us(WAIT_AFTER_COL_SELECT); */
    /*     uint32_t col_values = palReadPort(0) >> 21; */
    /*     writePinLow(row_pins_a[row]); */

    /*     if (col_values > 0) { */
    /*         for (uint8_t col = 0; col < COL_COUNT; col++) { */
    /*             scan_matrix[row] <<= 1; */
    /*             scan_matrix[row] |= (col_values & 1); */
    /*             col_values >>= 1; */
    /*         } */
    /*     } */

    /*     /1* Matrix B *1/ */
    /*     writePinHigh(row_pins_b[row]); */
    /*     wait_us(WAIT_AFTER_COL_SELECT); */
    /*     col_values = palReadPort(0); */
    /*     writePinLow(row_pins_b[row]); */

    /*     scan_matrix[row + 4] |= (matrix_row_t)(col_values & 0x000001ff); */
    /* } */

    /* static bool debouncing = false; */
    /* static uint16_t debounce[MATRIX_ROWS][MATRIX_COLS] = { 0 }; */

    /* if (debouncing) { */
    /*     /1* Decrement debounce count *1/ */
    /*     bool changed = false; */
    /*     for (uint8_t row = 0; row < MATRIX_ROWS; row++) { */
    /*         for (uint8_t col = 0; col < MATRIX_COLS; col++) { */
    /*             if (debounce[row][col] > 0) { */
    /*                 debounce[row][col] -= 1; */
    /*                 changed = true; */
    /*             } */
    /*         } */
    /*     } */
    /*     if (!changed) { */
    /*         debouncing = false; */
    /*     } */
    /* } */

    bool changed = memcmp(current_matrix, scan_matrix, sizeof(scan_matrix)) != 0;
    //XXX
    changed = false;
    // static int count = 0;
    if (changed) {
        memcpy(current_matrix, scan_matrix, sizeof(scan_matrix));

        // for (uint8_t row = 0; row < ROW_COUNT; row++) {
        //     uprintf("%x\n", scan_matrix[row]);
        // }
    }
    // XXX
    // changed = false;

    /* if (changed) { */
    /*     if (!debouncing) { */
    /*         /1* Start debounce *1/ */
    /*         for (uint8_t row = 0; row < MATRIX_ROWS; row++) { */
    /*             matrix_row_t cur_row = current_matrix[row], scan_row = scan_matrix[row]; */
    /*             for (uint8_t col = 0; col < MATRIX_COLS; col++) { */
    /*                 if ((cur_row & 1) != (scan_row & 1)) { */
    /*                     debounce[row][col] = OPT_DEBOUNCE; */
    /*                     debouncing = true; */
    /*                 } */
    /*                 cur_row >>= 1; */
    /*                 scan_row >>= 1; */
    /*             } */
    /*         } */
    /*         /1* Report the key event (state change) *1/ */
    /*         memcpy(current_matrix, scan_matrix, sizeof(scan_matrix)); */
    /*     } else { */
    /*         /1* Mask key state changes that are within debounce period *1/ */
    /*         for (uint8_t row = 0; row < MATRIX_ROWS; row++) { */
    /*             for (uint8_t col = 0; col < MATRIX_COLS; col++) { */
    /*                 if (debounce[row][col] > 0) { */
    /*                     scan_matrix[row] &= ~(1 << col); // zero out the bit */
    /*                     scan_matrix[row] |= current_matrix[row] & (1 << col); */
    /*                 } */
    /*             } */
    /*         } */
    /*         /1* Report key event if necessary *1/ */
    /*         changed = memcmp(current_matrix, scan_matrix, sizeof(scan_matrix)) != 0; */
    /*         if (changed) { */
    /*             memcpy(current_matrix, scan_matrix, sizeof(scan_matrix)); */
    /*         } */
    /*     } */
    /* } */

    return (uint8_t)changed;
}
