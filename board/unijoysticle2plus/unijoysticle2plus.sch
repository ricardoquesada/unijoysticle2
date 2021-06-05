EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32D U1
U 1 1 5F85DF75
P 5250 2750
F 0 "U1" H 5800 1350 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 5850 1250 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 5250 1250 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 4950 2800 50  0001 C CNN
	1    5250 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F861238
P 5250 4200
F 0 "#PWR0101" H 5250 3950 50  0001 C CNN
F 1 "GND" H 5255 4027 50  0000 C CNN
F 2 "" H 5250 4200 50  0001 C CNN
F 3 "" H 5250 4200 50  0001 C CNN
	1    5250 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4150 5250 4200
$Comp
L Device:R R3
U 1 1 5F862A7E
P 4100 1350
F 0 "R3" H 4170 1396 50  0000 L CNN
F 1 "10k" H 4170 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 4030 1350 50  0001 C CNN
F 3 "~" H 4100 1350 50  0001 C CNN
	1    4100 1350
	1    0    0    -1  
$EndComp
Connection ~ 4100 1550
$Comp
L Device:C C1
U 1 1 5F867E9B
P 4100 1700
F 0 "C1" H 3900 1700 50  0000 L CNN
F 1 "4.7uF" H 3850 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 4138 1550 50  0001 C CNN
F 3 "~" H 4100 1700 50  0001 C CNN
	1    4100 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5F86946E
P 4100 1850
F 0 "#PWR0103" H 4100 1600 50  0001 C CNN
F 1 "GND" H 4105 1677 50  0000 C CNN
F 2 "" H 4100 1850 50  0001 C CNN
F 3 "" H 4100 1850 50  0001 C CNN
	1    4100 1850
	1    0    0    -1  
$EndComp
Text Label 4300 1550 0    50   ~ 0
ESP_EN
$Comp
L power:+3V3 #PWR0104
U 1 1 5F869DFE
P 5250 750
F 0 "#PWR0104" H 5250 600 50  0001 C CNN
F 1 "+3V3" H 5265 923 50  0000 C CNN
F 2 "" H 5250 750 50  0001 C CNN
F 3 "" H 5250 750 50  0001 C CNN
	1    5250 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3350 6650 3350
Wire Wire Line
	5850 3450 6650 3450
Wire Wire Line
	5850 3250 6650 3250
Wire Wire Line
	5850 3150 6650 3150
Wire Wire Line
	5850 3550 6650 3550
Wire Wire Line
	5850 3650 6650 3650
Wire Wire Line
	5850 2850 6650 2850
Wire Wire Line
	5850 2750 6650 2750
Wire Wire Line
	5850 2650 6650 2650
Wire Wire Line
	5850 2550 6650 2550
Wire Wire Line
	5850 2350 6650 2350
Wire Wire Line
	5850 2250 6650 2250
Wire Wire Line
	5850 2150 6650 2150
Wire Wire Line
	5850 2050 6650 2050
Wire Wire Line
	5850 2950 6650 2950
Wire Wire Line
	5850 3050 6650 3050
Wire Wire Line
	5850 2450 6650 2450
$Comp
L Switch:SW_Push SW3
U 1 1 5F878AEA
P 3800 1550
F 0 "SW3" H 3800 1835 50  0000 C CNN
F 1 "SW_Push" H 3800 1744 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_B3U-1000P" H 3800 1750 50  0001 C CNN
F 3 "~" H 3800 1750 50  0001 C CNN
	1    3800 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5F8797E5
P 3600 1600
F 0 "#PWR0105" H 3600 1350 50  0001 C CNN
F 1 "GND" H 3605 1427 50  0000 C CNN
F 2 "" H 3600 1600 50  0001 C CNN
F 3 "" H 3600 1600 50  0001 C CNN
	1    3600 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1550 3600 1600
Text Label 6300 1550 2    50   ~ 0
ESP_BOOT
$Comp
L Connector:DB9_Female J1
U 1 1 5F896D30
P 1400 1650
F 0 "J1" H 1580 1696 50  0000 L CNN
F 1 "DB9_Female" H 1580 1605 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.54mm_EdgePinOffset9.40mm" H 1400 1650 50  0001 C CNN
F 3 " ~" H 1400 1650 50  0001 C CNN
	1    1400 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB9_Female J2
U 1 1 5F897BE0
P 2250 1650
F 0 "J2" H 2168 2342 50  0000 C CNN
F 1 "DB9_Female" H 2168 2251 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-9_Female_Horizontal_P2.77x2.54mm_EdgePinOffset9.40mm" H 2250 1650 50  0001 C CNN
F 3 " ~" H 2250 1650 50  0001 C CNN
	1    2250 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 1250 600  1250
Wire Wire Line
	1100 1350 600  1350
Wire Wire Line
	1100 1450 600  1450
Wire Wire Line
	1100 1650 600  1650
Wire Wire Line
	1100 1550 1050 1550
Wire Wire Line
	1050 550  1050 1550
Wire Wire Line
	1100 1750 1050 1750
Wire Wire Line
	1050 1750 1050 2300
Wire Wire Line
	1100 2050 600  2050
Wire Wire Line
	1100 1850 600  1850
$Comp
L power:GND #PWR0107
U 1 1 5F8BD615
P 1050 2300
F 0 "#PWR0107" H 1050 2050 50  0001 C CNN
F 1 "GND" H 1055 2127 50  0000 C CNN
F 2 "" H 1050 2300 50  0001 C CNN
F 3 "" H 1050 2300 50  0001 C CNN
	1    1050 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1950 600  1950
Wire Wire Line
	2550 1250 3050 1250
Wire Wire Line
	2550 1350 3050 1350
Wire Wire Line
	2550 1450 3050 1450
Wire Wire Line
	2550 1550 2600 1550
Wire Wire Line
	2600 1550 2600 550 
Wire Wire Line
	2550 1650 3050 1650
