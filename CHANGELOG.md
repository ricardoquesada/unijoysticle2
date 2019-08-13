# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.4-rc0] - 2019-08-12
### Added
- Firmware: Support for Nintendo Wii Remote Motion Plus controller.
- Firmware: Support for "accelerometer mode" in Nitendo Wii Remote.
- Firmware: Support for "vertical mode" in Nintendo Wii Remote.

### Changed
- Firmware: Fix crash when printing "cannot swap joystick"
- Docs: Improved "supported devices".

## [0.3] - 2019-08-05
### Added
- Firmware: Nintendo Wii controller LED's represent the joystick port assigned to.

### Changed
- Firmware: Nintendo Wii controller uses "horizontal" orientation setup.
- Firmware: Nintendo Wii U has Y axis working correctly.

## [0.3-rc0] - 2019-08-03
### Added
- Firmware: Add Nintendo Wii generic support. This includes
  - Wii U Pro controller
  - Wii Remote
  - Possibly other Nitendo Wii controllers

### Changed
- Firmware: Nintendo Wii U Pro support: Works Ok on ESP32.
- Firmware: Bluetooth state machine. Code clean-up. It is easier to mantain.
- Firmware: Using btstack master-branch. Commit: dbb3cbc198393187c63748b8b0ed0a7357c9f190

### Removed
- Firmware: Name discovery disabled for the moment

## [0.3-beta] - 2019-07-27
### Added
- Firmware: Added Wii U Pro controller support.

### Changed
- Firmware: Using esp-idf v3.2.2
- Firmware: Using btstack develop-branch. Commit: a4ea32feba8ca8a16509a75d3d80e8017ca2cf3b

## [0.2.1] - 2019-06-29
### Added
- Board: moved SparkFun.lib inside unijoysticle project
- Firmware: more verbose logs when detecting the type of device
- Firmware: Started Wii U Pro controller support. Not working yet.

### Changed
- Firmware: Gamepad names are fetched correctly.
- Firmware: Using btstack develop-branch. Commit: 32b46fec1df77000b2e383d209074f4c2866ebdf
- Firmware: "apple" parser renamed to "nimbus" parser.

## [0.2.0] - 2019-05-22
### Added
- Docs: User guide

### Changed
- Firmware: Combo-mode:
  - Turn on both LEDs when enabled.
  - When back from combo-mode, restore previously used port
  - Cannot swap ports when in combo mode
- Firmware: Atari ST mouse support
  - Buttons working as expected
  - A bit smoother than v0.1.0 but still not good enough
- Firmware: Updated link to http://retro.moe/unijoysticle2
- Firmware: Using esp-idf v3.2. Commit: 286202caa31b61c2182209f37f8069a0b60fb942
    - Components Bluetooth: enabled
       - Bluedroid: disabled
       - Controller -> Bluetooth controller mode: Bluetooth dual mode
       - Controller -> BR/EDR ACL Max Connections: 4
       - Controller -> BR/EDR Sync Max Connections: 2
    - Components ESP32-specific
       - Coredump to UART
       - Main XTAL frequency: Autodetect
    - Components Wi-Fi
       - Software controls WiFi/Bluetooth coexistence: disabled
    - 
- Firmware: Using btstack develop-branch. Commit: 4ce43359e6190a70dcb8ef079b902c1583c2abe4

## [0.1.0] - 2019-04-15
### Added
- Firmware: v0.1.0
  - Using esp-idf v3.1.3. Commit: cf5dbadf4f25b395887238a7d4d8251c279afa8c
  - Using btstack develop-branch. Commit: 8b22c04ddc425565c8e4002a6d4d26a53426a31f
- Schematic: Rev B
- Board layout: Rev B
