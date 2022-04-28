# aria

![giri](https://i.imgur.com/7HjXotx.jpg)
![giri](https://i.imgur.com/o7rhdtJ.jpg)
![giri](https://i.imgur.com/gi0ZL6s.jpg)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Girish Palya](https://github.com/girishji)
* Hardware Supported: Black pill STM32F401

Make example for this keyboard (after setting up your build environment):

    make handwired/giri/aria:default

Flashing example for this keyboard:

    make handwired/giri/aria:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button BOOT and then button NRST, release NRST first and then BOOT 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Verify that it entered DFU (bootloader) mode through QMK Toolbox before
flashing.

## Wiring instructions

- On Blackpill boards, **avoid** using the following pins, since they will cause either USB enumeration or the DFU bootloader to not work correctly:
  - **USB-related pins:** `PA10`, `PA11`, `PA12`
  - **BOOT1 pin:** `PB2`
