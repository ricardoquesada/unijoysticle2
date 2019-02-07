# Unijosyticle v2

Like the Unijoystile, but remove WiFi and add Bluetooth.

## Goal #1

**Enhance user-experience in retro computers by using modern bluetooth devices**.


*Enhance user-experinece* is a user-experience that is only possible by using modern devices. For example:

*  Gamepads are more ergonomic than joysticks from the 80's.
*  Gamepads have more buttons, and can be mapped to different options. eg: Button 'B' could be mapped to 'Jump'. Ideal in platform games.
*  Combo Joy+Joy: One gamepad could control 2 joysticks at the same time
*  Combo Mouse+Joy: One gamepad could be used as joystick + mouse (ideal for Atari ST / Amiga).
*  And of course, using a unicycle to connect to your retro computer so you can play "The Uni Games" properly.


*Modern bluetooth devices* includes, but not limited to:

*   Gamepads (iOS, Android, Xbox, PS4, Switch, etc.)
*   Smart TV remote controllers
*   Mice
*   Smartphones


*Retro computers* includes, but not limited to:

*   Commodore 64, 128
*   Commodore VIC 20
*   Commodore Amiga
*   Atari ST
*   Atari 8-bit faimily
*   FPGAs like [ZX-UNO](http://zxuno.speccy.org/index_e.shtml)

These are all computers that have compatible DB9, meaning that POWER & GROUND lines are the same.
Initially, I don't want to support computers where POWER/GROUND use different lines, like the Mastersystems.
That could be very dangerous.

See here [list of compmabile systems](http://zxuno.speccy.org/index_e.shtml).

In the future, we could do a PC release to support PCjr, Tandy 1000 and other PCs.


## Goal #2

We want to create a solid, high quality product. But most important is to have fun and learn new things while developing it.

## TODO

The project is divided in 3:

### Hardware

We can reuse parts of Unijoysticle v1, but a few things should be added / changed:

*   Control all 7 lines: UP, DOWN, LEFT, RIGHT, FIRE, BUTTON LEFT (POT X), BUTTON RIGHT (POT Y).
    Unijoysticle v1 only controls the UP, DOWN, LEFT, RIGHT, FIRE. Four 4066, instead of three, are needed.
*   Support for C64 mouse: uses pot x / pot y, and they are both input+output lines. Additional hardware requirements might be needed.
*   Is it possible to power the ESP32 directly from the joystick ports?
*   In any case offer +5V power jack for external power supply (like in Unijoysticle v1).
*   Button to select the different modes: Single, Combo Joy+Joy, Combo Mouse+Joy
*   Button to remove all bluetooth stored keys (?) (might not be needed).
*   Switch to swap ports A + B (A game might require the joy connected to port A, while other to port B).
*   Offer cables to connect to different machines. (eg: for the Atari ST, it needs extension cables since the ports un under the case).

Note: No additional hardware is needed to support for Amiga/Atari ST mice.

Schematics + PCB in [KiCad](http://kicad-pcb.org/). Unijoysticle v1 was done in [Eagle](https://www.autodesk.com/products/eagle/overview). Since we want to learn new things, we are switching to KiCad now.


### Firmware

What's already done:

*   Support Bluetooth Classic HID devices
*   Supports up until 2 gamepads connected, or one mouse + one gamepad.
*   Basic generic mapping for gamepad
*   Mouse kind of working... movement is not smooth yet.

Missing:

*   Mouse: button are not mapped.
*   Mouse: smooth movement.
*   Gamepad: mappings based on product id + vendor id. Take DB from libSDL and addap the mappings to our own needs.
*   Fetch product id + vendor id from SDP record (don't know how to do it).
*   Better Bluetooth connect / reconnect
*   Add support for Bluetooth LE devices (eg: Some smart TV remote controllers are BLE).
*   Report back to client mode being used in the gamepads LEDS (in case avaiable).
    The LEDs could be used for whatever purpose we want.

### Smartphone client

Create Android (iOS lower priority) client that allows us to:

*    Works as a Bluetooth client
*    Implement "Unijosytcile" mode: gyro / accel
*    Implement virtual gamepad
*    Implement Gyruss mode
*    Add way to see logs
*    Add way to swtich between different modes (Combo Joy+Joy, Combo Mouse+Joy, Single) (?)
*    Add way to swap ports (?)

Since we want to learn new stuff, instead of coding the client in Java (like in Unijoysticle v1), we should do it in Kotlin.
