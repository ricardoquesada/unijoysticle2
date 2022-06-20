# Unijoysticle™ 2

[![discord](https://img.shields.io/discord/775177861665521725.svg)](https://discord.gg/r5aMn6Cw5q)

Like the original [Unijoysticle][1], but remove WiFi and add Bluetooth.

|   | Unijoysticle 2| Unijoysticle 2+| Unijoysticle 2 A500 |
| - | -------------- | --------------- | ------------------- |
|   | ![uni2_photo] | ![uni2_plus_photo] | ![uni2_a500_photo] |
| Total Size (mm) | 63 x 66 x 17 | 64 x 64 x 13.6 | 67 x 72 x 13.6 |
| PCB Size (mm) | 46 x 57 x 1.6 | 49 x 62 x 1.6 | 52 x 67 x 1.6 |
| Weight (gr) | 37 | 24 | 25.6 |
| Current (mA)| ~100 | ~96 | ~96 |
| Amiga 2nd & 3rd button support| Only in Port #1| Both in Port #1 and #2 | Both in Port #1 and #2 |
| C64 mouse support (1351) | No | No | No |
| Amiga / AtariST mouse support | Yes (1) | Yes (1) | Yes  (1)|
| Fits | C64 / C128 | C64 / C128 | Amiga 500 / 1200 |
| Buttons | Reset, Enhanced | Reset, Enhanced | Reset, Mode,  Swap |
| LEDs | Port #1, #2 | Port #1, #2 | Port #1, #2, Bluetooth |
| Filter noise for C128 ([Issue #17][issue_17]) | No | Yes | Yes |
| Case friendly | No | Yes | Yes |
| Easy to DIY | Yes | No | No |
| Self-powered support | Yes (2) | Yes (2) | Yes (2) |
| External power | Both USB and Barrel Jack 5V+ | Only USB | Only USB |
| USB connector | Micro USB | Micro USB | Micro USB |
| Release date | April 2019 | August 2021 | ??? 2022 |

(1): Requires firmware Bluepad32 v3.5 or newer

(2): Amiga 500 requires external power.

[issue_17]: https://gitlab.com/ricardoquesada/unijoysticle2/-/issues/17

Unijoysticle 2 allows you to use modern Bluetooth gamepads, e.g DualSense gamepad,
in retro computers like the Commodore 64, Amiga and AtariST.

It also supports mice (for Amiga / AtariST only).

[uni2_photo]: https://lh3.googleusercontent.com/DChZhkyEl-qqZ3r9N7_RhzvF4zDkSdgNyZwczBofnp28D6ncXcbGq3CXBc5SeC5zooUbBCRo87stuAx-4Q7FwItz1NfaZ4_EJjX3pIroiiR-fcXPzZWk0OifvtaoA8iUJsQQnhkC9q4=-no
[uni2_plus_photo]: https://lh3.googleusercontent.com/pw/AM-JKLVeTZLBOCy4GmrG5N-WiRIcqoxLdsVXSN-77reS92gn7xxmZy-JuE_XeXgwSSPaUBYa2qaaw5RvZbzlkHdjDxal2p_WkKIm9RnzD6qeqV_u7j_3sRJOkm35EO5JCXFp_EpLvCTHGNEX6ZOtMyOGrzqLQw=-no
[uni2_a500_photo]: https://lh3.googleusercontent.com/pw/AM-JKLXEB6NQ-lr54G6cPEVQJ9i1OGR0XWLVYsjCs4Sc_883w-gYvwnUOPlH2wnzM0ibH48Y6QGAAIRO9pnfTxDsdQqY7JHBKzJPzOOY8Cin6t9sSjHvx94k1VZLdTh1Fkknum6nIR0z1pAMz69txQRV7qQksg=-no 


## Basic functionality

One Bluetooth gamepad controls one joystick.
You need two gamepads to control the two joysticks.

![Basic mode](https://lh3.googleusercontent.com/hkoAJbbtSpY53cpU-FO76QjTOPwuwWgDiKhQuNdbWnSwiozcqUloeOHuPclvunSC3vjH55n8Og-_cZO2ZTq6BhEbKOc0gb3qmASyLMC7BfAbTBNXjrV2LxzJu8-q0cDMexzOYlD4QE8=-no)

The mappings are:

- D-pad/joypad: controls up/down/left/right.
- Button A: fire button
- Button B: "up"  (ideal for platform games).
- Button shoulder-right: autofire.
- System button swaps between Joystick #1 and #2

## Enhanced functionality

![Enhanced mode](https://lh3.googleusercontent.com/89CUlpgxrnDJ8b5hXdvHCi-X7d-2a6r6qP5vJbnFJWAHObfCsYy7Flq7pYpwrv-qXy-dT_-Jk02tgWQpgwnedKrC5STNhpl_Xd2OtJ8lgP3PnEvKDIiumTB_PZHdg5qCxsEZLc5-dWU=-no)

When in "Enhanced mode", you control the two joysticks with only one gamepad.
The mappings are:

- Left joypad / d-pad: control Joystick #2 movements.
- Right joypad: control Joystick #1 movements.
- Button A: fire for Joystick #2
- Button B: fire for Joystick #1
- Button Shoulder Left: auto-fire for Joystick #1
- Button Shoulder Right : auto-fire for Joystick #2

This mode is ideal for games like [Commando][2] or [1942][3] since it allows you
throw grenades / roll by pressing Button B.

## Supported controllers

![Supported gamepads](https://lh3.googleusercontent.com/pw/AM-JKLXpmyDvNXZ_LmlmBSYObRZDhwuY6hHXXBzAicFw1YH1QNSgZrpiPWXZMiPNM0ATgrockqGf5bLsI3fWceJtQQEj2_OroHs1SrxsgmS8Rh4XHlnFolchomsTPVC7o5zi4pXGQkhGEFbinoh3-ub_a4lQIw=-no?authuser=0)

- Sony DualSense
- Sony DUALSHOCK 4
- Sony DUALSHOCK 3
- Nintendo Switch Pro
- Nintendo JoyCons
- Nintendo Wii U
- Nintendo Wii + accesories
- Xbox Wireless controller (model 1708)
- Android gamepads
- PC/Window gamepads
- 8BitDo controllers
- iCade
- And more

See:

* [Supported gamepads][gamepads]
* [Supported mice][mice]

[gamepads]: https://gitlab.com/ricardoquesada/unijoysticle2/blob/master/docs/supported_gamepads.md
[mice]: https://gitlab.com/ricardoquesada/bluepad32/blob/develop/docs/supported_mice.md

## Order info

If you are looking for ready-to-use boards, you can purchase one from here:

<a href="https://www.tindie.com/stores/riq/?ref=offsite_badges&utm_source=sellers_riq&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>

Looking for a remix and/or 3rd party vendors. Go here: [SELLING_DEVICES.md][selling_devices]

[selling_devices]: SELLING_DEVICES.md

## More Info

- [Users guide][users_guide]
- [Discord][discord]
- [Email group][email_group]

[users_guide]: https://gitlab.com/ricardoquesada/unijoysticle2/blob/master/docs/user_guide.md
[discord]: https://discord.gg/r5aMn6Cw5q
[email_group]: https://groups.google.com/forum/#!forum/unijoysticle

[1]: https://retro.moe/unijoysticle
[2]: https://csdb.dk/release/?id=137173
[3]: https://csdb.dk/release/?id=38140
