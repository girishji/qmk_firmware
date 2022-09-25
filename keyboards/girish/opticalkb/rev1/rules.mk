# https://docs.qmk.fm/#/squeezing_avr?id=rulesmk-settings
#

# MCU name
MCU = STM32F401
BOARD = BLACKPILL_STM32_F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP = yes

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DYNAMIC_MACRO_ENABLE = yes  # Dynamic macros

# LED_MATRIX_ENABLE = yes
# LED_MATRIX_DRIVER = IS31FL3731
# SRC += blackpill_f401.c

# turn this off after debugging
# CONSOLE_ENABLE = yes        # Console for debug

CUSTOM_MATRIX = lite
SRC += matrix.c
