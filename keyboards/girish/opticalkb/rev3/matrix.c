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
#define WAIT_AFTER_COL_SELECT 12 // 17 works
#endif

#define DEBOUNCE_VAL (WAIT_AFTER_COL_SELECT * 8)

#define COL_COUNT 15
#define ROW_COUNT 5

#define SENSOR_ADC GPIO28

static const pin_t row_pins[ROW_COUNT] = { GP22, GP6, GP5, GP4, GP3 };
static const pin_t col_pins[COL_COUNT] = { GP21, GP20, GP19, GP18, GP17, GP16, GP15, GP14, GP13, GP12, GP11, GP10, GP9, GP8, GP7 };

void is31fl3731_init(void);
void is31fl3731_all_led_on(uint8_t brightness_level);

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
    /* Initialize row pins to be Output and set them low. */
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

    // is31fl3731_init();
    // is31fl3731_all_led_on(80); // % brightness
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[])
{
    matrix_row_t scan_matrix[MATRIX_ROWS] = { 0 };

    for (uint8_t row = 0; row < ROW_COUNT; row++) {
        writePinHigh(row_pins[row]);
        wait_us(WAIT_AFTER_COL_SELECT);
        uint32_t cols = (palReadPort(0) >> 7) & 0x00007fff;
        writePinLow(row_pins[row]);

        if (cols > 0) {
            // reverse the bits read from GPIOs since column numbering is right-to-left in matrix
            // reverse last 15 bits in ever smaller chunks for clean O(1)
            cols = ((cols & 0x0000ff00) >> 8) | ((cols & 0x000000ff) << 8);
            cols = ((cols & 0x0000f0f0) >> 4) | ((cols & 0x00000f0f) << 4);
            cols = ((cols & 0x0000cccc) >> 2) | ((cols & 0x00003333) << 2);
            cols = ((cols & 0x0000aaaa) >> 1) | ((cols & 0x00005555) << 1);
            cols >>= 1; // remove the 16th bit which is now in 0th position
            scan_matrix[row] = (matrix_row_t) cols;
        }
    }

    static bool debouncing = false;
    static uint16_t debounce[MATRIX_ROWS][MATRIX_COLS] = { 0 };

    if (debouncing) {
        /* Decrement debounce count */
        bool changed = false;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (debounce[row][col] > 0) {
                    debounce[row][col] -= 1;
                    changed = true;
                }
            }
        }
        if (!changed) {
            debouncing = false;
        }
    }

    bool changed = memcmp(current_matrix, scan_matrix, sizeof(scan_matrix)) != 0;
    if (changed) {
        if (!debouncing) {
            /* Start debounce */
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                matrix_row_t newkeys = current_matrix[row] ^ scan_matrix[row];
                for (uint8_t col = 0; newkeys > 0 && col < MATRIX_COLS; col++) {
                    if ((newkeys & 1) > 0) {
                        debounce[row][col] = DEBOUNCE_VAL;
                        debouncing = true;
                    }
                    newkeys >>= 1;
                }
            }
            /* Report the key event (state change) */
            memcpy(current_matrix, scan_matrix, sizeof(scan_matrix));
        } else {
            /* Mask key state changes that are within debounce period */
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    if (debounce[row][col] > 0) {
                        scan_matrix[row] &= ~(1 << col); // zero out the bit
                        scan_matrix[row] |= current_matrix[row] & (1 << col);
                    }
                }
            }
            /* Report key event if necessary */
            changed = memcmp(current_matrix, scan_matrix, sizeof(scan_matrix)) != 0;
            if (changed) {
                memcpy(current_matrix, scan_matrix, sizeof(scan_matrix));
            }
        }
    }
    return (uint8_t)changed;
}