Wire Wire Line
	2550 1850 3050 1850
Wire Wire Line
	2550 1950 3050 1950
Wire Wire Line
	2550 2050 3050 2050
Wire Wire Line
	2550 1750 2600 1750
Wire Wire Line
	2600 1750 2600 2300
$Comp
L power:GND #PWR0108
U 1 1 5F8CEA9E
P 2600 2300
F 0 "#PWR0108" H 2600 2050 50  0001 C CNN
F 1 "GND" H 2605 2127 50  0000 C CNN
F 2 "" H 2600 2300 50  0001 C CNN
F 3 "" H 2600 2300 50  0001 C CNN
	1    2600 2300
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 1 1 5F8D1D3D
P 1300 4450
F 0 "U2" H 1300 4767 50  0000 C CNN
F 1 "74HC05" H 1300 4676 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 4450 50  0001 C CNN
	1    1300 4450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 2 1 5F8D2691
P 1300 4850
F 0 "U2" H 1300 5167 50  0000 C CNN
F 1 "74HC05" H 1300 5076 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 4850 50  0001 C CNN
	2    1300 4850
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 3 1 5F8D3511
P 1300 5250
F 0 "U2" H 1300 5567 50  0000 C CNN
F 1 "74HC05" H 1300 5476 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 5250 50  0001 C CNN
	3    1300 5250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 4 1 5F8D4333
P 1300 5650
F 0 "U2" H 1300 5967 50  0000 C CNN
F 1 "74HC05" H 1300 5876 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 5650 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 5650 50  0001 C CNN
	4    1300 5650
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 5 1 5F8D4FF9
P 1300 6050
F 0 "U2" H 1300 6367 50  0000 C CNN
F 1 "74HC05" H 1300 6276 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 6050 50  0001 C CNN
	5    1300 6050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 7 1 5F8D5BA9
P 1250 7350
F 0 "U2" H 1480 7396 50  0000 L CNN
F 1 "74HC05" H 1480 7305 50  0000 L CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1250 7350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1250 7350 50  0001 C CNN
	7    1250 7350
	0    -1   -1   0   
$EndComp
$Comp
L 74xx:74LS05 U3
U 1 1 5F8D6C86
P 3000 4450
F 0 "U3" H 3000 4767 50  0000 C CNN
F 1 "74HC05" H 3000 4676 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 4450 50  0001 C CNN
	1    3000 4450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 2 1 5F8D7E33
P 3000 4850
F 0 "U3" H 3000 5167 50  0000 C CNN
F 1 "74HC05" H 3000 5076 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 4850 50  0001 C CNN
	2    3000 4850
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 3 1 5F8D8B46
P 3000 5250
F 0 "U3" H 3000 5567 50  0000 C CNN
F 1 "74HC05" H 3000 5476 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 5250 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 5250 50  0001 C CNN
	3    3000 5250
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 4 1 5F8D9B73
P 3000 5650
F 0 "U3" H 3000 5967 50  0000 C CNN
F 1 "74HC05" H 3000 5876 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 5650 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 5650 50  0001 C CNN
	4    3000 5650
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 5 1 5F8DACA6
P 3000 6050
F 0 "U3" H 3000 6367 50  0000 C CNN
F 1 "74HC05" H 3000 6276 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 6050 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 6050 50  0001 C CNN
	5    3000 6050
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U2
U 6 1 5F8E2CFD
P 1300 6450
F 0 "U2" H 1300 6767 50  0000 C CNN
F 1 "74HC05" H 1300 6676 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 1300 6450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 1300 6450 50  0001 C CNN
	6    1300 6450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 6 1 5F8E3BBE
P 3000 6450
F 0 "U3" H 3000 6767 50  0000 C CNN
F 1 "74HC05" H 3000 6676 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3000 6450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3000 6450 50  0001 C CNN
	6    3000 6450
	1    0    0    -1  
$EndComp
Text Label 500  4450 0    50   ~ 0
GPIO_J1_UP
Wire Wire Line
	1000 4450 500  4450
Wire Wire Line
	1000 4850 500  4850
Wire Wire Line
	1000 5250 500  5250
Wire Wire Line
	1000 5650 500  5650
Wire Wire Line
	1000 6050 500  6050
Wire Wire Line
	1600 4450 2000 4450
Wire Wire Line
	1600 4850 2000 4850
Wire Wire Line
	1600 5250 2000 5250
Wire Wire Line
	1600 5650 2000 5650
Wire Wire Line
	1600 6050 2000 6050
Text Label 1700 4450 0    50   ~ 0
J1_UP
Text Label 500  4850 0    50   ~ 0
GPIO_J1_DOWN
Text Label 500  5250 0    50   ~ 0
GPIO_J1_LEFT
Text Label 500  5650 0    50   ~ 0
GPIO_J1_RIGHT
Text Label 500  6050 0    50   ~ 0
GPIO_J1_FIRE
Text Label 1650 4850 0    50   ~ 0
J1_DOWN
Text Label 2000 5250 2    50   ~ 0
J1_LEFT
Text Label 2000 5650 2    50   ~ 0
J1_RIGHT
Text Label 1650 6050 0    50   ~ 0
J1_FIRE
Text Label 2200 4450 0    50   ~ 0
GPIO_J2_UP
Wire Wire Line
	2700 4450 2200 4450
Wire Wire Line
	2700 4850 2200 4850
Wire Wire Line
	2700 5250 2200 5250
Wire Wire Line
	2700 5650 2200 5650
Wire Wire Line
	2700 6050 2200 6050
Text Label 2200 4850 0    50   ~ 0
GPIO_J2_DOWN
Text Label 2200 5250 0    50   ~ 0
GPIO_J2_LEFT
Text Label 2200 5650 0    50   ~ 0
GPIO_J2_RIGHT
Text Label 2200 6050 0    50   ~ 0
GPIO_J2_FIRE
Wire Wire Line
	3300 4450 3700 4450
