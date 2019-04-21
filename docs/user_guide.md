# User Guide

![Unijoysticle 2][https://lh3.googleusercontent.com/5z64MnH33BL75in0eUzcMZeayM6dUNELabYsVOB-fAuXg1LogRnEZN3G132GyiEIxGKzLtu-ZNaZyxh4UwsJbNI9UwP4f19cHUyUsJkge__LU6sLx3pXXtcNG3kAuNhCuoPcRgUDaL4=-no]

## Soldering the kit

![Solering the kit][https://lh3.googleusercontent.com/ZTu0iD57vqErS4Db-EeZyetXIQoKDy9E449kEcDra5ZAmpwThNIXn8jBqcDD87YzG1pip65pEcRpCkp2hKvoVQL1PpANQ766RERK4ecsmgYYdreZuJID4AX9zx7e3el4v3YggfPN4FM=-no]

All components are through-hole. The only components that have polarity are the LEDs and the diode.
See graphic for reference.

Neded components:

- 1 x Unijoysticle 2 PCB
- 1 x ESP32 Mini Kit (and its pins)
- 2 x 74HC05N ICs
- 2 x 14p DIP sockets for the 7405s
- 1 x standard green LED 3mm ~25mA
- 1 x standard red LED 3mm ~25mA
- 2 x 150 ohm resistors
- 1 x tactile button
- 2 x db9 female connectors
- 1 x 1N4001 diode
- 1 x DC Power Barrel Jack

You can source the components from here:

- Unijoysticle 2 PCB from: [PCBWay][3] or [OSHPark][4]
- [ESP32 Mini Kit][5] and some extra [pins][6]
- [Remaining components][7]

## Flashing the firmware

See: [firmware_setup.md][1]

## Power on

The Unijoysticle 2 can be powered either with:

- USB: Connect a USB-micro cable into the ESP32 mini kit module.
  - If powered from a computer, it is great for debugging since you can see the console
- Power Jack Barrel with a 5V+ / ~250mA
  - Self-powered in case you connect it to the C64/C128 datasette port.
  - Polarity: positive polarity (tip=+5v, sleeve=0v)

It is safe to plug both the USB and Jack Barrel at the same time, but that won't
give you any additional benefit.

## Booting

You should see the two LEDS (green and red) blink one for ~1 second.
The Unijoysticle 2 will be ready once both LEDs are off.

## Troubleshooting

### Gamepad cannot connect

This could be due to a lot of things. Assuming that you are using a [supported gamepad][2], try:

- Make sure that the red and green LEDs are off. Meaning that BT is ready.
  Reboot the device and try again.
 
- Reboot the Unijoysticle. Press the Reset button that is placed in the ESP32 Mini Kit
  And try again.

- Press the Reboot + Toggle-Mode buttons at the same time.
  This will reboot the Unijoysticle while also deleting the stored BT keys.
  Any try again.

- Put the gamepad in BT discovery mode. And try again.

If none of the above works, file a bug (see below).

### Both green and red LEDs are always on after booting

This means that the BT stack is not ready yet. It shouldn't take more than one second to be ready.
Try rebooting the device. If they are still on, file a bug (see below).

### Gamepad cannot re-connect

Assuming tha the gamepad connects Ok for the first time, but fails to reconnect then:

- Press the Reboot + Toggle-Mode buttons at the same time.
  This will reboot the Unijoysticle while also deleting the stored BT keys.
  Any try again.

- Put the gamepad in BT discovery mode. And try again.

If none of the above works, file a bug (see below).

## Reporting bugs

[1]: firmware_setup.md
[2]: supported_gamepads.md
[3]: https://oshpark.com/shared_projects/l32mADi8
[4]: https://www.pcbway.com/project/shareproject/Unijoysticle_2.html
[5]: https://www.aliexpress.com/store/product/MH-ET-LIVE-ESP32-MINI-KIT-WiFi-Bluetooth-Internet-of-Things-development-board-based-ESP8266-Fully/2348158_32819107932.html?spm=a2g0x.12010108.1000001.12.56543b1cEQVriV
[6]: https://www.aliexpress.com/item/10PCS-40Pin-1x40P-2-54mm-Male-Breakable-Single-Row-Pin-Header-Strip-Connector-For-Arduino/32973539561.html?spm=2114.search0104.3.9.158d2b70wty222
[7]: https://www.digikey.com/short/pprdhv