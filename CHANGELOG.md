# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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
  - Enabled options:
    - Bluetooth enabled
       - Controller -> Bluedroid disabled
       - Controller -> Dual mode BR/EDR + BLE enabled
       - Controller -> Bluetooth BR/EDR Max connections 4
    - ESP32-specific -> Coredump to UART
- Firmware: Using btstack develop-branch. Commit: 4ce43359e6190a70dcb8ef079b902c1583c2abe4

## [0.1.0] - 2019-04-15
### Added
- Firmware: v0.1.0
  - Using esp-idf v3.1.3. Commit: cf5dbadf4f25b395887238a7d4d8251c279afa8c
  - Using btstack develop-branch. Commit: 8b22c04ddc425565c8e4002a6d4d26a53426a31f
- Schematic: Rev B
- Board layout: Rev B