Wire Wire Line
	3300 4850 3700 4850
Wire Wire Line
	3300 5250 3700 5250
Wire Wire Line
	3300 5650 3700 5650
Wire Wire Line
	3300 6050 3700 6050
Text Label 3400 4450 0    50   ~ 0
J2_UP
Text Label 3350 4850 0    50   ~ 0
J2_DOWN
Text Label 3700 5250 2    50   ~ 0
J2_LEFT
Text Label 3700 5650 2    50   ~ 0
J2_RIGHT
Text Label 3350 6050 0    50   ~ 0
J2_FIRE
Text Label 600  1250 0    50   ~ 0
J1_UP
Text Label 600  1350 0    50   ~ 0
J1_FIRE
Text Label 600  1450 0    50   ~ 0
J1_DOWN
Text Label 600  1650 0    50   ~ 0
J1_LEFT
Text Label 600  1850 0    50   ~ 0
J1_RIGHT
Text Label 600  2050 0    50   ~ 0
J1_POTY
Text Label 600  1950 0    50   ~ 0
J1_POTX
Text Label 1050 550  3    50   ~ 0
J1_POWER
Text Label 3050 1250 2    50   ~ 0
J2_UP
Text Label 3050 1450 2    50   ~ 0
J2_DOWN
Text Label 3050 1650 2    50   ~ 0
J2_LEFT
Text Label 3050 1850 2    50   ~ 0
J2_RIGHT
Text Label 3050 1950 2    50   ~ 0
J2_POTX
Text Label 3050 2050 2    50   ~ 0
J2_POTY
Text Label 2600 550  3    50   ~ 0
J2_POWER
Text Label 3050 1350 2    50   ~ 0
J2_FIRE
Text Label 6650 2050 2    50   ~ 0
GPIO_J1_LED
Text Label 6650 2250 2    50   ~ 0
GPIO_J2_LED
Text Label 6650 2450 2    50   ~ 0
GPIO_SWITCH_JOY
Text Label 6650 3650 2    50   ~ 0
GPIO_J1_POTX
Text Label 6650 3550 2    50   ~ 0
GPIO_J2_LEFT
Text Label 6650 3450 2    50   ~ 0
GPIO_J2_UP
Text Label 6650 3350 2    50   ~ 0
GPIO_J1_UP
Text Label 6650 2150 2    50   ~ 0
GPIO_J2_FIRE
Text Label 6650 2350 2    50   ~ 0
GPIO_J1_FIRE
Text Label 6650 2550 2    50   ~ 0
GPIO_J1_POTY
Text Label 6650 2650 2    50   ~ 0
GPIO_J2_RIGHT
Text Label 6650 2750 2    50   ~ 0
GPIO_J1_DOWN
Text Label 6650 2850 2    50   ~ 0
GPIO_J1_LEFT
Text Label 6650 3150 2    50   ~ 0
GPIO_J1_RIGHT
Text Label 6650 3250 2    50   ~ 0
GPIO_J2_DOWN
Text Label 6650 2950 2    50   ~ 0
GPIO_J2_POTX
Text Label 6650 3050 2    50   ~ 0
GPIO_J2_POTY
Wire Wire Line
	5850 3750 6300 3750
Wire Wire Line
	5850 3850 6300 3850
Text Label 6300 3750 2    50   ~ 0
GPIO34
Text Label 6300 3850 2    50   ~ 0
GPIO35
Wire Notes Line
	500  3950 3850 3950
Wire Wire Line
	3550 7350 3550 7450
Wire Wire Line
	1750 7350 1750 7450
$Comp
L power:GND #PWR0109
U 1 1 5F883166
P 3550 7450
F 0 "#PWR0109" H 3550 7200 50  0001 C CNN
F 1 "GND" H 3555 7277 50  0000 C CNN
F 2 "" H 3550 7450 50  0001 C CNN
F 3 "" H 3550 7450 50  0001 C CNN
	1    3550 7450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5F883CF9
P 1750 7450
F 0 "#PWR0110" H 1750 7200 50  0001 C CNN
F 1 "GND" H 1755 7277 50  0000 C CNN
F 2 "" H 1750 7450 50  0001 C CNN
F 3 "" H 1750 7450 50  0001 C CNN
	1    1750 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  2900 1400 2900
Wire Wire Line
	1400 2900 1400 3150
Wire Wire Line
	1400 3350 900  3350
Wire Wire Line
	1400 3150 1550 3150
Wire Wire Line
	1550 3150 1550 2950
Connection ~ 1400 3150
Wire Wire Line
	1400 3150 1400 3350
Text Label 900  2900 0    50   ~ 0
J1_POWER
Text Label 900  3350 0    50   ~ 0
J2_POWER
$Comp
L Diode:1N5819 D4
U 1 1 5F8A8493
P 1850 3150
F 0 "D4" H 1850 2933 50  0000 C CNN
F 1 "1N5819" H 1850 3024 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 1850 2975 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 1850 3150 50  0001 C CNN
	1    1850 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 3150 2100 3150
$Comp
L Switch:SW_SPST SW2
U 1 1 5F8C88E4
P 2300 3150
F 0 "SW2" H 2300 3385 50  0000 C CNN
F 1 "SW_SPST" H 2300 3294 50  0000 C CNN
F 2 "Button_Switch_THT:SW_CuK_OS102011MA1QN1_SPDT_Angled" H 2300 3150 50  0001 C CNN
F 3 "~" H 2300 3150 50  0001 C CNN
	1    2300 3150
	1    0    0    -1  
$EndComp
Connection ~ 1550 3150
Wire Wire Line
	1550 3150 1700 3150
Wire Wire Line
	12550 5700 12350 5700
Wire Wire Line
	12350 5700 12350 6000
Wire Wire Line
	12350 6000 12550 6000
Connection ~ 12350 6000
Wire Wire Line
	12350 6000 12350 6300
Wire Wire Line
	12350 6300 12550 6300
