# Kailh Choc Ergo Keyboard

Keyboards using Choc switches are not common. These switches are low-profile
and can be used with 15gf light springs. PCB for this backlit keyboard can be
found [here](https://github.com/girishji/choc-keyboard).

![3d printed case](https://i.imgur.com/risvk8Q.jpg?1)
![3d printed case](https://i.imgur.com/H77lyNH.jpg?1)
![front side](https://i.imgur.com/7ngL65q.jpg)
![back side](https://i.imgur.com/xvfgL1L.jpg)

* Keyboard Maintainer: [Girish Palya](https://github.com/girishji)
* Hardware Supported: Black pill STM32F401

Make example for this keyboard (after setting up your build environment):

    make chockb/rev1:default

Flashing example for this keyboard:

    make chockb/rev1:default:flash

See the [build environment
setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make
instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more
information. Brand new to QMK? Start with our [Complete Newbs
Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button BOOT and then button NRST, release NRST first and then BOOT 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Verify that it entered DFU (bootloader) mode through QMK Toolbox before
flashing.

## Wiring instructions

Blackpill can only be soldered one way. Please see the pictures.

