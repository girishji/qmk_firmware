# https://docs.qmk.fm/#/squeezing_avr?id=rulesmk-settings
#

# MCU name
MCU = RP2040
BOARD = GENERIC_RP_RP2040


# Bootloader selection
BOOTLOADER = rp2040
SERIAL_DRIVER = vendor
# SERIAL_DRIVER = usart

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DYNAMIC_MACRO_ENABLE = yes  # Dynamic macros
CAPS_WORD_ENABLE = yes      # Enable current word being typed to be all caps

OPT_DEFS += -DHAL_USE_I2C=TRUE
LED_MATRIX_ENABLE = no
SRC += is31fl3731.c
# LED_MATRIX_ENABLE = yes
# LED_MATRIX_DRIVER = IS31FL3731

# turn this off after debugging
# CONSOLE_ENABLE = yes        # Console for debug

CUSTOM_MATRIX = lite
SRC += matrix.c