Connection ~ 12350 6300
Wire Wire Line
	12350 6300 12350 6400
$Comp
L Device:LED D1
U 1 1 5F96CB69
P 12700 5700
F 0 "D1" H 12693 5917 50  0000 C CNN
F 1 "LED" H 12693 5826 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 12700 5700 50  0001 C CNN
F 3 "~" H 12700 5700 50  0001 C CNN
	1    12700 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5F96DEB5
P 12700 6000
F 0 "D2" H 12693 6217 50  0000 C CNN
F 1 "LED" H 12693 6126 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 12700 6000 50  0001 C CNN
F 3 "~" H 12700 6000 50  0001 C CNN
	1    12700 6000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5F96F5C6
P 12750 6300
F 0 "SW1" H 12750 6585 50  0000 C CNN
F 1 "SW_Push" H 12750 6494 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 12750 6500 50  0001 C CNN
F 3 "~" H 12750 6500 50  0001 C CNN
	1    12750 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	12850 5700 12950 5700
Wire Wire Line
	12850 6000 12950 6000
Wire Wire Line
	12950 6300 13800 6300
$Comp
L Device:R R1
U 1 1 5F98F579
P 13100 5700
F 0 "R1" V 13307 5700 50  0000 C CNN
F 1 "150" V 13216 5700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 13030 5700 50  0001 C CNN
F 3 "~" H 13100 5700 50  0001 C CNN
	1    13100 5700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F9908EC
P 13100 6000
F 0 "R2" V 12893 6000 50  0000 C CNN
F 1 "150" V 12984 6000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 13030 6000 50  0001 C CNN
F 3 "~" H 13100 6000 50  0001 C CNN
	1    13100 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	13250 5700 13800 5700
Wire Wire Line
	13250 6000 13800 6000
Text Label 13800 5700 2    50   ~ 0
GPIO_J1_LED
Text Label 13800 6000 2    50   ~ 0
GPIO_J2_LED
Text Label 13800 6300 2    50   ~ 0
GPIO_SWITCH_JOY
$Comp
L power:GND #PWR0114
U 1 1 5F9AFA6D
P 12350 6400
F 0 "#PWR0114" H 12350 6150 50  0001 C CNN
F 1 "GND" H 12355 6227 50  0000 C CNN
F 2 "" H 12350 6400 50  0001 C CNN
F 3 "" H 12350 6400 50  0001 C CNN
	1    12350 6400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J3
U 1 1 5F9B5A38
P 10550 2050
F 0 "J3" H 10607 2375 50  0000 C CNN
F 1 "Barrel_Jack" H 10607 2284 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 10600 2010 50  0001 C CNN
F 3 "~" H 10600 2010 50  0001 C CNN
	1    10550 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 2150 10950 2150
Wire Wire Line
	10950 2150 10950 2300
$Comp
L power:GND #PWR0115
U 1 1 5F9BB6EE
P 10950 2300
F 0 "#PWR0115" H 10950 2050 50  0001 C CNN
F 1 "GND" H 10955 2127 50  0000 C CNN
F 2 "" H 10950 2300 50  0001 C CNN
F 3 "" H 10950 2300 50  0001 C CNN
	1    10950 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 1950 11050 1950
Wire Wire Line
	2500 3150 2600 3150
Wire Wire Line
	2600 3150 2600 2950
NoConn ~ 7600 1250
Wire Wire Line
	7600 1150 8450 1150
Wire Wire Line
	5850 1650 6300 1650
Wire Wire Line
	5850 1850 6300 1850
Text Label 6300 1650 2    50   ~ 0
ESP_TXD
Text Label 6300 1850 2    50   ~ 0
ESP_RXD
Wire Wire Line
	5850 1950 6300 1950
Text Label 6300 1950 2    50   ~ 0
GPIO04
Wire Wire Line
	7200 1450 7200 1550
Wire Wire Line
	7200 1550 7250 1550
Wire Wire Line
	7300 1550 7300 1450
Wire Wire Line
	7250 1550 7250 1650
Connection ~ 7250 1550
Wire Wire Line
	7250 1550 7300 1550
$Comp
L power:GND #PWR0112
U 1 1 5F9EB2D8
P 7250 1650
F 0 "#PWR0112" H 7250 1400 50  0001 C CNN
F 1 "GND" H 7255 1477 50  0000 C CNN
F 2 "" H 7250 1650 50  0001 C CNN
F 3 "" H 7250 1650 50  0001 C CNN
	1    7250 1650
	1    0    0    -1  
$EndComp
$Comp
L Diode:ESD9B5.0ST5G D6
U 1 1 5FA6217B
P 7850 1550
F 0 "D6" H 7850 1766 50  0000 C CNN
F 1 "LESD5D5.0CT1G" H 7850 1675 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-523" H 7850 1550 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/ESD9B-D.PDF" H 7850 1550 50  0001 C CNN
	1    7850 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7850 1400 7850 850 
Wire Wire Line
	7850 850  7600 850 
$Comp
L Diode:ESD9B5.0ST5G D7
U 1 1 5FB69614
P 8150 1550
F 0 "D7" H 8150 1766 50  0000 C CNN
F 1 "LESD5D5.0CT1G" H 8150 1675 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-523" H 8150 1550 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/ESD9B-D.PDF" H 8150 1550 50  0001 C CNN
	1    8150 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 1050 8150 1050
$Comp
L Diode:ESD9B5.0ST5G D8
U 1 1 5FC7F37F
P 8450 1550
F 0 "D8" H 8450 1766 50  0000 C CNN
F 1 "LESD5D5.0CT1G" H 8450 1675 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-523" H 8450 1550 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/ESD9B-D.PDF" H 8450 1550 50  0001 C CNN
	1    8450 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8150 1400 8150 1050
Connection ~ 8150 1050
Wire Wire Line
	8150 1050 8650 1050
Wire Wire Line
	8450 1400 8450 1150
