# Unijoysticle v2.0

Unijoysticle + bluetooth.

## About

Use modern bluetooth gamepads / mouse in old computers like the Commodore 64, Atari ST, Amiga 500, Apple 2, Tandy 1000, IBM PC Jr., Atari 800, etc.

## Status

Early develop stages. PoC working on PC. Need the rest.

- firmware works on PC.
- missing all the rest.


## Want to help ?

### Local development 
- Download libusb: https://libusb.info/ (needed to test on PC with bluetooth dongle).
- Download BlueKitchen: https://github.com/bluekitchen/btstack
- Download Unijoysticle code: https://gitlab.com/ricardoquesada/unijoysticle
- Get any bluetooth gamepad (iOS, Android, Xbox tested. PS4 not supported ATM)
- For ESP32:
  - Download ESP-IDF: https://github.com/espressif/esp-idf
  - Get an ESP32 module, like [the MH-ET Live][1] which is pin-compatible with [Wemos D1 Mini][2] (used by Unijoysticle v0.4.2 PCB).

### Compile BTstack

#### For PC/Linux/Mac development

- Install the Bluetooth USB dongle on your PC/Mac/Linux
- libusb: Compile and install. Don't use `master` tip-of-tree if you are on macOS. Use 1.0.22 or earlier
- bluekitchen: Compile the libusb port to make sure everything works.

```sh
$ cd src/btstack/port/libusb
$ make
$ ./gap_inquiry
```

Put your gamepad in bluetooth discovery mode and you should see it.

#### For ESP32 development
```sh
$ cd src/btstack/port/esp32
$ ./integrate_btstack.py
$ cd example/gap_inquiry
$ make menuconfig
$ make flash monitor
```
And just in case, read the `README.md` that is in the `src/btstack/port/esp32` folder.

Put your gamepad in bluetooth discovery mode and you should see it.

### Compile Unijoysticle

Once you know that BTStack is working as expected, you can try with the UniJoystiCle code.

For PC/Linux/Mac development:
```sh
$ cd src/unijoysticle/firmware/esp32/tools
$ make
./unijoysticle
```

For ESP32 development:
```sh
$ cd src/unijoysticle/firmware/esp32
$ make menuconfig
$ make flash monitor
```

Put the gamepad in discovery mode. The gamepad should be recognized and when you press buttons, you should see them on the console.

### Vagrant development (lazy way)

A vagrant file is provided with virtual linux boxes and the previous instructions scripted. VirtualBox provider is required for USB compatibility. Read the instructions inside the vagrant file to fill up the 'VendorID' and 'ProductID' of your ESP32 USB Serial or bluetooth dongle.

#### ESP32 

```sh
$ cd firmware
$ vagrant up
$ vagrant ssh
$ cd /vagrant/
#ESP serial will showup in /dev/ttyUSB0. Configure accordingly.
$ make menuconfig
$ make flash monitor
```

#### Virtual linux

```sh
$ cd firmware/tools
$ vagrant up
$ vagrant ssh
$ make
$ ./gap_inquiry
```

## What works:

- PC + Bluetooth dongle. Ideal for rapid development. Eastier to test new Bluetooth features and debug.
- Works on ESP32 as well
- It supports up until 4 gamepads at the same time.
- Discovery/Connect/Disconnect/Reconnects works
- Parses HID and identifies all possible gamepad buttons / pads / hats.

## What's missing

### Firmware:
- Create mapping code. Something that correctly maps the different gamepad buttons to the desired ones.
- Support Class / Extended modes:
   - Mode Classic: traditional modes with 1 or 2 gamepads (like one or two joysticks)
   - Mode extended: one gamepad controls 2 joysticks
- Test everything on esp32
  - Disable non required features like WiFi that it takes less current.
- Support mouse/pads: ideally a bluetooth mouse could be used.

### Hardware

- it is possible that the board could get current from the c64/atari's joystick ports?
- design new board, if possible one that doesn't use devkits
- lines for the C64 / Atari pots
- PC Jr. / Tandy 1000 / Apple II: investigate, they use analog lines

### Mobile application

- [Optional]: Simple Bluetooth application that connects to the host and allow us to configure it
  and see its status, etc.


[1]: https://www.aliexpress.com/item/MH-ET-LIVE-ESP32-MINI-KIT-WiFi-Bluetooth-Internet-of-Things-development-board-based-ESP8266-Fully/32819107932.html
[2]: https://wiki.wemos.cc/products:d1:d1_mini
