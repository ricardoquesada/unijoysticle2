# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).
Adheres to the "standard" way to version boards/layouts. E.g: letters instead of numbers.

## [RPi Hat for C64] - 2023-04-03
### New

* RPi Hat for C64. Similar to the A500 but with a few more resistors for the POT buttons
* Ports fits the C64

## [Unijoysticle 2 C64 - Rev C] - 2023-03-12
### New

* Unijoysticle C64: Model to be used in Commodore 64/128
* Supports Pot buttons (2nd and 3rd buttons)
* Supports rumble

## [Unijoysticle 2 A500 - Rev C] - 2022-07-??
### New

* Unijoysticle A500: Model to be used in Amiga 500 / 1200
* Supports Amiga / AtariST mouse

### Added

 * contrib: Unijoysticle2 NeoGeo adapter for Unijoysticle2
 * contrib: Unijoysticle2 for NeoGeo
 * contrib: Unijoysticle2 A500 case

## [Unijoysticle 2+ Rev F] - 2021-10-03

### Added: New model: Unijosyticle 2+!!

  * It is case friendly
  * Doesn't use ESP32 Mini Kit, it is built-in
  * Most of the components are SMD, hand-solder friendly (0805 package)
  * Includes caps to filter hi and low frequencies: fixes noise on C128
  * Consumes tiny bit less of current: from 100mA to 96mA
  * Has extra 7405 to control buttons 2 and 3 on both ports on the Amiga / Atari ST

### Changes from Rev A

  * Uses 0805 with long pads (hand-solder friendly)
  * Uses CH340C instead of CP2102 (hand-solder friendly)
  * USB Micro connector moved a few mm inside the board.
    * Board has "hole" so that the USB Micro has space
  * Board has 4 layers instead of 2.
    * Board can be routed in 2 layers without major probblems,
      but using 4-layers for testing purposes.
  * Cap to filter noise in C128 working Ok
  * Autoboot working Ok
  * LEDs have more or less the same intensity

## [Unijoysticle2+ Rev A] - 2021-06-22

* First attempt of the Unijoysticle2+
  * It is case friendly
  * Doesn't use ESP32 Mini Kit, it is built-in
  * Most of the components are SMD
  * Includes caps to filter hi and low frequencies
  * Schematic seems to be Ok, but layout is not.
* Firmware, including all related files, moved to Bluepad32 repo
* Only things related to the board like schematics and layout are kept in this repo
* Community contributions:
  * C16/Plus4 board, by Eduardo Casino
  * C64 - Rev H board, by Kospec C64

## [Revision F] - 2020-09-17

* Includes Schottky diodes from Rev E.
* Adds mounting hole, for a possible case
* Logo is made as "locked" so that it doesn't get removed after a re-route

## [Revision E] - 2020-02-06

* Revision E is a contribution by Kopsec C64
* It is en Eagle format.
* They layout is slightly different
* Uses Schottky diodes

## [Revision D] - 2019-09-28

* Board: a bit wider than Rev C. Easier to solder.
* Replaces DIP switch with Swith Slide SPDT.
  * Easier to source a 200mA Switch Slide than a 200mA DIP switch.
* Funcional equivalent to Rev C.
* Public release.

## [Revision C] - 2019-09-??

* Board: a bit wider, and taller than Rev B. Easier to solder.
* 7405 are powered from C64. Allows to plug in the Unijoysticle unpowered
   without causing noise in CIAs.
* Possibility to power the Unijoysticle from C64, if power supply is big enough.
* KiCad Project: moved SparkFun.lib inside unijoysticle project.
* Internal version: Not released to public.

## [Revision B] - 2019-04-15

### Added

* Schematic: Rev B.
* Board layout: Rev B.
* Initial public release.
