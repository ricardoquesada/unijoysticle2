# Soldering the Unijoysticle 2 kit

**Warning**: Not valid for Unijoysticle 2+

This is a detailed step-by-step guide, intended mostly to people not familiar with soldering.

## What's needed

### The Unijoysticle 2 Kit

![Unijoysticle 2 kit](https://lh3.googleusercontent.com/pw/ACtC-3c_9eAYPLb34fGdI-sDKXB2cat9iabFaRa3xb-xC-kZJp850PlTJ_WNddJ3n1pSH2-Ud5NVt2aPf0gmAVi_GwlGuHK7aRb2wHLnaIqVmXmvn0T2LMoj9oywW9aW7Ds-eX6Jz_UeZ0V28wxv-AznDZzWig=-no)

Needed components:

- 1 x Unijoysticle 2 PCB
- 1 x ESP32 Mini Kit (and its pins) (ref: B1)
- 2 x 74HC05N ICs
- 2 x 14p DIP sockets for the 7405s (ref: IC1, IC2)
- 1 x standard green LED 3mm (ref: D1)
- 1 x standard red LED 3mm (ref: D2)
- 2 x 1N5819 (or 1N4001) diodes (ref: D3, D4)
- 2 x 150 ohm resistors (ref: R1, R2)
- 1 x Switch Tacticle SPST (ref: SW1)
- 1 x Switch Slide SPDT 200mA (ref: SW2)
- 2 x db9 female connectors (ref: J1, J2)
- 1 x DC Power Barrel Jack (ref: J3)

You can source the components from here:

- Unijoysticle 2 PCB from: [PCBWay][pcbway]
- ESP32 devkit from: [ESP32 Mini Kit][esp32mini]
- Remaining components: [DigiKey list][digikey]

[pcbway]: https://www.pcbway.com/project/shareproject/Unijoysticle_2___Rev_F__Gamepads_for_the_C64_and_other_retro_computers.html
[esp32mini]: https://www.aliexpress.com/store/product/MH-ET-LIVE-ESP32-MINI-KIT-WiFi-Bluetooth-Internet-of-Things-development-board-based-ESP8266-Fully/2348158_32819107932.html?spm=a2g0x.12010108.1000001.12.56543b1cEQVriV
[digikey]: https://www.digikey.com/short/z2fr7v

### Additional tools

- [Soldering iron][soldering_iron]
- [Solder][solder]
- [Wire cutters][wire_cutters]
- [Copper alligator clips][alligator_clips]
- [Plier][plier]
- [Isopropil alcohol 99%][alcohol]
- [Cotton swab][cotton]


[soldering_iron]: https://www.google.com/search?q=hakko+fx888d
[solder]: https://www.google.com/search?q=kester+lead+free+solder
[alligator_clips]: https://www.google.com/search?q=copper+alligator+clips
[wire_cutters]: https://www.google.com/search?q=Wire+Cutters%2C+Precision+Electronic+Flush+Cutter
[plier]: https://www.google.com/search?q=long+nose+plier
[alcohol]: https://www.google.com/search?q=isopropyl+alcohol+99%25
[cotton]: https://www.google.com/search?q=cotton+swap

## Reference Image

Use it as a reference to where place the different components.

![reference](https://lh3.googleusercontent.com/pw/ACtC-3fjffaILCIoGDeBmBi4BBlT8U_RPmmJU5EEVXj8qNPm5SIDm3HT5SJGXACMFbQ1iui82At09GzE927q69N1x-_9KH64N9t-3w4ro81i0ucOQN4ds0Lrg_oeazWqqf9A0irHQuN3TOoSrXDWsXkz8fAdZA=-no)

## Safety

I assume you have soldered before, at least once, and you know the very basic safety guidelines:

- Wear safety goggles when soldering
- Use a fume extractor when soldering, or solder in a ventilated area
- Never touch the tip of the soldering iron

But there are more, [read all of them][safety]

[safety]: https://ehs.stonybrook.edu/programs/laboratory-safety/laboratory-equipment/soldering

## Step 1: Prepare the db9 connectors

Use the plier to remove the screws and the metal shield from the db9 connectors.

![prepare db9 connector](https://lh3.googleusercontent.com/pw/ACtC-3djLMqW73NMEvxsOkJtnaCKe2BozFP8D5n41gyz50vIupxiUab_LxWloSmCwLxq00em2shVGKgCoQNzCqGaB4VDRDsv8lf4xdZC6GzK-hK-op6DJzVp6fPGAO_dHRBFgI2vPvrlTEek1WRSsqEHkKi0hA=-no)

## Step 2: Solder the resistors

It is better to solder first the components with the shortest profile. Start with the resistors.

- Bend the wires as shown below:

![resistors](https://lh3.googleusercontent.com/pw/ACtC-3dU67qBlewhKIyG8X4Tzrssh3vwKcp0QfYAtoW5rPvpsdqQJssl8TBUGpXDmiECk8TLmQXMfINmxD04wz8aKQuvos-I7rGpjK_7wmxbPHLPxwhCy9migJshvgo-lMfPCZZg7DVuighCqZT6HPMdDAOFjw=-no)

- Insert the resistors in positions **R1** and **R2** (see Reference Image)
- Resistors don't have polarity. There is not such a thing as "good" / "bad" orientation.
- Once the resistors are inserted, flip the PCB and "unbent" the wire as shown below:

![unbent_resistors](https://lh3.googleusercontent.com/pw/ACtC-3dOYjdE_fZeRgP-PgIfRWcFVtxp6bzy_n8RflAlW8OsDfJbw9MXNWT_2D-hBoAAVlVOdOQgRt04Eo7xsEilQPwC0H01uKvOxNMVzBM3mXp1OKjB6NrE_7lkVzrEbY5CWP2xswZmQcjbfkuy9hYxKAGrDQ=-no)

- And solder them
- Use wire cutter to cut the "extra" wire. As close as possible to the PCB, but don't cut the solder

![resistor_wire_cutter](https://lh3.googleusercontent.com/pw/ACtC-3cl3Fr5QE8uxhZFTOegcMpPc5o27Tz_LGcKRTpag_lnGq0IrsUO6-z4jZTERgm6v3CHHJ22IALBxAYGBGgSFCv33UNu0OR09I2_zz3UVZLBMdRqRKIDMjhkMomCuw3Kxf-D_9NWulL8ZFT5EQnuM-lYFQ=-no)

## Step 3

TODO: Finish this guide