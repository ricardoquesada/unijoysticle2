# Unijoysticle™ 2 800XL

![uni2_800xl_photo][uni2_800xl_photo]

Unijoysticle 2 800XL is a device that lets you use modern Bluetooth gamepads and mice in retro computers like the Atari 800XL / 600XL (as well as Atari 400, Amiga, and Atari ST). It supports Atari 8-bit 2nd & 3rd fire buttons ([Joy 2B+][atari_joy2bplus]) and Amiga / Atari ST mouse emulation.

Unijoysticle 2 is open source / open hardware. See [license][license] for details.

[uni2_800xl_photo]: https://lh3.googleusercontent.com/pw/AIL4fc9fcgdY3Gka6iSZmyUlBTA1Q9ABujo-9v_4qE85St2GdW-2TBzzLNx-pc25o0rFloL0ghWZDDVW_kGWpQjcXaP-SJf9NWPnNw-2jpc_8tcVKp8gzLH7fxnFd7DBEV1ahWYLy97WvthAy7p193wtZ7uM4w=-no
[atari_joy2bplus]: https://github.com/ascrnet/Joy2Bplus

## Schematic

* [Unijoysticle 2 800XL schematic](../../docs/schematic_unijoysticle2_xl800.pdf)

## Layout

Layout files are in KiCad 7 format in this same folder.

## BOM

| Item | Qty | Reference(s) | Value | LibPart | Footprint | Datasheet |
| ---- | --- | ------------ | ----- | ------- | --------- | --------- |
| 1 | 7 | C1, C2, C4, C9, C11, C12, C13 | .1uF | Device:C_Small | Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder | ~ |
| 2 | 1 | C3 | 10uF | Device:C_Small | Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder | ~ |
| 3 | 3 | C5, C7, C8 | 22uF | Device:C_Small | Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder | ~ |
| 4 | 1 | C6 | 2200uF | Device:C_Polarized_Small | Capacitor_SMD:CP_Elec_10x10 | ~ |
| 5 | 1 | C10 | 1uF | Device:C_Small | Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder | ~ |
| 6 | 1 | D1 | PWR | Device:LED | LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder | ~ |
| 7 | 2 | D2, D3 | 1N5819 | Device:D_Schottky_Small | Diode_SMD:D_SOD-123 | ~ |
| 8 | 1 | D4 | BLUE | Device:LED | LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder | ~ |
| 9 | 1 | D5 | GREEN | Device:LED | LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder | ~ |
| 10 | 1 | D6 | RED | Device:LED | LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder | ~ |
| 11 | 2 | H1, H2 | MountingHole_Pad | Mechanical:MountingHole_Pad | MountingHole:MountingHole_3.2mm_M3_Pad_Via | ~ |
| 12 | 1 | J1 | USB_B_Micro | Connector:USB_B_Micro | Connector_USB:USB_Micro-B_Amphenol_10118194_Horizontal | ~ |
| 13 | 2 | J2, J3 | DE9_Receptacle | Connector:DE9_Receptacle | Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.54mm_EdgePinOffset9.40mm | ~ |
| 14 | 1 | JP1 | SolderJumper_1_Open | Jumper:SolderJumper_2_Open | Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm | ~ |
| 15 | 2 | Q1, Q2 | S8050 | Device:Q_NPN_BEC | Package_TO_SOT_SMD:SOT-23 | ~ |
| 16 | 4 | R1, R10, R11, R14 | 10K | Device:R | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 17 | 5 | R2, R7, R8, R9, R12 | 3.3K | Device:R | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 18 | 2 | R3, R4 | 10K | Device:R_Small | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 19 | 2 | R5, R6 | 1K | Device:R_Small | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 20 | 2 | R13, R15 | 0 | Device:R | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 21 | 4 | R16, R17, R18, R19 | 2K7 | Device:R | Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder | ~ |
| 22 | 1 | SW1 | RESET | Switch:SW_Push | Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS | ~ |
| 23 | 1 | SW2 | BOOT | Switch:SW_Push | Unijoysticle:SW_Push_1P1T_NO_5.1x5.1mm | ~ |
| 24 | 1 | SW3 | MODE | Switch:SW_Push | Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS | ~ |
| 25 | 1 | SW4 | SWAP | Switch:SW_Push | Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS | ~ |
| 26 | 1 | U1 | ESP32-WROOM-32 | RF_Module:ESP32-WROOM-32 | Unijoysticle:ESP32-WROOM-32 | https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf |
| 27 | 1 | U2 | AMS1117-3.3 | Regulator_Linear:AMS1117-3.3 | Package_TO_SOT_SMD:SOT-223-3_TabPin2 | http://www.advanced-monolithic.com/pdf/ds1117.pdf |
| 28 | 1 | U3 | CH340C | Interface_USB:CH340C | Package_SO:SOIC-16_3.9x9.9mm_P1.27mm | https://datasheet.lcsc.com/szlcsc/Jiangsu-Qin-Heng-CH340C_C84681.pdf |
| 29 | 3 | U4, U5, U6 | 74HC05 | 74xx:74LS05 | Package_SO:SOIC-14_3.9x8.7mm_P1.27mm | http://www.ti.com/lit/gpn/sn74LS05 |

## Order info

If you are looking for ready-to-use boards, you can purchase one from here:

<a href="https://www.tindie.com/stores/riq/?ref=offsite_badges&utm_source=sellers_riq&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>


[license]: ../../LICENSE