# Supported devices

![Supported gamepads][Supported gamepads]

[Supported gamepads]: https://lh3.googleusercontent.com/nMFlbXHBq_bhSpL7EhAN4Xb8CZEm73u41DxDI2HrACay-RAWuCVfRCWgRyM5XL3qGqQksOmkMdxiYA2HUW1GuGp17b6DTvmGEDQRgzgKxGBbEVOIkvYcGGNHV_HTsz8f43wTwAly9yE=-no

## Bluetooth Classic: Supported

All Bluetooth Classic HID devices are supported, or should be easy to support them.
Example of Bluetooth Classic HID devices are:

- Xbox One S gamepad
- Sony Dualshock 4 (in PC mode)
- Nitendo Wii / Wii u controllers
- Android gamepads
- PC/Windows gamepads
- iCade joystick
- Some TV remote controls, like the Amazon Fire TV
- Some mice

## Bluetooth BLE: Not supported ATM

Not every Bluetooth HID device is "Classic". Some of them are "BLE" (low energy).
And "BLE" devices are **not supported** at the moment, like:

- Apple TV remote control (1st gen)
- Nexus Android TV remote control

The good news is that all popular Bluetooth gamepads are Classic (not BLE).

## Non-Bluetooth: Not supported

Not every wireless device is Bluetooth. If the device doesn't explicity say
it is a Bluetooth, most probably it is not a Bluetooth device, hence not supported by Unijoysticle.

Devices known to be non-Bluetooth:

- mice / keyboards that come with their own wireless dongle.
- NVIDIA Shield gamepad

# Tested gamepads

Tested gamepads so far.

## Xbox One S
[![Xbox One S][xbox_one_s]][13]

