# C16/Plus4 board

This board is specifically designed for the TED series of Commodore computers (c16, c116 and Plus/4) and it is based on the work of [Levente Hársfalvi](https://www.commodore.ca/manuals/funet/cbm/documents/projects/interfaces/plus4joy/plus4joy.html)

It uses the same firmware as the C64 version and works exactly the same, except for two particularities:

- Joystick \#1 and \#2 are swapped (default joystick in c16 games is usually \#1)
- The board can be self-powered or USB-powered, there is no barrel jack

## Important

Board **must** be 1mm thick or the mini DIN connectors won't fit!

## Bill Of Materials

- 10 x 110ohm, 1/4W resistors (100ohm is also OK)
- 2 x 150ohm, 1/4W resistors
- 3 x 100nF ceramic capacitors
- 1 x 220uF 16V, low ESR, electrolytic capacitor
- 1 x 3mm red LED
- 1 x 3mm green LED
- 1 x 1n5819 Schottky diode
- 1 x SPST right angle, 6x6x5mm push button
- 2 x 20pin DIP sockets
- 2 x 74HCT240 buffers with inverted outputs
- 2 x [Mini DIN male connectors](https://es.aliexpress.com/item/4001071580837.html)
- 2 x 2x10 PIN double row, straight, female header
- 1 x ESP32 Mini Kit
- 1 x [Unijoysticle2-c16 board](https://www.pcbway.com/project/shareproject/Unijoysticle_2_for_Commodore_TED_series_of_computers__c16__c116_and_Plus_4__1.html)