Connection ~ 8450 1150
Wire Wire Line
	8450 1150 8650 1150
Wire Wire Line
	7850 1700 7850 1800
Wire Wire Line
	8150 1700 8150 1800
Wire Wire Line
	8450 1700 8450 1800
$Comp
L power:GND #PWR0113
U 1 1 5FCD484D
P 7850 1800
F 0 "#PWR0113" H 7850 1550 50  0001 C CNN
F 1 "GND" H 7855 1627 50  0000 C CNN
F 2 "" H 7850 1800 50  0001 C CNN
F 3 "" H 7850 1800 50  0001 C CNN
	1    7850 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5FCD5004
P 8150 1800
F 0 "#PWR0116" H 8150 1550 50  0001 C CNN
F 1 "GND" H 8155 1627 50  0000 C CNN
F 2 "" H 8150 1800 50  0001 C CNN
F 3 "" H 8150 1800 50  0001 C CNN
	1    8150 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5FCD5A37
P 8450 1800
F 0 "#PWR0117" H 8450 1550 50  0001 C CNN
F 1 "GND" H 8455 1627 50  0000 C CNN
F 2 "" H 8450 1800 50  0001 C CNN
F 3 "" H 8450 1800 50  0001 C CNN
	1    8450 1800
	1    0    0    -1  
$EndComp
Text Label 8650 1050 2    50   ~ 0
USBD+
Text Label 8650 1150 2    50   ~ 0
USBD-
Connection ~ 7850 850 
$Comp
L Diode:1N5819 D5
U 1 1 5FD081BA
P 9300 750
F 0 "D5" H 9150 550 50  0000 C CNN
F 1 "1N5819" H 9150 650 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 9300 575 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 9300 750 50  0001 C CNN
	1    9300 750 
	-1   0    0    1   
$EndComp
Wire Wire Line
	7850 850  7850 750 
$Comp
L power:VBUS #PWR0118
U 1 1 5FD77036
P 7850 750
F 0 "#PWR0118" H 7850 600 50  0001 C CNN
F 1 "VBUS" H 7865 923 50  0000 C CNN
F 2 "" H 7850 750 50  0001 C CNN
F 3 "" H 7850 750 50  0001 C CNN
	1    7850 750 
	1    0    0    -1  
$EndComp
Wire Notes Line
	6900 450  6900 5050
Wire Wire Line
	11050 1950 11050 1900
$Comp
L power:+5V #PWR0120
U 1 1 60172313
P 11050 1900
F 0 "#PWR0120" H 11050 1750 50  0001 C CNN
F 1 "+5V" H 11065 2073 50  0000 C CNN
F 2 "" H 11050 1900 50  0001 C CNN
F 3 "" H 11050 1900 50  0001 C CNN
	1    11050 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0121
U 1 1 601BC371
P 2600 2950
F 0 "#PWR0121" H 2600 2800 50  0001 C CNN
F 1 "+5V" H 2615 3123 50  0000 C CNN
F 2 "" H 2600 2950 50  0001 C CNN
F 3 "" H 2600 2950 50  0001 C CNN
	1    2600 2950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U3
U 7 1 5F8E509A
P 3050 7350
F 0 "U3" H 3280 7396 50  0000 L CNN
F 1 "74HC05" H 3280 7305 50  0000 L CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 3050 7350 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 3050 7350 50  0001 C CNN
	7    3050 7350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2550 7350 2550 7250
Wire Wire Line
	750  7350 750  7250
$Comp
L power:VDD #PWR0123
U 1 1 60271912
P 2550 7250
F 0 "#PWR0123" H 2550 7100 50  0001 C CNN
F 1 "VDD" H 2565 7423 50  0000 C CNN
F 2 "" H 2550 7250 50  0001 C CNN
F 3 "" H 2550 7250 50  0001 C CNN
	1    2550 7250
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0124
U 1 1 602727D8
P 750 7250
F 0 "#PWR0124" H 750 7100 50  0001 C CNN
F 1 "VDD" H 765 7423 50  0000 C CNN
F 2 "" H 750 7250 50  0001 C CNN
F 3 "" H 750 7250 50  0001 C CNN
	1    750  7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 950  9700 950 
Wire Wire Line
	9700 950  9700 1050
$Comp
L Device:C_Small C4
U 1 1 608E91F4
P 9700 1150
F 0 "C4" H 9792 1196 50  0000 L CNN
F 1 "22uF" H 9792 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 9700 1150 50  0001 C CNN
F 3 "~" H 9700 1150 50  0001 C CNN
	1    9700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1250 9700 1350
Wire Wire Line
	10650 950  10500 950 
$Comp
L power:GND #PWR0127
U 1 1 60941937
P 10200 1350
F 0 "#PWR0127" H 10200 1100 50  0001 C CNN
F 1 "GND" H 10205 1177 50  0000 C CNN
F 2 "" H 10200 1350 50  0001 C CNN
F 3 "" H 10200 1350 50  0001 C CNN
	1    10200 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 6094209B
P 9700 1350
F 0 "#PWR0128" H 9700 1100 50  0001 C CNN
F 1 "GND" H 9705 1177 50  0000 C CNN
F 2 "" H 9700 1350 50  0001 C CNN
F 3 "" H 9700 1350 50  0001 C CNN
	1    9700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 950  10650 1050
Connection ~ 10650 950 
$Comp
L Device:C_Small C5
U 1 1 6094A6C8
P 10650 1150
F 0 "C5" H 10742 1196 50  0000 L CNN
F 1 "22uF" H 10742 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10650 1150 50  0001 C CNN
F 3 "~" H 10650 1150 50  0001 C CNN
	1    10650 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 1250 10650 1350
$Comp
L power:GND #PWR0129
U 1 1 60953195
P 10650 1350
F 0 "#PWR0129" H 10650 1100 50  0001 C CNN
F 1 "GND" H 10655 1177 50  0000 C CNN
F 2 "" H 10650 1350 50  0001 C CNN
F 3 "" H 10650 1350 50  0001 C CNN
	1    10650 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0130
