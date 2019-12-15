# Firmware setup

## Flashing precompiled firmware

If you only want to flash the latest firmware version without downloading the toolchain + sources you should do:

Download latest precompiled firmware from here:

- https://github.com/ricardoquesada/unijoysticle2/releases

And then...

### Command Line

For Command Line tool, download `esptool.py`:

- Source Code: https://github.com/espressif/esptool
- macOS: `brew install esptool`
- Debian: `sudo apt install esptool`
- Windows and other OSs: `pip install esptool`

And:

```sh
# macOS
$ export ESPPORT=/dev/cu.SLAB_USBtoUART
# Linux
$ export ESPPORT=/dev/ttyUSB0
# Windows
$ export ESPPORT=COM??  #??? Try different ones

$ esptool.py --chip esp32 --port ${ESPPORT} --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 bootloader.bin 0x10000 firmware.bin 0x8000 partitions_singleapp.bin
```

### Flash tool

If you are not familiar with command-line tools, you can try with the ESP32 Flash Tool.
A tutorial that explains how to use and from where to download is here:

- [Esp32 flash download tool tutorial](http://iot-bits.com/esp32/esp32-flash-download-tool-tutorial/)

## Compiling + flashing firmware

Development can be done locally or using Vagrant for convenience. It's recommended to read the local instructions once (or the bootstrap.sh script) before using Vagrant.

### Local development

- Download BlueKitchen: https://github.com/bluekitchen/btstack
- Download Unijoysticle 2 code: https://gitlab.com/ricardoquesada/unijoysticle2
- Get a bluetooth gamepad
- For ESP32:
  - Download ESP-IDF: https://github.com/espressif/esp-idf
  - Get an ESP32 module, like [the MH-ET Live][1] which is pin-compatible with [Wemos D1 Mini][2] (used by Unijoysticle v0.4.2 PCB).
- For PC/Linux/Mac (optional, and for development only):
  - Download libusb: https://libusb.info/

### ESP-IDF

From the [CHANGELOG.md][changelog], see what is the latest supported ESP-IDF
version. As of this writing it is `v3.2.2`

```sh
$ cd esp/esp-idf
$ git checkout v3.2.2
$ git submodule update --init
```

### Compile BTstack

From the [CHANGELOG.md][changelog], see what is the latest supported BTStack
version. As of this writing it is `dbb3cbc198393187c63748b8b0ed0a7357c9f190`.

```sh
$ cd src/btstack
$ git checkout dbb3cbc198393187c63748b8b0ed0a7357c9f190
```

[changelog]: https://gitlab.com/ricardoquesada/unijoysticle2/blob/master/CHANGELOG.md

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

Once you know that BTStack is working as expected, you can try with the
Unijoysticle code.

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
