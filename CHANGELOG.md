# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Changed
- Firmware: Updated link to http://retro.moe/unijoysticle2
- Firmware: Using esp-idf v3.2. Commit: cf866f23f2384ebf078fe71a3af1757e53ec6638
  - Enabled options:
    - Component Bluetooth enabled
    - Bluedroid disabled
    - Dual mode BR/EDR + BLE enabled
    - Bluetooth BR/EDR Max connections 4
    - Coredump to UART

## [0.1.0] - 2019-04-15
### Added
- Firmware: v0.1.0
  - Using esp-idf v3.1.3. Commit: cf5dbadf4f25b395887238a7d4d8251c279afa8c
  - Using btstack develop-branch. Commit: 79ca10bb195dedeed22d0e1319a8d33730d36318
- Schematic: Rev B
- Board layout: Rev B