U 1 1 6096D6B5
P 10650 850
F 0 "#PWR0130" H 10650 700 50  0001 C CNN
F 1 "+3V3" H 10665 1023 50  0000 C CNN
F 2 "" H 10650 850 50  0001 C CNN
F 3 "" H 10650 850 50  0001 C CNN
	1    10650 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0131
U 1 1 6096DE0E
P 9050 750
F 0 "#PWR0131" H 9050 600 50  0001 C CNN
F 1 "+5V" H 9065 923 50  0000 C CNN
F 2 "" H 9050 750 50  0001 C CNN
F 3 "" H 9050 750 50  0001 C CNN
	1    9050 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 4600 10900 4600
Wire Wire Line
	10200 3850 10050 3850
Wire Wire Line
	10200 4400 10050 4400
$Comp
L Device:R R5
U 1 1 60AF2CFC
P 9900 3850
F 0 "R5" V 9693 3850 50  0000 C CNN
F 1 "10k" V 9784 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9830 3850 50  0001 C CNN
F 3 "~" H 9900 3850 50  0001 C CNN
	1    9900 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 60AF3FED
P 9900 4400
F 0 "R6" V 10107 4400 50  0000 C CNN
F 1 "10k" V 10016 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 9830 4400 50  0001 C CNN
F 3 "~" H 9900 4400 50  0001 C CNN
	1    9900 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9750 3850 9550 3850
Wire Wire Line
	9750 4400 9650 4400
Wire Wire Line
	10500 4050 9650 4050
Wire Wire Line
	9650 4050 9650 4400
Connection ~ 9650 4400
Wire Wire Line
	9550 3850 9550 4200
Wire Wire Line
	9550 3850 9250 3850
Connection ~ 9550 3850
Wire Wire Line
	9250 4400 9650 4400
Wire Wire Line
	10500 3650 10850 3650
$Comp
L Connector:USB_B_Micro J5
U 1 1 5F99FD12
P 7300 1050
F 0 "J5" H 7357 1517 50  0000 C CNN
F 1 "USB_B_Micro" H 7357 1426 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 7450 1000 50  0001 C CNN
F 3 "~" H 7450 1000 50  0001 C CNN
	1    7300 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3200 9350 3200
Text Label 9050 3200 0    50   ~ 0
ESP_RXD
Wire Wire Line
	8900 3100 9350 3100
Text Label 9050 3100 0    50   ~ 0
ESP_TXD
Wire Wire Line
	8900 3400 9350 3400
Wire Wire Line
	8900 3000 9350 3000
Text Label 9000 3400 0    50   ~ 0
DTR_PROG
Text Label 9000 3000 0    50   ~ 0
RTS_PROG
Wire Wire Line
	7900 3400 7600 3400
Wire Wire Line
	7900 3500 7600 3500
Text Label 7600 3400 0    50   ~ 0
USBD+
Text Label 7600 3500 0    50   ~ 0
USBD-
Wire Wire Line
	8400 5300 8400 5400
$Comp
L power:GND #PWR0111
U 1 1 60E6428D
P 8400 5400
F 0 "#PWR0111" H 8400 5150 50  0001 C CNN
F 1 "GND" H 8405 5227 50  0000 C CNN
F 2 "" H 8400 5400 50  0001 C CNN
F 3 "" H 8400 5400 50  0001 C CNN
	1    8400 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 60E88C4A
P 7300 2900
F 0 "#PWR0125" H 7300 2650 50  0001 C CNN
F 1 "GND" H 7305 2727 50  0000 C CNN
F 2 "" H 7300 2900 50  0001 C CNN
F 3 "" H 7300 2900 50  0001 C CNN
	1    7300 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 60EF6BA5
P 7750 2700
F 0 "C2" H 7550 2750 50  0000 C CNN
F 1 ".1uF" H 7550 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7750 2700 50  0001 C CNN
F 3 "~" H 7750 2700 50  0001 C CNN
	1    7750 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 60EF76EE
P 7300 2700
F 0 "C3" H 7500 2750 50  0000 C CNN
F 1 "4.7uF" H 7500 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7300 2700 50  0001 C CNN
F 3 "~" H 7300 2700 50  0001 C CNN
	1    7300 2700
	-1   0    0    1   
$EndComp
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMSS8050-H-TP Q1
U 1 1 60BC69F6
P 10400 3850
F 0 "Q1" H 10300 4100 60  0000 L CNN
F 1 "MMSS8050" H 10150 4200 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10600 4050 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 10600 4150 60  0001 L CNN
F 4 "MMSS8050-H-TPMSCT-ND" H 10600 4250 60  0001 L CNN "Digi-Key_PN"
F 5 "MMSS8050-H-TP" H 10600 4350 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10600 4450 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10600 4550 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 10600 4650 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMSS8050-H-TP/MMSS8050-H-TPMSCT-ND/2825945" H 10600 4750 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 25V 1.5A SOT23" H 10600 4850 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 10600 4950 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10600 5050 60  0001 L CNN "Status"
	1    10400 3850
	1    0    0    -1  
$EndComp
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMSS8050-H-TP Q2
U 1 1 60BC761C
P 10400 4400
F 0 "Q2" H 10350 4650 60  0000 L CNN
F 1 "MMSS8050" H 10200 4750 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10600 4600 60  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 10600 4700 60  0001 L CNN
F 4 "MMSS8050-H-TPMSCT-ND" H 10600 4800 60  0001 L CNN "Digi-Key_PN"
F 5 "MMSS8050-H-TP" H 10600 4900 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10600 5000 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10600 5100 60  0001 L CNN "Family"
F 8 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 10600 5200 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/micro-commercial-co/MMSS8050-H-TP/MMSS8050-H-TPMSCT-ND/2825945" H 10600 5300 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 25V 1.5A SOT23" H 10600 5400 60  0001 L CNN "Description"
F 11 "Micro Commercial Co" H 10600 5500 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10600 5600 60  0001 L CNN "Status"
	1    10400 4400
	1    0    0    1   
