# Amiga / Atari ST support

The Unijoysticle 2 can be used in any "Atari DB9 joystick" compatible computer.
That includes the 8-bit Atari family, the Commodore C64/C128, as well as the
Amiga and Atari ST (among others).

The Unijoysticle 2 was designed to fit in the Commodore 64 / 128 computers. If you
want to use in any other computer will one (or two) DB9 extension cables[cable].

The difference between the C64/C128/Atari-8bit family vs. the Atari ST and Amiga
is that the latter supports up to 3 buttons in the joystick, while the former only
supports 1 button.

If you want to enable the 3 buttons in the Unijoysticle you have to install the
`amiga` firmware (despite its name it also suitable for the Atari ST).

If you only plan to use games that require just one button, you can use the
`c64` firmware, and you can skip this documentation.
See the benefits/limitations below.

[cable]: https://www.aliexpress.com/item/33012270252.html?spm=a2g0s.9042311.0.0.74394c4diOD0iB

## 3-buttons Firmware

Use this firmware if you plan to play games that require 2 or more buttons:

* Download firmware [0.5beta-1 or newer][firmware]
* Unzip it, and install the one that is in the `amiga` folder.
* Read the README.md that is in the `amiga` folder and follow its intructions.

## Amiga line

![Amiga](https://lh3.googleusercontent.com/lsG9gSNVQxaz8YUH3pqvO3SJ5bC_KX_t5G5ELI2jOsepYODRma7IoazxTutNzX-ChzpyysxyXTaWImN30KlCfQY0BiwCb6ogWADzXNHZKD5IcnvG-i_wIANtQdj0_y9CNRPmcVPay28=-no)

Tested on:

* Amiga 500: Unijoysticle *cannot* be self-powered.
* Connect DB9-extension cable
  * to Unijoysticle port #1.
  * to the Amiga port #2 (games usually expect joystick on port #2)

## Atari ST line

![AtariST](https://lh3.googleusercontent.com/HxxVCTN8gu6_5pXb_-dOB03FHvW7EcrazyEUyamJZzMliLzYk8RO82HYK8qtF9C5LQ1qz72myjmpceX8-OAvg2W_CrR0xp8GzzVGmsROG6su5RE19rlv2wdwLUGc2Y_dkCSxHFDfVPQ=-no)

Tested on:

* Atari ST 1040F: Unijoysticle can be self-powered.
* Connect DB9-extension cable
  * to Unijoysticle port #1.
  * to the Atari ST port #2 (games usually expect joystick on port #2)

## Benefits / Limitation

The `amiga` firmware has the following benefits / limitations:

* Supports the 3 joystick buttons (yay!)
* But only one gamepad at the same time can be connected. That means:
  * `Enhanced mode` cannot be activated.
  * Cannot use just one Unijoysticle to play two player games (it requires two Unijoysticles).

[firmware]: https://github.com/ricardoquesada/unijoysticle2/releases
