# Unijoysticle 2 / 2+ User Guide

This guide is valid both for Unijoysticle 2 and Unijoysticle 2+.
Features that are only applicable for Unijoysticle 2 / 2+, are tagged as **[v2 only]** / **[v2+ only]** respectively.

Comparison between the two:

|   | Unijoysticle 2 | Unijoysticle 2+ |
| - | -------------- | ------------------ |
| Buttons / Switches / LEDs | ![uni2](https://lh3.googleusercontent.com/pw/AM-JKLUphquTBg9JoV-L7wuMtze_aKIJ8LvfokTakuBKSVFClziLWCViggcrlNZtqGUMgv6u6yYpZ_RuE2jdGSn3Q0oYl0jOQzzGcutRt-JiMjLZY_oAvK4LehrawNj_aNbthCJ-VEJzsW3dywhJNekjhTsfNQ=-no) | ![uni2plus](https://lh3.googleusercontent.com/pw/AM-JKLWV2Zo912VtOfuM71AluanNXGwVQiAehNEiQ1VL3L7SkWDl-9k0fA6tfza9QpGL52petBfFFFHMb8rh_ybSj17LOQA70IycMDQw6AVqlN8Jp4HDWT8sWcXHIPEQZTxNuQ-RFygKbmVpW2n52wwi5cJgwA=-no) |
| Amiga / AtariST 2nd & 3rd button support| Only in Port #1| Both in Port #1 and #2 (1) |
| C64 mouse support (1351) | No | No |
| Amiga / AtariST mouse support | Yes (2) | Yes (2) |
| Filter noise for C128 ([Issue #17][issue_17]) | No | Yes |
| Case friendly | No | Yes |
| Easy to solder | Yes. All components are through-hole | No. Most components are surface-mount |
| Self-powered | Yes, can be turned on/off with switch | Yes, always on |
| External power | Both USB and Barrel Jack 5V+ | Only USB |
| Size | 63 x 66 x 17 mm | 64 x 64 x 12 mm |
| Current | ~95mA | ~100mA |
| USB connector | Micro USB | Micro USB |

- Toggle Mode button: Toggles between *Basic* and *Enhanced* mode (see below for further info)
- Reset button: Resets the device
- Green / Red LEDs: Joystick 1 / Joystick 2 are attached
- Power LED: Red in Unijoysticle 2, Blue in 2+. If On, it means the device has current.
- [v2 only] Self-Powered On/Off: When On, the Unijoysticle will be powered by the Commodore.
- [v2+ only] Prog Mode: If programming the firmware fails, press this button to force "programming mode". Legacy feature, might be removed in future revisions.

* (1): Requires update in Bluepad32 firmware (WIP)
* (2): Requires update in Bluepad32 firmware (WIP)

[issue_17]: https://gitlab.com/ricardoquesada/unijoysticle2/-/issues/17

## Supported computers

![supported computers](https://lh3.googleusercontent.com/j9KjfEW5KXse1Caf0xV8WfD8c7HRFO1UCHx5WOnPMAneoKOPsDs8UNXAFS84D9pXzcu5ZdHoPxJDdqNvzUB_0q7hk7tQcqxYXQIa7NsLZ3j-KLlG-qyFI6TknNgiYNpwcIdXxEROOhI=-no)

The Unijoysticle 2 was designed to fit in the Commodore 64 / 128 ports. No additional
cables are needed for these computers.

However, the Unijoysticle 2 can be used in any computer that is compatible with the Atari DB9 joystick ports.

That includes, but not limited to:

- Commodore 64 / SX-64 / 128 / 128-D.
- Atari 8-bit line, both computers and consoles (requires [DB9 extension cable][cable]).
- Amiga line (requires [DB9 extension cable][cable]).
- Atari ST line (requires [DB9 extension cable][cable]).
- Commodore 16 / 116 / +4 (requires joyadaptercables)

For Amiga / Atari ST 3-button joystick support, read [Amiga / Atari ST support](amiga_atarist.md).

[cable]: https://www.aliexpress.com/item/33012270252.html?spm=a2g0s.9042311.0.0.74394c4diOD0iB

For Commodore 16/116/+4 you need two identical and suitable joyadapters to work with this design,
though a new design Unijoysticle 2 for the 264 is available, this one is multi-usable for C64 as for C16/116/+4.

You need joyadapters with suitable pinconnections:

If you want the Unijoysticle 2 with DB9 connectors to work on a C16/+4 together with 264 joyadapters,
you have to be sure that the adapters have:

Pin 1-4,6 connected on minidin/DB9, corresponding pinnumbers
Pin 5 (+5VDC) minidin NC
Pin 7 (GND) minidin NC (important criterium!)
Pin 8 minidin (Data/select) on pin 8 DB9 (GND)
USB external PSU (have not tried it with internal +5VDC pin, while amperage is a bit low)

Before connecting the joyadapters on the Unijoysicle 2 do measure the pinout,
while there are different variants!

## Flashing the firmware

See: [firmware_setup.md][firmware_setup]

[firmware_setup]: https://gitlab.com/ricardoquesada/bluepad32/-/blob/main/docs/firmware_setup.md

## How to power on the device

There are multiple ways to power on the device

|   | Unijoysticle 2 | Unijoysticle 2+ |
| - | -------------- | --------------- |
| Self-powered | Yes, requires the "Self powered" switch to be On | Yes, always On |
| USB powered | Yes | Yes |
| External 5V+ | Yes, using the Barrel jack | No |

Note: It is safe to plug the two / three of them at the same time, but that won't give you any additional benefit.

### Self-powered

| Unijoysticle 2 | Unijoysticle 2+ |
| -------------- | --------------- |
| ![uni2](https://lh3.googleusercontent.com/XVQU7lkllCqc-1k6KX_3CdDIOlx0NCHO8NVDuBOJGdVef3Rq03KJpDHLqG_FNYW2GTeXOAxna9njsclcrlxmhOiBR_KvI-M8CDUOglUX9nCZLBILnkSB32Tews7yhmU38tfaVMxXnWU=-no) | ![uni2plus](https://lh3.googleusercontent.com/pw/AM-JKLUXjhjUsPDIVH1C_i8310k5ERQT-IQc71w2ibmBWCHoKC5uEIHjHBdp52ydb0XBZoKqftGv8JIonAn9tfuxXnoo00BypKL62ZTk_kbOLEQwdXG7QM3FDhrHm41NAbP9dhAxn9N4M5pTxUMiOJ_T2oHgSw=-no) |

- Gets current directly from the joystick ports. No extra cables needed.
- [v2 only] "Self-powered" switch must be "ON", otherwise the ESP32 won't receive current.
- A beefy [power supply with ~4Amps][power_supply] is recommended (depends on the peripherals used).
- Tested successfully with:
  - C128 + 1541 Ultimate 2 + Unijoysticle 2 + [beefy power supply][power_supply].
  - C64 + 1541 Ultimate 2 + Unijoysticle 2 + [beefy power supply][power_supply].
  - SX-64 + Unijoysticle 2
  - Atari ST 1040F

This feature is available since Unijoysticle 2 [Revision D][changelog_board], and is present in all
Unijoysticle 2+ revisions.

[changelog_board]: https://gitlab.com/ricardoquesada/unijoysticle2/blob/master/CHANGELOG.board.md

### USB-powered

| Unijoysticle 2 | Unijoysticle 2+ |
| -------------- | --------------- |
| ![uni2](https://lh3.googleusercontent.com/lYiISEtede7TkKwvBZyOB57ZUynSDzPuKIqmfp6Cpl75BbGENM6qZkAXWD066YhpY1Xg-k016PrVt3783Q6iuLXFOdZrpXIW_XaEEwRaeUFvPBk1XVtwIvVjmxMGt5bvAPUHwOFScYw=-no) | ![uni2plus](https://lh3.googleusercontent.com/pw/AM-JKLXXbxm4umDQfC-xYt9AzvAWIXsGQaYrpQUFnDpYwE0F5SanC8DgjQu9Uu7s9nj2dAd1dVWq4WD8EWxifGM8t73bT0Mz-yiFPCXn8dyUgNXkW2FA2SA00PfL_kdCBbVpXKLRu1Ez7hnaMBSmlUiufBncxw=-no) |

- Use a micro-USB cable to connect the Unijosyticle device to your computer.
- Ideal for debugging: you can see the Unijoysticle console by attaching a terminal to it.
- [v2 only]: "Self-powered" switch can either be "On" or "Off".

### Jack Barrel-powered [v2 only]

![jack_barrel_powered](https://lh3.googleusercontent.com/REa_wfIZt5KEQT8ypO6d-OmpHLg8t8BUgz5tqnp-f6_ne7JgagdjGzp9RlPIbSXzIlAokX_ewJudmwD1Ony5OYq1Epd6-DnGMWVtXEafDw9H6DIvXlT3iffDOlmXTLoYWQhbR8TrLH8=-no)

- Connect a 5V+ / ~250mA to the Power Barrel Jack (like some Arduino boards).
- Polarity: positive polarity (tip=+5v, sleeve=0v).
- [v2 only]: "Self-powered" switch can either be "On" or "Off".

[power_supply]: https://www.carlsenelectronics.net/

## Using Gamepads

The first gamepad to connect will control joystick #2.
The second gamepad to connect will use the available joystick.

If you want to control joystick #1, and you only have one gamepad connected,
you have to press the "swap" button in the gamepad.

![swap joystick](https://lh3.googleusercontent.com/jT3RiP75ffx9zWv2Csq3LGl5aFvhwKTt4sk0XkWrr9eyOBSo89ICTf6VzLrsRCGmI3vvbLtwbC1OqSnqR8_P51HR063qZjpOaLLSDE4DHaWLjxy8zi4FyoitwMAM3tPVMkoiQpYNQNk=-no)

The "swap" button varies from gamepad to gamepad, but usually it is mapped to
the big button in the center. In the Xbox One it is the "Xbox" button.

If two gamepads are connected, then the swap button is disabled.

The gamepad could be in two possible modes:

- Basic mode: one gamepad controls one joystick.
- Enhanced mode: one gamepad controls the two joysticks.

### Basic mode

![basic mode](https://lh3.googleusercontent.com/hkoAJbbtSpY53cpU-FO76QjTOPwuwWgDiKhQuNdbWnSwiozcqUloeOHuPclvunSC3vjH55n8Og-_cZO2ZTq6BhEbKOc0gb3qmASyLMC7BfAbTBNXjrV2LxzJu8-q0cDMexzOYlD4QE8=-no)

"Basic mode" is what you would expect, with the additional benefit that
Button B is mapped to "jump". Ideal for platform games like Giana Sisters,
Super Mario Bros, Mayhem in Monsterland, etc.

- D-pad/joypad: controls up/down/left/right
- Button A: fire button
- Button B: "up"  (ideal for platform games)
- Button shoulder-right: autofire
- System button swaps between Joystick #1 and #2

### Enhanced mode

![enhanced mode](https://lh3.googleusercontent.com/89CUlpgxrnDJ8b5hXdvHCi-X7d-2a6r6qP5vJbnFJWAHObfCsYy7Flq7pYpwrv-qXy-dT_-Jk02tgWQpgwnedKrC5STNhpl_Xd2OtJ8lgP3PnEvKDIiumTB_PZHdg5qCxsEZLc5-dWU=-no)

In Enhanced mode, you control both joysticks from only one gamepad.
Since "Button B" is mapped to "J1 fire" this is great for games like
[Commando][commando] or [1942][1942] since you can throw grenades / do rolls with it.
It also opens up the possibility to create games that require more controls,
like [Commando 2084][commando2084]

- Left joypad / d-pad: control Joystick #2 movements
- Right joypad: control Joystick #1 movements
- Button A: fire for Joystick #2
- Button B: fire for Joystick #1
- Button Shoulder Left: auto-fire for Joystick #1
- Button Shoulder Right: auto-fire for Joystick #2

[1942]: https://csdb.dk/release/?id=38140
[commando]: https://csdb.dk/release/?id=137173
[commando2084]: https://csdb.dk/release/?id=182074

### Supported gamepads

![gamepads](https://lh3.googleusercontent.com/pw/AM-JKLWUZS_vlkMmd3o8EKzXlYCS0uriEW_gXfOoiFqZlABJi_dM1GWYHGafrdMnTP-VHgVdCdVA4pUageZgyI98RH1SHtydac2yyrx_vJVXgWPYBFN-SJoOikdlGuOowPoDqYOwfKU39yketYPJyRJlIPwjEw=-no)

- Sony DualSense
- Sony DUALSHOCK 4
- Xbox One S
- Nintendo Switch Pro
- Nintendo Wii U
- Nintendo Wii
- Android gamepads
- PC/Window gamepads
- 8BitDo
- iCade
- And more

For a complete list, see: [Supported gamepads][supported_gamepads]

## Troubleshooting

### Fails to boot

![booting](https://lh3.googleusercontent.com/pw/AM-JKLWhqgMB9Ysm8rpigW8leZ-9EVDI6V16cgqHZ367sgmLW5_ryNepZgCgczJwPRkreb9YBnEFCRXXY3mhwJk7wLR-vo2qRNmtjzNkC-4nnxtCKecsL4qI7CnLm1owSAOWeCwqHjyA9TxdaLE10FzuXWQLWg=-no)

Booting the device takes ~1 second. You should see:

- Power LED must be On
- J1 (Green) & J2 (Red) LEDs should stay On for ~1 second
- Once J1 and J2 are Off, the device will be ready to use

If one of the above mentioned conditions are not met, please file a bug (See "Filing bugs" down below).

### Gamepad cannot connect

This could be due to a lot of things. Assuming that you are using a [supported gamepad][supported_gamepads], try:

1. Unplug the Unijoysticle from the Commodore (turn off the Commodore first).

2. Reset the Unijoysticle: Press the "Reset" button that is placed in the ESP32 Mini Kit.

3. While rebooting, the LEDs should turn on, and after ~half a second, then they should turn off.
   - If the LEDs don't turn On at all: file a bug (see below).
   - If the LEDs don't turn Off, it means that Bluetooth is not ready. Go to step 2.

4. Once the LEDs are off, trying connecting the Gamepad again.

5. If it fails press "Reset + Toggle-Mode" buttons at the same time.
   This will reboot the Unijoysticle while also deleting the stored Bluetooth keys.

6. Put the gamepad in Bluetooth discovery mode (grab the manual of your gamepad). Try again.

7. If it fails, trying connecting the gamepad to a Linux (MacOs or Windows might be the same) machine first.
   If the gamepad cannot connect to Linux, then most probably it is a gamepad issue. Cannot help here.

8. Repeat. Go to Step 2.

If it keeps failing, file a bug (see below).

[supported_gamepads]: supported_gamepads.md

### Gamepad cannot re-connect

Assuming that the gamepad connects Ok for the first time, but fails to reconnect then:

- Press the Reset + Toggle-Mode buttons at the same time.
  This will reboot the Unijoysticle while also deleting the stored BT keys.
  Any try again.

- Put the gamepad in Bluetooth discovery mode. And try again.

If none of the above works, file a bug (see below).

## Filing bugs

File bug here: https://gitlab.com/ricardoquesada/unijoysticle2/issues

When you file a bug, make sure that you include as much information as possible:

- Gamepad you are using. If possible the firmware version the gamepad is using.
- Unijoysticle firmware.
- Computer that you are using: C64, C128, etc.
- How you are powering the Unijoysticle.
- Logs (this is the most important thing!)

### Unijoysticle logs

The logs can be fetched by connecting a terminal to the ESP32 module.

1. Connect the ESP32 module to your PC using a micro USB cable.
2. Launch any serial terminal, like the one that comes from Arduino.
3. Reset the Unijoysticle
4. Try to connect the gamepad again.
5. Let it try for a few seconds.
6. Copy & paste the output from the terminal and put it in the bug report.

### Arduino terminal step-by-step

1. Download Arduino from here: https://www.arduino.cc/en/main/software
2. Launch Arduino -> Tools -> Set Port

![Arduino Set Port](https://lh3.googleusercontent.com/ZFQuAf_6tvYutrRcdcduTdFJSS-dfhDcznTpv5GTkAVdKzsPgHBrpBcuZX5TApMCoc1FXI0wLnKkTKSxONlWGF0Y7RZXJxFmi3a4iZE8AZ_ovOCTl_a3Vd8jOUEbtX0g4m0F_OlHESo=-no)

3. Arduino -> Tools -> Serial Monitor

![Arduino Serial Monitor](https://lh3.googleusercontent.com/0z1QOhcuTcLnv-Ra-JrgEoOYD0-cH4tAumqxECO9jE6KdcItf7zycBx5tG4BWhUyISq_E5e7T9gC4fdAehkQ6WJDYAN3U6B2P5OwSsStEXOs6-kFkW1Kol0-Jf26Bno8dIxf7Jp1l0E=-no)

4. From the Serial Monitor, set Bauds to 115200

![Set Bauds](https://lh3.googleusercontent.com/evBxv1oQ2jv28wk29ofAKiM0CNMK2GVi6tXmrCX8Wml3xZG6MEz4WoAVIbyX2h21fYDGN7SvkYiFFmTxwVarR4Zm0oElPwzL-oHnIuW5FCOSzclQt3rRI_rrqw5LZ1SzceUBMBSDIjY=-no)