- Must be the *Xbox One S* and not the *Xbox One* gamepad. The *Xbox One S* supports Bluetooth, while the regular *Xbox One* doesn't.
- Press *Xbox* button to swap joystick port
- Known Issues: [issue #1][23]

[xbox_one_s]: https://lh3.googleusercontent.com/YmONc-MhVZhnE8HVRgzH7FKSpT_29MLeIF70U5AfrcBuCtuNJ2Ln5xkmSpNqO0myrFpnDLbFvR2TRTRu0xcqvP3cLNaq1BBpruEAn-Z7vBbwzNtaXx7eQaLLF7aa8tt2Wa0IcYxeD08=-no

## Sony DualShock 4

[![ps4_gamepad][dualshock_4]][14]

- [Must be in PC mode][25]. Clones might not work.
- Press *Play* button to swap joystick port
- Known issues: [issue #4][32]

[dualshock_4]: https://lh3.googleusercontent.com/_0sAxKXbSkk4g8rWJzTNxAirz2hD632jW4TGjGVOwjoac8sD4AfiN9PA1HdGWhm_ujcVygDlEG-LENPemF7IyFhqVsHgVHfCMVeFVjBbeDl-fUUjdMbRYAE8FiKdyWM_UBNUNmVy9Ro=-no

## Wii Remote

[![Wii Remote][wii_remote]][29]

- Supports both Wii Remote and Wii Remote Motion Plus.
- Supports 3 modes:
  - Sideways mode (default): Use Wii Remote in [horiontal position][wii_sideways].
  - Vertical mode: enter by pressing button "A" while connecting.  LED #4 will be on in this mode.
  - Accelerometer mode: enter by pressing "+" while connecting. LED #3 will be on in this mode.
- LEDs #1 and #2 indicates what joystick is being controlled. E.g: If LED #1 is lit, it means that the Wii Remote is controlling Joystick #1.
- Press *Home* button to swap joystick port
- Known issues: [issue #6][30]

[wii_remote]: https://lh3.googleusercontent.com/HtQgfME-mwm59JFfASHLwHRzvrfesY_FkJTZKfUSAD5XTsPhi-r7Veqvs3n5zr5igm5ug9WmL3rKWuoA7AToeXKIsHpSeMhFRfHfTi53mqu5boTHRtzQSrUex8kHEd8Ny6CS0bpUhEk=w380-no
[wii_sideways]: https://forums.dolphin-emu.org/Thread-how-to-hold-the-wii-remote

## Wii U Pro controller
[![Wii U Pro][wii_u_pro]][27]

- LEDs #1 and #2 indicates what joystick is being controlled. E.g: If LED #1 is lit, it means that the Wii Remote is controlling Joystick #1.
- Press *Home* button to swap joystick port
- Known issues: [issue #6][30]

[wii_u_pro]: https://lh3.googleusercontent.com/kfKAySKzV-lLG7VmQGfCES1KuhtjBcTIfMzo59FgABcL7Ir9Tp7fQqrTP2iFqf8UVIhce1JhIXyBN_EH9eXpjlf5Q4b9NhhyxrFX9H0yVVRF0_pghjjz3pVqmY4uxS-FMgr7FC7egNo=w360-no

## Android

![Android][android_gamepad]

Tested with different Android gamepads:

- [ASUS][15]
- [Moga Pro 2][16]
- [Amazon Fire TV gamepads][17]

Press the main/big button in the center (depends on the Android gamepad) to swap joystick port.

[android_gamepad]: https://lh3.googleusercontent.com/S3H1pEGYGT5aVTwF3ySWHF7vqbonDYR0UxOLJBxFe5At6Q4AP_4TQUCaNOiEXD22U4H3C0lVP1E3m26H3QM4rIbgp1wysbQoSt1NpD61snlWES5N5zGUgx20c2sfFCKZL4w_Gl66Y1s=-no

## Nimbus SteelSeries

[![Nimbus SteelSeries for iOS][nimbus_steelseries]][18]

- Tested with Nimbus SteelSeries for iOS.
- Press *Menu button* to swap joystick port

[nimbus_steelseries]: https://lh3.googleusercontent.com/QeK4QebBIw4O-vWuyc-oxTGT_eST6BZ_2y6R9X5cuXPsQVQgZRdm5JEYs982dDKkYDs7AqCIGZyCQBRPJgLJ3ZxNqt_7KYMl9uKkWtmR0P89VbYgC4cMtkEFob2ihA8J6UxGHQ_4Tw0=-no

## OUYA

[![OUYA 1st gen][ouya_1gen]][19]

- Mappings: Buttons: O,U,Y,A -> A,X,Y,B.
- Only 1st gen is supported. It is unknown the status on newer version. They might or might not work.
- Press *OUYA button* to swap joystick port
- Known issues: [issue #7][31]

[ouya_1gen]: https://lh3.googleusercontent.com/FtbQLbt1QrzU59TTPQHIEarGZItlPik0bGWo40iDu0rnMwddCEwKMcy8LAe_fqzklaSKfMbt3-EvFJI4Vcoz3gSPTgC9MnTog3MyGfNWMc0Wq2Idq1kzjPOpRIS5OXeSqSSmIfGa5-w=-no

## 8Bitdo NES30

[![8bitdo NES30][8bitdo_nes30]][20]

- Only tested with 8Bitdo NES30. It is probable that other 8Bitdo are supported as well.
- Mappings: Buttons: B,Y,X,A -> A,X,Y,B.
- Press *Start button* to swap joystick port
- Known issues: [issue #3][24]

[8bitdo_nes30]: https://lh3.googleusercontent.com/2JN1IhyPhxFRTm-dUazcOq-iXm7p_F6xDZIP5hn5EEj5QZxxW4h1u7smPhRT-4uEu6DVf8sbRlsr8Io2cMbU6HGLMk7amKMCT6Q0k8wZwXL8sl86WuWVUoBundZH78k9wHTE3qOX4bQ=-no

## iCade

[![iCade][icade]][21]

- The original iCade cabines works great.
- Press *Top Right button* to swap joystick port
- Might work with other devices that support the iCade protocol, but the `uni_hid_device_vendors.h` file might need to be updated.

[icade]: https://lh3.googleusercontent.com/owslbSElM2BJL5M9h3hqksaCJhjAGf7DyfEwRFxxqjdG3Y73D5V9ScI0zVNokmSJMO6jrHMuX7j437kB-ER7kCAzc8GPX4ir9MPEVdypuxMneoIuzp3yAY8DqvkItbSZY0hlaAUMPn8=-no

## Amazon Fire TV Remote

[![Amazon Fire TV Remote 1st gen][fire_tv_remote]][22]

- Only *1st gen* is supported. Apparently *2nd gen* uses BLE intead of BT Classic.
- Press *Home button* to swap joystick port

[fire_tv_remote]: https://lh3.googleusercontent.com/qnSdv7NM5et0vDhMQsRp7oMniqcjYxGKN9QJY0_gRWT6NXFrdWBf94JKNvP77abBZoykaSQOJBtXUnGW-Z1yF-MWn3q3t2Nt_TUVVV7a2HsPFjRc_DIuLh8tPiQNsEZSWDsb0z6Ys3k=-no

## Generic HID devices

![Generic][generic_gamepad] 

In general, any Bluetooth Classic (not BLE) device that supports HID is supported, or should be easy to support it.

There many *generic* Bluetooth devices that sometimes are offered as gifts in conferences. Usually these *generic* Bluetooth devices have different connection modes. Use the HID one.

- Select Button + X + Right trigger to enter into Gamepad mode
- Select Button + X + Left trigger to enter in iCade mode.

[generic_gamepad]: https://lh3.googleusercontent.com/JG0sQGQ4lmFIITl_nincUDdPi-mlYPol-RSQrnoxsYZf1_cc16A4WMod_ttuLJoIQigvcZ_ZF6NiA7p54bBQP-Eu52b28mbjfVCwsMjuu_LCQB9Lj0k9e5UkW_PkRM12IB0HrW8ah0k=-no

# Technical notes: Virtual gamepad

Internally, all devices are converted to a virtual gamepad which is very similar
to the Android/Xbox One gamepads layout. The different parsers convert the physical
gamepads to the virtual gamepad.

Button are mapped based on physical position, and not on names. For example, 8bitdo N30 gamepad
uses the Nintendo layout, which is different than the Virtual Gamepad layout:

```
NES30 layout     Virtual Gamepad layout
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

## Virtual gamepad mappings

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



[1]: https://lh3.googleusercontent.com/sfRd1qSHaxe4he4lt63Xjsr_ejmrthB00bPpIj4CwuUOyzKy3otIrdsPqhy_Y0U78Ibcw5bssuUOgKxNsvhvq6AQGlmigtj2tWA67HQHEaDU4tEmq850Z47rwRW9EzAhFGi6XrgUhUI=-no
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
[24]: https://gitlab.com/ricardoquesada/unijoysticle2/issues/3
[25]: https://www.techradar.com/how-to/gaming/how-to-use-the-ps4-dualshock-4-controller-on-a-pc-1309014
[27]: https://en.wikipedia.org/wiki/Wii_U_Pro_Controller
[29]: https://en.wikipedia.org/wiki/Wii_Remote
[30]: https://gitlab.com/ricardoquesada/unijoysticle2/issues/6
[31]: https://gitlab.com/ricardoquesada/unijoysticle2/issues/7
[32]: https://gitlab.com/ricardoquesada/unijoysticle2/issues/4