$EndComp
Wire Wire Line
	9550 4200 10500 4200
Text Label 9250 3850 0    50   ~ 0
DTR_PROG
Text Label 9250 4400 0    50   ~ 0
RTS_PROG
Text Label 10550 4600 0    50   ~ 0
ESP_BOOT
Text Label 10600 3650 0    50   ~ 0
ESP_EN
Wire Wire Line
	5850 1550 6300 1550
$Comp
L Mechanical:MountingHole H2
U 1 1 60CC66D4
P 5950 7100
F 0 "H2" H 6050 7146 50  0000 L CNN
F 1 "MountingHole" H 6050 7055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 5950 7100 50  0001 C CNN
F 3 "~" H 5950 7100 50  0001 C CNN
	1    5950 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 60CC7928
P 5950 7300
F 0 "H3" H 6050 7346 50  0000 L CNN
F 1 "MountingHole" H 6050 7255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 5950 7300 50  0001 C CNN
F 3 "~" H 5950 7300 50  0001 C CNN
	1    5950 7300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 60CC8B56
P 5950 6900
F 0 "H1" H 6050 6946 50  0000 L CNN
F 1 "MountingHole" H 6050 6855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 5950 6900 50  0001 C CNN
F 3 "~" H 5950 6900 50  0001 C CNN
	1    5950 6900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 60CC9CFE
P 5950 7500
F 0 "H4" H 6050 7546 50  0000 L CNN
F 1 "MountingHole" H 6050 7455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 5950 7500 50  0001 C CNN
F 3 "~" H 5950 7500 50  0001 C CNN
	1    5950 7500
	1    0    0    -1  
$EndComp
$Comp
L Interface_USB:CP2102N-A01-GQFN28 U6
U 1 1 60BB8FDE
P 8400 4000
F 0 "U6" H 8600 2600 50  0000 C CNN
F 1 "CP2102N-A01-GQFN28" H 9000 2700 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-28-1EP_5x5mm_P0.5mm_EP3.35x3.35mm" H 8850 2800 50  0001 L CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/cp2102n-datasheet.pdf" H 8450 3250 50  0001 C CNN
	1    8400 4000
	1    0    0    -1  
$EndComp
NoConn ~ 8900 3900
NoConn ~ 8900 3800
$Comp
L power:VBUS #PWR0106
U 1 1 60D372FF
P 7600 3300
F 0 "#PWR0106" H 7600 3150 50  0001 C CNN
F 1 "VBUS" H 7615 3473 50  0000 C CNN
F 2 "" H 7600 3300 50  0001 C CNN
F 3 "" H 7600 3300 50  0001 C CNN
	1    7600 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3300 7900 3300
$Comp
L Regulator_Linear:AMS1117-3.3 U4
U 1 1 60DA00BF
P 10200 950
F 0 "U4" H 10200 1192 50  0000 C CNN
F 1 "AMS1117-3.3" H 10200 1101 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 10200 1150 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 10300 700 50  0001 C CNN
	1    10200 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1250 10200 1350
Wire Wire Line
	10650 850  10650 950 
Wire Wire Line
	9700 950  9500 950 
Wire Wire Line
	9500 950  9500 750 
Wire Wire Line
	9500 750  9450 750 
Connection ~ 9700 950 
Wire Wire Line
	9450 950  9500 950 
Connection ~ 9500 950 
$Comp
L Diode:1N5819 D3
U 1 1 60EBEADC
P 9300 950
F 0 "D3" H 9300 1050 50  0000 C CNN
F 1 "1N5819" H 9300 1150 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 9300 775 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 9300 950 50  0001 C CNN
	1    9300 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	9150 750  9050 750 
Wire Wire Line
	9150 950  8900 950 
$Comp
L power:VBUS #PWR0119
U 1 1 60EEF96B
P 8900 950
F 0 "#PWR0119" H 8900 800 50  0001 C CNN
F 1 "VBUS" H 8915 1123 50  0000 C CNN
F 2 "" H 8900 950 50  0001 C CNN
F 3 "" H 8900 950 50  0001 C CNN
	1    8900 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2700 8400 2550
Wire Wire Line
	7300 2550 7300 2450
$Comp
L power:+3V3 #PWR0122
U 1 1 60FFCD54
P 7300 2450
F 0 "#PWR0122" H 7300 2300 50  0001 C CNN
F 1 "+3V3" H 7315 2623 50  0000 C CNN
F 2 "" H 7300 2450 50  0001 C CNN
F 3 "" H 7300 2450 50  0001 C CNN
	1    7300 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2550 7750 2550
Wire Wire Line
	7300 2600 7300 2550
Connection ~ 7300 2550
Wire Wire Line
	7750 2600 7750 2550
Connection ~ 7750 2550
Wire Wire Line
	7750 2550 8300 2550
Wire Wire Line
	7750 2800 7750 2900
Wire Wire Line
	7750 2900 7300 2900
Wire Wire Line
	7300 2900 7300 2800
Connection ~ 7300 2900
Wire Wire Line
	8300 2700 8300 2550
Connection ~ 8300 2550
Wire Wire Line
	8300 2550 8400 2550
$Comp
L power:+3V3 #PWR0102
U 1 1 5F86633D
P 4100 1150
F 0 "#PWR0102" H 4100 1000 50  0001 C CNN
F 1 "+3V3" H 4200 1150 50  0000 C CNN
F 2 "" H 4100 1150 50  0001 C CNN
F 3 "" H 4100 1150 50  0001 C CNN
	1    4100 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1550 4100 1500
Wire Wire Line
	4100 1200 4100 1150
Wire Wire Line
	4650 1750 4300 1750
