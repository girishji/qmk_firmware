/*
Copyright 2022 Girish Palya <girishji@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Scan matrix
 * https://github.com/qmk/qmk_firmware/blob/master/docs/custom_matrix.md
 */

#include "quantum.h"
#include "wait.h"
#include "print.h"

#define DEBOUNCE 0

#ifndef WAIT_AFTER_COL_SELECT
#    define WAIT_AFTER_COL_SELECT 100
#endif

#define COL_COUNT 9
#define ROW_COUNT 4
#define MATRIX_COUNT 2
#define MATRIX_ROW_PINS_A \
    { GP20, GP19, GP18, GP15 }
#define MATRIX_ROW_PINS_B \
    { GP14, GP13, GP12, GP11 }
#define MATRIX_COL_PINS_A \
    { GP29, GP28, GP27, GP26, GP25, GP24, GP23, GP22, GP21 }
#define MATRIX_COL_PINS_B \
    { GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8 }
static const pin_t row_pins_a[ROW_COUNT] = MATRIX_ROW_PINS_A;
static const pin_t row_pins_b[ROW_COUNT] = MATRIX_ROW_PINS_B;
static const pin_t col_pins_a[COL_COUNT] = MATRIX_COL_PINS_A;
static const pin_t col_pins_b[COL_COUNT] = MATRIX_COL_PINS_B;

matrix_row_t col_selector[MATRIX_COLS] = {0};

void matrix_init_custom(void) {
    for (uint8_t i = 0; i < MATRIX_COUNT; i++) {
        // initialize column pins to be Input
        for (uint8_t col = 0; col < COL_COUNT; col++) {
            pin_t pin = (i == 0) ? col_pins_a[col] : col_pins_b[col];
            if (pin != NO_PIN) {
                ATOMIC_BLOCK_FORCEON {
                    setPinInputHigh(pin);
                    setPinInput(pin);
                }
            }
        }
        // initialize row pins to be Output and set them low
        for (uint8_t row = 0; row < ROW_COUNT; row++) {
            pin_t pin = (i == 0) ? row_pins_a[row] : row_pins_b[row];
            if (pin != NO_PIN) {
                ATOMIC_BLOCK_FORCEON {
                    setPinOutput(pin);
                    writePinLow(pin);
                }
            }
        }
    }

    matrix_row_t shifter = 1;
    for (uint8_t col = 0; col < MATRIX_COLS; col++, shifter <<= 1) {
        col_selector[col] = shifter;
    }
}

static inline void set_col_of_row(uint16_t pin_val, matrix_row_t *row, matrix_row_t *shifter) {
    if (pin_val == 1) {
        *row |= *shifter;
    } else {
        *row &= ~(*shifter);
    }
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    for (uint8_t row = 0; row < ROW_COUNT; row++) {
        // Matrix A
        //
        pin_t pin = row_pins_a[row];
        writePinHigh(pin);
        wait_us(WAIT_AFTER_COL_SELECT);

        for (uint8_t col = 0; col < COL_COUNT; col++) {
            set_col_of_row(readPin(col_pins_a[col]), curr_matrix + row, col_selector + col);
        }
        writePinLow(pin);

        // Matrix B
        //
        pin = row_pins_b[row];
        writePinHigh(pin);
        wait_us(WAIT_AFTER_COL_SELECT);

        switch (row + ROW_COUNT) {
            case ROW_COUNT:
                for (uint8_t col = 0; col < COL_COUNT; col++) {
                    set_col_of_row(readPin(col_pins_a[col]), curr_matrix + ROW_COUNT, col_selector + col);
                }
                break;
            case ROW_COUNT + 1:
                for (uint8_t col = 0; col < 5; col++) {
                    set_col_of_row(readPin(col_pins_a[col]), curr_matrix + MATRIX_ROWS - 1, col_selector + col + COL_COUNT);
                }
                set_col_of_row(readPin(col_pins_a[5]), curr_matrix + MATRIX_ROWS - 2, col_selector + 12);
                set_col_of_row(readPin(col_pins_a[6]), curr_matrix + MATRIX_ROWS - 2, col_selector + 11);
                set_col_of_row(readPin(col_pins_a[7]), curr_matrix + MATRIX_ROWS - 2, col_selector + 10);
                set_col_of_row(readPin(col_pins_a[8]), curr_matrix + MATRIX_ROWS - 2, col_selector + 9);
                break;

            case ROW_COUNT + 2:
                for (uint8_t col = 0; col < 6; col++) {
                    set_col_of_row(readPin(col_pins_a[col]), curr_matrix + MATRIX_ROWS - 3, col_selector + col + COL_COUNT);
                }
                set_col_of_row(readPin(col_pins_a[6]), curr_matrix + MATRIX_ROWS - 2, col_selector + 13);
                set_col_of_row(readPin(col_pins_a[7]), curr_matrix + 1, col_selector + 13);
                set_col_of_row(readPin(col_pins_a[8]), curr_matrix + 1, col_selector + 12);
                break;
            case ROW_COUNT + 3:
                for (uint8_t col = 0; col < 6; col++) {
                    set_col_of_row(readPin(col_pins_a[col]), curr_matrix + 0, col_selector + col + COL_COUNT);
                }
                set_col_of_row(readPin(col_pins_a[6]), curr_matrix + 1, col_selector + 11);
                set_col_of_row(readPin(col_pins_a[7]), curr_matrix + 1, col_selector + 10);
                set_col_of_row(readPin(col_pins_a[8]), curr_matrix + 1, col_selector + 9);
                break;
        }
        writePinLow(pin);
    }

    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));
    }
    return (uint8_t)changed;
}
