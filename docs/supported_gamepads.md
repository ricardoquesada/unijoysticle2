# Unijoysticle 2 gamepads

## Supported devices

### Bluetooth Classic: Supported

All Bluetooth Classic HID devices are supported, or should be easy to support them.
Example of Bluetooth Classic HID devices are:

- Xbox One gamepad
- Sony Dualshock 4 (in PC mode)
- Android gamepads
- PC/Windows gamepads
- iCade joystick
- Some TV remote controls, like the Amazon Fire TV
- Some mice
- Some keyboards

### Unknown

I don't have any of these devices. It is possible that it might be easy to support them, or not.

- Nintendo Switch controllers
- Steam controllers

### Bluetooth BLE: Not supported ATM

But not every Bluetooth HID device is "Classic". Some of them are "BLE" (low energy).
And "BLE" devices are **not supported** at the moment, like:

- Apple TV remote control (1st gen)
- Nexus Android TV remote control

The good news is that all popular Bluetooth gamepads are Classic (not BLE).

### Non-Bluetooth: Not supported

Not every wireless device is Bluetooth. If the device doesn't explicity say
it is a Bluetooth, most probably it is not a Bluetooth device, hence not supported by Unijoysticle.

Devices known to be non-Bluetooth:

- mice / keyboards that come with their own wireless dongle.
- NVIDIA Shield gamepad

## Virtual gamepad

Internally, all devices are converted to a virtual gamepad which is very similar
to the Android/Xbox One gamepads layout. The different parsers convert the physical
gamepads to the virtual gamepad.

Button are mapped based on physical position, and not on names. For example, 8bitdo N30 gamepad
uses the Nintendo layout, which is different than the Virtual Gamepad layout:

```
N30 layout       Virtual Gamepad layout
    X                     Y
    ^                     ^
Y<-   ->A             X<-   ->B
    v                     v
    B                     A
 ```

 So, instead of honoring the button names, N30 will get remapped to match the
 virtual gamepad layout, meaning that:

- Button B -> A
- Button A -> B
- Button Y -> X
- Button X -> Y

### Virtual gamepad mappings

Many of the virtual buttons/pads are left unmapped, but could be mapped in the future.

![virtual_gamepad][1]

- 1: D-pad
- 2: Axis X & Y, Button Thumb Left
- 3: Axis Rx & Ry, Button Thumb Right
- 4: Button X
- 5: Button A
- 6: Button Y
- 7: Button B
- 8: Button Shoulder Right
- 9: Accelerator, Trigger Button Right
- 10: Brake, Trigger Button Left
- 11: Button Shoulder Left
- M1: Button System
- M2: Button Home
- M3: Button Back

## Basic mode

![basic mode][2]

- D-pad/joypad: controls up/down/left/right
- Button A: fire button
- Button B: "up"  (ideal for platform games)
- Button shoulder-right: autofire
- System button swaps between Joystick #1 and #2

## Enhanced mode

![enhanced mode][3]

- Left joypad / d-pad: control Joystick #2 movements
- Right joypad: control Joystick #1 movements
- Button A: fire for Joystick #2
- Button B: fire for Joystick #1
- Button Shoulder Left: auto-fire for Joystick #1
- Button Shoulder Right: auto-fire for Joystick #2

## Tested gamepads

Tested gamepads so far.

