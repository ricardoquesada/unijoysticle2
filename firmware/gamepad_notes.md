# Notes about certain gamepads

## Nintendo Switch Pro

### Nintendo Pro (original)

BT Addr: DC:68:EB:EF:8B:AB, COD: 0x002508

Device info: Firmware: 3.72, controller type=3
03 48 03 02 DC 68 EB EF 8B AB 01 01

0x6000 (serial number + misc):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

0x6012 (device type):
03 A0 FF FF FF FF FF FF FF 01 FF 00 00 00

0x603D (Factory axis calibration):
BC C5 64 DA 57 7C 15 F6 5F B2 57 73 40 56 62 ED 75 60

0x6086 (stick device param 1):
0F 30 61 96 30 F3 D4 14 54 41 15 54 C7 79 9C 33 36 63

0x6086 (stick device param 2):
0F 30 61 96 30 F3 D4 14 54 41 15 00 00 00 00 00 00 00

0x8010 (user stick calibration):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

### 8BitDo Lite & 8BitDo SN30 Pro

Lite: BT Addr: E4:17:D8:BE:B4:72, COD: 0x002508
SN30: BT Addr: E4:17:D8:D8:D0:74, COD: 0x002508

Firmware: 3.72, controller type=3
Lite: 03 48 03 02 E4 17 D8 BE B4 72 03 01
SN30: 03 48 03 02 E4 17 D8 D8 D0 74 03 01

0x6000 (serial number + misc):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

0x6012 (device type):
03 A0 FF FF FF FF FF FF FF 01 FF 00 00 00

0x603D (Factory axis calibration):
7F B5 5F DF 97 7A 10 66 5F F0 07 80 50 06 5E 61 75 5E

0x6086 (stick device param 1):
0F 30 61 96 30 F3 D4 14 54 41 15 54 C7 79 9C 33 36 63

0x6086 (stick device param 2):
0F 30 61 96 30 F3 D4 14 54 41 15 35 09 09 65 6E 09 00

0x8010 (user stick calibration):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

### Clone (whitelabel)

https://www.ebay.com/itm/Switch-Pro-Controller-Wireless-With-USB-cable-for-Nintendo-Smash/383363616179

BT Addr: 58:A1:9B:63:43:8D, COD: 0x002504
Firmware: 3.72, controller type=3
03 48 03 02 58 A1 9B 63 43 8D 01 02

0x6000 (serial number + misc):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF

0x6012 (device type):
FF FF FF FF FF FF FF FF FF FF FF 00 00 00

0x603D (Factory axis calibration):
7F B5 5F 00 08 80 10 66 5F 00 08 80 50 06 5E 61 75 5E

0x6086 (stick device param 1):
0F 30 61 96 30 F3 D4 14 54 41 15 54 C7 79 9C 33 36 63

0x6098 (stick device param 2):
0F 30 61 96 30 F3 D4 14 54 41 15 00 00 00 00 00 00 00

0x8010 (user stick calibration):
FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF
