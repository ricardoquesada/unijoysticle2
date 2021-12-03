# Amiga / Atari ST support

**OUTDATED INFO: Should include info about Unijoysticle 2+ that supports 2nd & 3rd
buttons on Amiga/AtariST on both ports using the same firmware**

The Unijoysticle 2 can be used in any "[Atari DB9 joystick][db9]"-compatible computer.
That includes the 8-bit Atari family, the Commodore C64/C128, as well as the
Amiga and Atari ST (among others).

The Unijoysticle 2 was designed to fit in the Commodore 64 / 128 computers. If you
want to use in any other computer will one (or two) DB9 extension [cables][cable].

The difference between the C64/C128/Atari-8bit family vs. the Amiga/Atari ST
is that the latter supports up to 2 or 3 joystick buttons, while the former only
supports 1 joystick button.

If you want to use the 3-buttons with the Unijoysticle you have to flash the
`amiga` firmware (despite its name it also suitable for the Atari ST).

If you only play Amiga/Atari ST games that require just one button, you can use the
`c64` firmware, and you can skip this documentation.
See the benefits/limitations below.

[db9]: http://wiki.icomp.de/wiki/DB9-Joystick
[cable]: https://www.aliexpress.com/item/33012270252.html?spm=a2g0s.9042311.0.0.74394c4diOD0iB

## 3-buttons firmware

Use this firmware if you plan to play games that require 2 or more joystick buttons.
Suitable for some Amiga/Atari ST games.

* Download firmware [0.5beta-1 or newer][firmware]
* Unzip it, and install the one that is in the `amiga` folder.
* Read the README.md that is in the `amiga` folder and follow the intructions.

[firmware]: https://github.com/ricardoquesada/unijoysticle2/releases

### Amiga family

![Amiga](https://lh3.googleusercontent.com/lsG9gSNVQxaz8YUH3pqvO3SJ5bC_KX_t5G5ELI2jOsepYODRma7IoazxTutNzX-ChzpyysxyXTaWImN30KlCfQY0BiwCb6ogWADzXNHZKD5IcnvG-i_wIANtQdj0_y9CNRPmcVPay28=-no)

Tested on:

* Amiga 500 with default power supply: Unijoysticle **cannot** be self-powered (not enough current).
* Connect DB9-extension cable
  * to Unijoysticle port 1.
  * to the Amiga port 2 (games usually expect joystick on port 2)

### Atari ST family

![AtariST](https://lh3.googleusercontent.com/HxxVCTN8gu6_5pXb_-dOB03FHvW7EcrazyEUyamJZzMliLzYk8RO82HYK8qtF9C5LQ1qz72myjmpceX8-OAvg2W_CrR0xp8GzzVGmsROG6su5RE19rlv2wdwLUGc2Y_dkCSxHFDfVPQ=-no)

Tested on:

* Atari ST 1040F: Unijoysticle can be self-powered.
* Atari ST doesn't have a 3rd-joystick button, but it does a 2nd one.
  Use the "3-button firmware" to play games that use the 2nd button.
* Connect DB9-extension cable
  * to Unijoysticle port 1.
  * to the Atari ST port 2 (games usually expect joystick on port 2)

## Benefits / Limitation

The 3-buttons firmware has the following benefits / limitations:

* Supports the 3-joystick buttons (yay!). Suitable for certain Amiga/Atari ST games.
* But only one gamepad can be connected. That means:
  * Unijoysticle's `enhanced mode` cannot be activated.
  * Cannot use just one Unijoysticle to play games that requires two joysticks
    (it requires two Unijoysticles).