| Model              | Notes                       | Names                                                       |
| ------------------ | --------------------------- | ----------------------------------------------------------- |
| ![Xbox One][4]     | See [issue #1][23]          | [Xbox One][13]                                              |
| ![ps4_gamepad][5]  | Must be in PC mode          | [Sony Dualshock 4][14]                                      |
| ![Android][6]      |                             | [ASUS][15], [Moga Pro 2][16], [Amazon Fire TV gamepads][17] |
| ![Nimbus iOS][7]   |                             | [SteelSeries Nimbus][18] for iOS                            |
| ![OUYA][8]         | Buttons: O,U,Y,A -> A,X,Y,B | [OUYA (1st gen)][19]                                        |
| ![8bitdo NES30][9] | Buttons: B,Y,X,A -> A,X,Y,B | [8bitdo NES30][20]                                          |
| ![iCade][10]       |                             | [ION iCade][21]                                             |
| ![Generic][11]     | [*] See below               | Generic one                                                 |
| ![TV Remote][12]   |                             | [Amazon Fire TV remote control][22] (1st gen)               |

[*] Generic gamepads:

- Select Button + X + Right trigger to enter into Gamepad mode
- Select Button + X + Left trigger to enter in iCade mode.


[1]: https://lh3.googleusercontent.com/sfRd1qSHaxe4he4lt63Xjsr_ejmrthB00bPpIj4CwuUOyzKy3otIrdsPqhy_Y0U78Ibcw5bssuUOgKxNsvhvq6AQGlmigtj2tWA67HQHEaDU4tEmq850Z47rwRW9EzAhFGi6XrgUhUI=-no
[2]: https://lh3.googleusercontent.com/hkoAJbbtSpY53cpU-FO76QjTOPwuwWgDiKhQuNdbWnSwiozcqUloeOHuPclvunSC3vjH55n8Og-_cZO2ZTq6BhEbKOc0gb3qmASyLMC7BfAbTBNXjrV2LxzJu8-q0cDMexzOYlD4QE8=-no
[3]: https://lh3.googleusercontent.com/89CUlpgxrnDJ8b5hXdvHCi-X7d-2a6r6qP5vJbnFJWAHObfCsYy7Flq7pYpwrv-qXy-dT_-Jk02tgWQpgwnedKrC5STNhpl_Xd2OtJ8lgP3PnEvKDIiumTB_PZHdg5qCxsEZLc5-dWU=-no
[4]:  https://lh3.googleusercontent.com/YmONc-MhVZhnE8HVRgzH7FKSpT_29MLeIF70U5AfrcBuCtuNJ2Ln5xkmSpNqO0myrFpnDLbFvR2TRTRu0xcqvP3cLNaq1BBpruEAn-Z7vBbwzNtaXx7eQaLLF7aa8tt2Wa0IcYxeD08=-no
[5]: https://lh3.googleusercontent.com/_0sAxKXbSkk4g8rWJzTNxAirz2hD632jW4TGjGVOwjoac8sD4AfiN9PA1HdGWhm_ujcVygDlEG-LENPemF7IyFhqVsHgVHfCMVeFVjBbeDl-fUUjdMbRYAE8FiKdyWM_UBNUNmVy9Ro=-no
[6]: https://lh3.googleusercontent.com/S3H1pEGYGT5aVTwF3ySWHF7vqbonDYR0UxOLJBxFe5At6Q4AP_4TQUCaNOiEXD22U4H3C0lVP1E3m26H3QM4rIbgp1wysbQoSt1NpD61snlWES5N5zGUgx20c2sfFCKZL4w_Gl66Y1s=-no
[7]: https://lh3.googleusercontent.com/QeK4QebBIw4O-vWuyc-oxTGT_eST6BZ_2y6R9X5cuXPsQVQgZRdm5JEYs982dDKkYDs7AqCIGZyCQBRPJgLJ3ZxNqt_7KYMl9uKkWtmR0P89VbYgC4cMtkEFob2ihA8J6UxGHQ_4Tw0=-no
[8]: https://lh3.googleusercontent.com/FtbQLbt1QrzU59TTPQHIEarGZItlPik0bGWo40iDu0rnMwddCEwKMcy8LAe_fqzklaSKfMbt3-EvFJI4Vcoz3gSPTgC9MnTog3MyGfNWMc0Wq2Idq1kzjPOpRIS5OXeSqSSmIfGa5-w=-no
[9]: https://lh3.googleusercontent.com/2JN1IhyPhxFRTm-dUazcOq-iXm7p_F6xDZIP5hn5EEj5QZxxW4h1u7smPhRT-4uEu6DVf8sbRlsr8Io2cMbU6HGLMk7amKMCT6Q0k8wZwXL8sl86WuWVUoBundZH78k9wHTE3qOX4bQ=-no
[10]: https://lh3.googleusercontent.com/owslbSElM2BJL5M9h3hqksaCJhjAGf7DyfEwRFxxqjdG3Y73D5V9ScI0zVNokmSJMO6jrHMuX7j437kB-ER7kCAzc8GPX4ir9MPEVdypuxMneoIuzp3yAY8DqvkItbSZY0hlaAUMPn8=-no
[11]: https://lh3.googleusercontent.com/JG0sQGQ4lmFIITl_nincUDdPi-mlYPol-RSQrnoxsYZf1_cc16A4WMod_ttuLJoIQigvcZ_ZF6NiA7p54bBQP-Eu52b28mbjfVCwsMjuu_LCQB9Lj0k9e5UkW_PkRM12IB0HrW8ah0k=-no
[12]: https://lh3.googleusercontent.com/qnSdv7NM5et0vDhMQsRp7oMniqcjYxGKN9QJY0_gRWT6NXFrdWBf94JKNvP77abBZoykaSQOJBtXUnGW-Z1yF-MWn3q3t2Nt_TUVVV7a2HsPFjRc_DIuLh8tPiQNsEZSWDsb0z6Ys3k=-no
[13]: https://www.xbox.com/en-US/xbox-one/accessories/controllers/xbox-wireless-controller
[14]: https://www.playstation.com/en-us/explore/accessories/gaming-controllers/dualshock-4/
[15]: https://www.asus.com/us/Home-Entertainment/Gamepad-TV500BG/
[16]: https://www.amazon.com/PowerA-MOGA-Pro-Power-Electronic-Games/dp/B00FB5RBJM?th=1
[17]: http://www.gamingonfire.com/2014-amazon-fire-gaming-controller-1st-gen/
[18]: https://steelseries.com/gaming-controllers/nimbus
[19]: https://www.amazon.com/OUYA-Wireless-Controller/dp/B002I0GX38?th=1
[20]: https://www.ebay.com/itm/8Bitdo-NES30-Classic-Edition-Controller-set-for-Nintendo-Switch-Android-PC-Mac/192855559380
[21]: https://www.amazon.com/ION-iCade-Arcade-Bluetooth-Cabinet/dp/B004YC4NH6
[22]: https://www.amazon.com/Alexa-Voice-Remote-Amazon-Stick/dp/B071D41YC3
[23]: https://gitlab.com/ricardoquesada/unijoysticle2/issues/1