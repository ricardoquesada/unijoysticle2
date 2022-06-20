# Unijoysticle™ 2+

![uni2_plus_photo][uni2_plus_photo]

Unijoysticle 2+ is device that lets you use modern gamepads and Mice in retro computers like the Commodore 64.

Unijoysticle 2 is open source / open hardware. See [license][license] for details.

[uni2_plus_photo]: https://lh3.googleusercontent.com/pw/AM-JKLVeTZLBOCy4GmrG5N-WiRIcqoxLdsVXSN-77reS92gn7xxmZy-JuE_XeXgwSSPaUBYa2qaaw5RvZbzlkHdjDxal2p_WkKIm9RnzD6qeqV_u7j_3sRJOkm35EO5JCXFp_EpLvCTHGNEX6ZOtMyOGrzqLQw=-no

## Schematic

* [Unijoysticle 2+ schematic](../../docs/schematic_unijoysticle2plus.pdf)

## Layout

Layout files are in Kicad 5 format in this same folder.

## BOM


| Item | Qty | Reference(s) | Value | LibPart | Footprint | Datasheet |
| ---- | --- | ------------ | ----- | ------- | --------- | --------- |
|1|7|C1, C2, C3, C5, C11, C12, C13|.1uF|Device:C_Small|Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder|~|
|2|1|C4|10uF|Device:C_Small|Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder|~|
|3|3|C6, C8, C9|22uF|Device:C_Small|Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder|~|
|4|1|C7|1000uF|unijoysticle2plus-rescue:CP_Small-Device|Capacitor_SMD:CP_Elec_10x10||
|5|1|C10|1uF|Device:C_Small|Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder|~|
|6|1|D1|BLUE|Device:LED|LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder|~|
|7|1|D2|GREEN|Device:LED|LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder|~|
|8|1|D3|RED|Device:LED|LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder|~|
|9|2|D4, D5|1N5819|Device:D_Schottky_Small|Diode_SMD:D_SOD-123|~|
|10|2|H1, H2|MountingHole_Pad|Mechanical:MountingHole_Pad|MountingHole:MountingHole_3.2mm_M3_Pad_Via|~|
|11|2|J1, J2|DB9_Female|Connector:DB9_Female|Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.54mm_EdgePinOffset9.40mm| ~|
|12|1|J3|USB_B_Micro|Connector:USB_B_Micro|Connector_USB:USB_Micro-B_Amphenol_10118194_Horizontal|~|
|13|2|Q1, Q2|S8050|Device:Q_NPN_BEC|Package_TO_SOT_SMD:SOT-23|~|
|14|1|R1|10k|Device:R|Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder|~|
|15|3|R2, R3, R4|1.5k|Device:R|Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder|~|
|16|2|R5, R6|1k|Device:R_Small|Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder|~|
|17|2|R7, R8|10k|Device:R_Small|Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder|~|
|18|1|SW1|RESET|Switch:SW_Push|Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS|~|
|19|1|SW2|JOY SWAP|Switch:SW_Push|Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS|~|
|20|1|SW3|BOOT|Switch:SW_Push|Unijoysticle:SW_Push_1P1T_NO_5.1x5.1mm|~|
|21|3|U1, U2, U3|74HC05|74xx:74LS05|Package_SO:SOIC-14_3.9x8.7mm_P1.27mm|http://www.ti.com/lit/gpn/sn74LS05|
|22|1|U4|ESP32-WROOM-32E|RF_Module:ESP32-WROOM-32D|RF_Module:ESP32-WROOM-32|https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf|
|23|1|U5|AMS1117-3.3|Regulator_Linear:AMS1117-3.3|Package_TO_SOT_SMD:SOT-223-3_TabPin2|http://www.advanced-monolithic.com/pdf/ds1117.pdf|
|24|1|U6|CH340C|Interface_USB:CH340C|Package_SO:SOIC-16_3.9x9.9mm_P1.27mm|https://datasheet.lcsc.com/szlcsc/Jiangsu-Qin-Heng-CH340C_C84681.pdf|


## Order info

If you are looking for ready-to-use boards, you can purchase one from here:

<a href="https://www.tindie.com/stores/riq/?ref=offsite_badges&utm_source=sellers_riq&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>


[license]: ../../LICENSE