Wire Wire Line
	4650 1850 4300 1850
Text Label 4300 1750 0    50   ~ 0
GPIO36
Text Label 4300 1850 0    50   ~ 0
GPIO39
Wire Wire Line
	4000 1550 4100 1550
Wire Wire Line
	4100 1550 4650 1550
$Comp
L Connector:Conn_01x05_Male J4
U 1 1 6166461E
P 5900 6300
F 0 "J4" H 6008 6681 50  0000 C CNN
F 1 "Conn_01x05_Male" H 6008 6590 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 5900 6300 50  0001 C CNN
F 3 "~" H 5900 6300 50  0001 C CNN
	1    5900 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 6100 6500 6100
Wire Wire Line
	6100 6200 6500 6200
Wire Wire Line
	6100 6300 6500 6300
Wire Wire Line
	6100 6400 6500 6400
Wire Wire Line
	6100 6500 6500 6500
Text Label 6250 6400 0    50   ~ 0
GPIO36
Text Label 6250 6500 0    50   ~ 0
GPIO39
Text Label 6250 6100 0    50   ~ 0
GPIO04
Text Label 6250 6200 0    50   ~ 0
GPIO34
Text Label 6250 6300 0    50   ~ 0
GPIO35
Wire Wire Line
	500  6450 1000 6450
Wire Wire Line
	1600 6450 2000 6450
Wire Wire Line
	2200 6450 2700 6450
Wire Wire Line
	3300 6450 3700 6450
Text Label 500  6450 0    50   ~ 0
GPIO_J1_POTX
Text Label 2200 6450 0    50   ~ 0
GPIO_J1_POTY
Text Label 1650 6450 0    50   ~ 0
J1_POTX
Text Label 3350 6450 0    50   ~ 0
J1_POTY
$Comp
L Device:C_Small C7
U 1 1 61942ED6
P 6000 1050
F 0 "C7" H 5850 1000 50  0000 C CNN
F 1 "10uF" H 5800 1100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 6000 1050 50  0001 C CNN
F 3 "~" H 6000 1050 50  0001 C CNN
	1    6000 1050
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 6194D076
P 5600 1050
F 0 "C6" H 5400 1100 50  0000 C CNN
F 1 ".1uF" H 5400 1000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 5600 1050 50  0001 C CNN
F 3 "~" H 5600 1050 50  0001 C CNN
	1    5600 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 750  5250 900 
Wire Wire Line
	5250 900  5600 900 
Connection ~ 5250 900 
Wire Wire Line
	5250 900  5250 1350
Connection ~ 5600 900 
Wire Wire Line
	5600 900  6000 900 
$Comp
L OLIMEX_Power:GND #PWR0126
U 1 1 61A07917
P 6000 1200
F 0 "#PWR0126" H 6000 950 50  0001 C CNN
F 1 "GND" H 6005 1027 50  0000 C CNN
F 2 "" H 6000 1200 60  0000 C CNN
F 3 "" H 6000 1200 60  0000 C CNN
	1    6000 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 950  5600 900 
Wire Wire Line
	6000 950  6000 900 
Wire Wire Line
	6000 1150 6000 1200
Wire Wire Line
	5600 1150 6000 1150
Connection ~ 6000 1150
$Comp
L power:VDD #PWR0132
U 1 1 61B8BF9F
P 1550 2950
F 0 "#PWR0132" H 1550 2800 50  0001 C CNN
F 1 "VDD" H 1565 3123 50  0000 C CNN
F 2 "" H 1550 2950 50  0001 C CNN
F 3 "" H 1550 2950 50  0001 C CNN
	1    1550 2950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U5
U 1 1 61D2A05A
P 4700 6000
F 0 "U5" H 4700 6317 50  0000 C CNN
F 1 "74LS05" H 4700 6226 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4700 6000 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 4700 6000 50  0001 C CNN
	1    4700 6000
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U5
U 2 1 61D2B419
P 4700 6450
F 0 "U5" H 4700 6767 50  0000 C CNN
F 1 "74LS05" H 4700 6676 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4700 6450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 4700 6450 50  0001 C CNN
	2    4700 6450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74LS05 U5
U 7 1 61D2CBB9
P 4700 7400
F 0 "U5" V 5067 7400 50  0000 C CNN
F 1 "74LS05" V 4976 7400 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4700 7400 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS05" H 4700 7400 50  0001 C CNN
	7    4700 7400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 7400 4200 7300
Wire Wire Line
	5200 7400 5200 7450
$Comp
L power:VDD #PWR0133
U 1 1 61D6DE91
P 4200 7300
F 0 "#PWR0133" H 4200 7150 50  0001 C CNN
F 1 "VDD" H 4215 7473 50  0000 C CNN
F 2 "" H 4200 7300 50  0001 C CNN
F 3 "" H 4200 7300 50  0001 C CNN
	1    4200 7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0134
U 1 1 61D6E82B
P 5200 7450
F 0 "#PWR0134" H 5200 7200 50  0001 C CNN
F 1 "GND" H 5205 7277 50  0000 C CNN
F 2 "" H 5200 7450 50  0001 C CNN
F 3 "" H 5200 7450 50  0001 C CNN
	1    5200 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6000 3900 6000
Wire Wire Line
	5000 6000 5300 6000
Wire Wire Line
	5000 6450 5300 6450
Text Label 5000 6000 0    50   ~ 0
J2_POTX
Text Label 5000 6450 0    50   ~ 0
J2_POTY
Text Label 3900 6000 0    50   ~ 0
GPIO_J2_POTX
Text Label 3900 6450 0    50   ~ 0
GPIO_J2_POTY
Wire Wire Line
	3900 6450 4400 6450
Wire Notes Line
	3850 3950 3850 5450
Wire Notes Line
	3850 5450 5600 5450
Wire Notes Line
	5600 5450 5600 7800
Wire Notes Line
	3350 450  3350 3950
$EndSCHEMATC
