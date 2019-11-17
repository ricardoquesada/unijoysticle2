# Unijoysticle 2 User Guide

![Unijoysticle 2](https://lh3.googleusercontent.com/cbeL59-n7k_9RIFQCdspwVP8zAm3nssiOad_g7NGF83SjWvAHnhD2opSXFDXh7e1WJnX6LrM31MhGfoeHxgKKDaAJwnOmYoFqY9mrfEv7KCXQWg1RYVepyljDuJCSbkh5gDNzbsNNb8=-no)

- Toggle Mode button: Toggles between "Basic" and "Enhanced" modes
- Reboot button: Reboots the Unijoysticle 2
- LEDs: Green/Red LEDs turn on when Joystick 1/Joystick 2 are attached
- Self-Powered On/Off: When On, the Unijoysticle will be powered by the Commodore.

## Supported computers

![supported computers](https://lh3.googleusercontent.com/j9KjfEW5KXse1Caf0xV8WfD8c7HRFO1UCHx5WOnPMAneoKOPsDs8UNXAFS84D9pXzcu5ZdHoPxJDdqNvzUB_0q7hk7tQcqxYXQIa7NsLZ3j-KLlG-qyFI6TknNgiYNpwcIdXxEROOhI=-no)

The Unijoysticle 2 was designed to fit in the Commodore 64 / 128 ports. No additional
cables are needed for these computers.

However, the Unijoysticle 2 can be used in any computer that is compatible with the Atari DB9 joystick ports.

That includes, but not limtied to:

- Commodore 64 / SX-64 / 128 / 128-D.
- Atari 8-bit line, both computers and consoles (requires [DB9 extension cable][cable]).
- Amiga line (requires [DB9 extension cable][cable]).
- Atari ST line (requires [DB9 extension cable][cable]).

For Amiga / Atari ST 3-button joystick support, read [Amiga / Atari ST support](amiga_atarist.md).

[cable]: https://www.aliexpress.com/item/33012270252.html?spm=a2g0s.9042311.0.0.74394c4diOD0iB

## Soldering the kit

All components are through-hole. The only components that have polarity are the LEDs and the diodes.
See graphic for reference:

![Solering the kit](https://lh3.googleusercontent.com/OeZOaFWiLGXJBIcYT9sOwVjyqbsDSZoijTJW9cbUNGYfc9TbIJVF53CqkWTVfTdlYQfp77WaFv4bsRyZmPLXDquYdG8hyqrcCCb6tOtwiuIDGkAcJAjTXWARg1gh9Owzy4crkM6BMhQ=-no)

An assembled + soldered kit should look like this:

![Assembled kit](https://lh3.googleusercontent.com/f-C7DUbvMRB_aTx0MFTeJAaFxzJ2_EG6xE9aztIERBFYnqPDXcAmC_RI3-B546JMcBqZOAGRAwmOPGcqEdEO3BXl1xXhaQoPP2ANkf5qFqEea-H6qP6pvE_J2gKnZnpTIubd0NDPhZk=-no)

Needed components:

- 1 x Unijoysticle 2 PCB
- 1 x ESP32 Mini Kit (and its pins) (ref: B1)
- 2 x 74HC05N ICs
- 2 x 14p DIP sockets for the 7405s (ref: IC1, IC2)
- 1 x standard green LED 3mm (ref: D1)
- 1 x standard red LED 3mm (ref: D2)
- 2 x 1N4001 diode (ref: D3, D4)
- 2 x 150 ohm resistors (ref: R1, R2)
- 1 x Switch Tacticle SPST (ref: SW1)
- 1 x Switch Slide SPDT 200mA (ref: SW2)
- 2 x db9 female connectors (ref: J1, J2)
- 1 x DC Power Barrel Jack (ref: J3)

![Reference](https://lh3.googleusercontent.com/BZplH5gzBTbTEPQ1l5KSiLJBKZHsFWQEoTvIFTTcSLrdnKBCY7O1BuwaI28URDwALjSvUshcuRu5MHDktKl-I9ZqmWwRNEOlRW8g4KBjII-ZTMKznyK2nsnc92jYbycMiTUf-GYuUPw=-no)

You can source the components from here:

- Unijoysticle 2 PCB from: [PCBWay][3]
- ESP32 devkit from: [ESP32 Mini Kit][5]
- Remaining components: [DigiKey list][7]

## Flashing the firmware

See: [firmware_setup.md][1]

## Power on

![Self-powered](https://lh3.googleusercontent.com/j9ruthMtq84AaKz4ABCAuhsUWJ6tPFzelvwwb1t3MpEIMc7jXJaKpywNKp9GSX2qXQmdul5ZT7JB5g928YSXKaXNttvLVmMbJZaczqUGD1E_FaUtP9BlGxOHjQVOdEk5D674QHMxZfI=-no)

The Unijoysticle 2 can be powered in three different ways:

- Self-powered.
- USB-powered.
- +5V barrel jack-powered.

Note: It is safe to plug the three of them at the same time, but that won't give you any additional benefit.

### Self-powered

![self_powered](https://lh3.googleusercontent.com/XVQU7lkllCqc-1k6KX_3CdDIOlx0NCHO8NVDuBOJGdVef3Rq03KJpDHLqG_FNYW2GTeXOAxna9njsclcrlxmhOiBR_KvI-M8CDUOglUX9nCZLBILnkSB32Tews7yhmU38tfaVMxXnWU=-no)

- Gets current directly from the joystick ports. No extra cables needed.
- "Self-powered" switch must be "ON", otherwise the ESP32 won't receive current.
- A beefy [power supply with ~4Amps][power_supply] is recommended (depends on the peripherals used).
- Tested successfully with:
  - C128 + 1541 Ultimate 2 + Unijoysticle 2 + [beefy power supply][power_supply].
  - C64 + 1541 Ultimate 2 + Unijoysticle 2 + [beefy power supply][power_supply].
  - SX-64 + Unijoysticle 2
  - Atari ST 1040F

This features is only available on [Revision D][changelog_board] (and newer).

[changelog_board]: https://gitlab.com/ricardoquesada/unijoysticle2/blob/master/CHANGELOG.board.md

### USB-powered

![usb_powered](https://lh3.googleusercontent.com/lYiISEtede7TkKwvBZyOB57ZUynSDzPuKIqmfp6Cpl75BbGENM6qZkAXWD066YhpY1Xg-k016PrVt3783Q6iuLXFOdZrpXIW_XaEEwRaeUFvPBk1XVtwIvVjmxMGt5bvAPUHwOFScYw=-no)

- Connect the ESP32 with a micro-USB cable to your computer (or any other source).
- Ideal for debugging: you can see the Unijoysticle console by attaching a terminal to it.
- "Self-powered" switch should be in "OFF" (but no harm done if it is "ON").

### Jack Barrel-powered

![jack_barrel_powered](https://lh3.googleusercontent.com/REa_wfIZt5KEQT8ypO6d-OmpHLg8t8BUgz5tqnp-f6_ne7JgagdjGzp9RlPIbSXzIlAokX_ewJudmwD1Ony5OYq1Epd6-DnGMWVtXEafDw9H6DIvXlT3iffDOlmXTLoYWQhbR8TrLH8=-no)

- Connect a 5V+ / ~250mA to the Power Barrel Jack (like some Arduino boards).
- Polarity: positive polarity (tip=+5v, sleeve=0v).
- "Self-powered" switch should be in "OFF" (but no harm done if it is "ON").

[power_supply]: https://www.carlsenelectronics.net/

## Booting

You should see the two LEDS (green and red) blink one for ~1 second.
The Unijoysticle 2 will be ready once both LEDs are off.

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
[Commmando][10] or [1942][9] since you can throw grenades / do rolls with it.
It also opens up the possibility to create games that require more controls,
like [Robotron: 2084][8]

- Left joypad / d-pad: control Joystick #2 movements
- Right joypad: control Joystick #1 movements
- Button A: fire for Joystick #2
- Button B: fire for Joystick #1
- Button Shoulder Left: auto-fire for Joystick #1
- Button Shoulder Right: auto-fire for Joystick #2

## Troubleshooting

![Buttons](https://lh3.googleusercontent.com/Ck97IlSA8diFQ0E-SxdAkO6z2yRX-tfSJYtEd-zKqIy9vd8orW7kaOVqlWY5QKqgnBAtzPd3iwqfo2TKRwIwFIwdRS-vnB5pOriiBoccYz4chHoM7UOGV08OjvB95b_2uZIjxyGDJmw=-no)

### Gamepad cannot connect

This could be due to a lot of things. Assuming that you are using a [supported gamepad][2], try:

1. Unplug the Unijoysticle from the Commodore (turn off the Commodore first).

2. Reboot the Unijoysticle: Press the "Reboot" button that is placed in the ESP32 Mini Kit.

3. While rebooting, the LEDs should turn on, and after ~half a second, the should turn off.
   - If the LEDs don't turn On at all: file a bug (see below).
   - If the LEDs don't turn Off, it means that Bluetooth is not ready. Go to step 2.

4. Once the LEDs are off, trying connecting the Gamepad again.

5. If it fails press "Reboot + Toggle-Mode" buttons at the same time.
   This will reboot the Unijoysticle while also deleting the stored Bluetooth keys.

6. Put the gamepad in Bluetooth discovery mode (grab the manual of your gamepad). Try again.

7. If it fails, trying connecting the gamepad to a Linux (MacOs or Windows might be the same) machine first.
   If the gamepad cannot connect to Linux, then most probably it is a gamepad issue. Cannot help here.

8. Repeat. Go to Step 2.

If it keeps failing, file a bug (see below).

### Gamepad cannot re-connect

Assuming that the gamepad connects Ok for the first time, but fails to reconnect then:

- Press the Reboot + Toggle-Mode buttons at the same time.
  This will reboot the Unijoysticle while also deleting the stored BT keys.
  Any try again.

- Put the gamepad in Bluetooth discovery mode. And try again.

If none of the above works, file a bug (see below).

## Reporting bugs

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
3. Reboot the Unijoysticle
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


[1]: firmware_setup.md
[2]: supported_gamepads.md
[3]: https://www.pcbway.com/project/shareproject/Unijoysticle_2___Rev__D.html
[5]: https://www.aliexpress.com/store/product/MH-ET-LIVE-ESP32-MINI-KIT-WiFi-Bluetooth-Internet-of-Things-development-board-based-ESP8266-Fully/2348158_32819107932.html?spm=a2g0x.12010108.1000001.12.56543b1cEQVriV
[7]: https://www.digikey.com/short/pnq527
[8]: https://en.wikipedia.org/wiki/Robotron:_2084
[9]: https://csdb.dk/release/?id=38140
[10]: https://csdb.dk/release/?id=137173
