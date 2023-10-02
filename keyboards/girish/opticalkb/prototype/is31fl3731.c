/*
 * Copyright (c) 2022 Girish Palya
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <math.h>
#include <ch.h>
#include <hal.h>
#include "print.h"

#define RP_I2C0_SDA_PIN GP16
#define RP_I2C0_SCL_PIN GP17
/* In ChibiOS I2CD1 corresponds to I2C0 driver of rp2040 */
#define I2C_DRIVER I2CD1
#define IS31FL3731_I2C_ADDRESS_DEFAULT 0x74
#define I2C_TIMEOUT_MS 100

static const I2CConfig i2cconfig = {.baudrate = 400000};

void is31fl3731_init(void) {
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    palSetLineMode(RP_I2C0_SDA_PIN,
                   PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);
    palSetLineMode(RP_I2C0_SCL_PIN,
                   PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);
    i2cStart(&I2C_DRIVER, &i2cconfig);
  }
}

static void i2c_reg_write_uint8(uint8_t reg, uint8_t value) {
  uint8_t buffer[2] = {reg, value};
  msg_t status =
      i2cMasterTransmitTimeout(&I2C_DRIVER, IS31FL3731_I2C_ADDRESS_DEFAULT,
                               buffer, 2, NULL, 0, TIME_MS2I(I2C_TIMEOUT_MS));
  /* If timeout, driver must be stopped and restarted (ChibiOS HAL doc).
   */
#ifdef CONSOLE_ENABLE
  if (status != MSG_OK) {
    uprintf("i2c transmit error: %lu\n", status);
  }
#endif
  if (status == MSG_TIMEOUT) {
    i2cStop(&I2C_DRIVER);
    i2cStart(&I2C_DRIVER, &i2cconfig);
  }
}

void is31fl3731_all_led_off(void) {
  i2c_reg_write_uint8(0xFD, 0x0B); // write function register
  i2c_reg_write_uint8(0x0A, 0x00); // enter software shutdown mode
  i2c_reg_write_uint8(0xFD, 0x00); // write first frame

  /* Turn off all LEDs */
  for (uint8_t i = 0; i < 0x12; i++) {
    i2c_reg_write_uint8(i, 0x00);
  }

  i2c_reg_write_uint8(0xFD, 0x0B); // write function register
  i2c_reg_write_uint8(0x00, 0x00); // picture mode
  i2c_reg_write_uint8(0x01, 0x00); // select first frame
  i2c_reg_write_uint8(0x0A, 0x01); // normal operation
}

/* brightness_level is 0-100% */
void is31fl3731_all_led_on(uint8_t brightness_level) {
  i2c_reg_write_uint8(0xFD, 0x0B); // write function register
  i2c_reg_write_uint8(0x0A, 0x00); // enter software shutdown mode
  i2c_reg_write_uint8(0xFD, 0x00); // write first frame

  /* Turn on LEDs */
  i2c_reg_write_uint8(0x00, 0xff); // row-1, matrix A
  i2c_reg_write_uint8(0x01, 0x7f); // row-1, matrix B
  i2c_reg_write_uint8(0x02, 0xff); // row-2, matrix A
  i2c_reg_write_uint8(0x03, 0x3f); // row-2, matrix B
  i2c_reg_write_uint8(0x04, 0xff);
  i2c_reg_write_uint8(0x05, 0x7f);
  i2c_reg_write_uint8(0x06, 0xff);
  i2c_reg_write_uint8(0x07, 0x3f);
  i2c_reg_write_uint8(0x08, 0x00);
  i2c_reg_write_uint8(0x09, 0x3f);
  i2c_reg_write_uint8(0x0a, 0x00);
  i2c_reg_write_uint8(0x0b, 0x0f);
  i2c_reg_write_uint8(0x0c, 0x00);
  i2c_reg_write_uint8(0x0d, 0x0f);
  i2c_reg_write_uint8(0x0e, 0x00);
  i2c_reg_write_uint8(0x0f, 0x00);
  i2c_reg_write_uint8(0x10, 0x00);
  i2c_reg_write_uint8(0x11, 0x00);

  /* Turn down intensity by 50%  */
  // for (uint8_t i = 0x24; i < 0xb3; i++) {
  //     i2c_reg_write_uint8(i, 0x7f);
  // }
  /* Turn down intensity to 25%  */
  // for (uint8_t i = 0x24; i < 0xb3; i++) {
  //   i2c_reg_write_uint8(i, 0x3f);
  // }

  float brightness = brightness_level / 100.0 * 255;
  for (uint8_t i = 0x24; i < 0xb3; i++) {
    i2c_reg_write_uint8(i, floor(brightness));
  }

  i2c_reg_write_uint8(0xFD, 0x0B); // write function register
  i2c_reg_write_uint8(0x00, 0x00); // picture mode
  i2c_reg_write_uint8(0x01, 0x00); // select first frame
  i2c_reg_write_uint8(0x0A, 0x01); // normal operation
}
