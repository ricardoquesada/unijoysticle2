# Firmware setup

## How to help

Development can be done locally or using Vagrant for convinience. It's recommended to read the local instructions once (or the bootstrap.sh script) before using Vagrant.

### Local development

- Download BlueKitchen: https://github.com/bluekitchen/btstack
- Download Unijoysticle 2 code: https://gitlab.com/ricardoquesada/unijoysticle2
- Get a bluetooth gamepad
- For ESP32:
  - Download ESP-IDF: https://github.com/espressif/esp-idf
  - Get an ESP32 module, like [the MH-ET Live][1] which is pin-compatible with [Wemos D1 Mini][2] (used by Unijoysticle v0.4.2 PCB).
- For PC/Linux/Mac (optional, and for development only):
  - Download libusb: https://libusb.info/

### Compile BTstack

#### For ESP32 development

```sh
$ cd src/btstack/port/esp32
$ ./integrate_btstack.py
$ cd example/gap_inquiry
$ make menuconfig
$ make flash monitor
```

And just in case, read the [README.md][3] that is in the `src/btstack/port/esp32` folder.

Put your gamepad in bluetooth discovery mode and you should see it.

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

### Compile Unijoysticle

Once you know that BTStack is working as expected, you can try with the Unijoysticle code.

For ESP32 development:

```sh
$ cd src/unijoysticle/firmware/esp32
$ make menuconfig
$ make flash monitor
```

For PC/Linux/Mac development:

```sh
$ cd src/unijoysticle/firmware/esp32/tools
$ make
./unijoysticle
```

Put the gamepad in discovery mode. The gamepad should be recognized and when you press buttons, you should see them on the console.

### Vagrant development

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

[1]: https://www.aliexpress.com/item/MH-ET-LIVE-ESP32-MINI-KIT-WiFi-Bluetooth-Internet-of-Things-development-board-based-ESP8266-Fully/32819107932.html
[2]: https://wiki.wemos.cc/products:d1:d1_mini
[3]: https://github.com/bluekitchen/btstack/blob/master/port/esp32/README.md
