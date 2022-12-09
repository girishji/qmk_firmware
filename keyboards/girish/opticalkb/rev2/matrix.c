/*
 * Copyright (c) 2022 Girish Palya
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "print.h"
#include "quantum.h"
#include "wait.h"

#define DEBOUNCE 0

#ifndef WAIT_AFTER_COL_SELECT
#define WAIT_AFTER_COL_SELECT 30  // 18 works
#endif

#define COL_COUNT 9
#define ROW_COUNT 4
#define MATRIX_COUNT 2

static const pin_t row_pins_a[ROW_COUNT] = { GP20, GP19, GP18, GP15 };
static const pin_t row_pins_b[ROW_COUNT] = { GP14, GP13, GP12, GP11 };
static const pin_t col_pins_a[COL_COUNT] = { GP29, GP28, GP27, GP26, GP25, GP24, GP23, GP22, GP21 };
static const pin_t col_pins_b[COL_COUNT] = { GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8 };

matrix_row_t col_selector[MATRIX_COLS] = { 0 };

// void is31fl3731_init(void);
// void is31fl3731_all_led_on(uint8_t brightness_level);

void matrix_init_custom(void)
{
    for (uint8_t i = 0; i < MATRIX_COUNT; i++) {
        /* Initialize column pins to be Input. */
        for (uint8_t col = 0; col < COL_COUNT; col++) {
            pin_t pin = (i == 0) ? col_pins_a[col] : col_pins_b[col];
            if (pin != NO_PIN) {
                ATOMIC_BLOCK_FORCEON
                {
                    setPinInput(pin);
                }
            }
        }
        /* Initialize row pins to be Output and set them low. */
        for (uint8_t row = 0; row < ROW_COUNT; row++) {
            pin_t pin = (i == 0) ? row_pins_a[row] : row_pins_b[row];
            if (pin != NO_PIN) {
                ATOMIC_BLOCK_FORCEON
                {
                    setPinOutput(pin);
                    writePinLow(pin);
                }
            }
        }
    }

    // is31fl3731_init();
    // is31fl3731_all_led_on(0);
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[])
{
    matrix_row_t curr_matrix[MATRIX_ROWS] = { 0 };

    for (uint8_t row = 0; row < ROW_COUNT; row++) {
        /* Matrix A */
        writePinHigh(row_pins_a[row]);
        wait_us(WAIT_AFTER_COL_SELECT);
        uint32_t col_values = palReadPort(0) >> 21;
        writePinLow(row_pins_a[row]);

        if (col_values > 0) {
            for (uint8_t col = 0; col < COL_COUNT; col++) {
                curr_matrix[row] <<= 1;
                curr_matrix[row] |= (col_values & 1);
                col_values >>= 1;
            }
        }

        /* Matrix B */
        writePinHigh(row_pins_b[row]);
        wait_us(WAIT_AFTER_COL_SELECT);
        col_values = palReadPort(0);
        writePinLow(row_pins_b[row]);

        switch (row) {
        case 0:
            curr_matrix[4] |= (matrix_row_t)(col_values & 0x000001ff);
            break;
        case 1:
            if (col_values & 0x0000001f) {
                curr_matrix[4] |= (matrix_row_t)((col_values & 0x0000001f) << COL_COUNT);
            }
            curr_matrix[3] |= (matrix_row_t)((col_values & 0x00000020) ? 0x1000 : 0); // col 6/13
            curr_matrix[3] |= (matrix_row_t)((col_values & 0x00000040) ? 0x0800 : 0); // col 7/12
            curr_matrix[3] |= (matrix_row_t)((col_values & 0x00000080) ? 0x0400 : 0); // col 8/11
            curr_matrix[3] |= (matrix_row_t)((col_values & 0x00000100) ? 0x0200 : 0); // col 9/10
            break;
        case 2:
            if (col_values & 0x0000003f) {
                curr_matrix[2] |= (matrix_row_t)((col_values & 0x0000003f) << COL_COUNT);
            }
            curr_matrix[3] |= (matrix_row_t)((col_values & 0x00000040) ? 0x2000 : 0); // col 7/14
            curr_matrix[1] |= (matrix_row_t)((col_values & 0x00000080) ? 0x2000 : 0); // col 8/14
            curr_matrix[1] |= (matrix_row_t)((col_values & 0x00000100) ? 0x1000 : 0); // col 9/13
            break;
        case 3:
            if (col_values & 0x0000003f) {
                curr_matrix[0] |= (matrix_row_t)((col_values & 0x0000003f) << COL_COUNT);
            }
            curr_matrix[1] |= (matrix_row_t)((col_values & 0x00000040) ? 0x0800 : 0); // col 7/12
            curr_matrix[1] |= (matrix_row_t)((col_values & 0x00000080) ? 0x0400 : 0); // col 8/11
            curr_matrix[1] |= (matrix_row_t)((col_values & 0x00000100) ? 0x0200 : 0); // col 9/10
            break;
        }
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));
    }
    return (uint8_t)changed;
}
