EESchema Schematic File Version 4
LIBS:unijoysticle-cache
EELAYER 26 0
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
L 4xxx_IEEE:4066 U?
U 1 1 5C650471
P 1200 1000
F 0 "U?" H 1200 1416 50  0000 C CNN
F 1 "4066" H 1200 1325 50  0000 C CNN
F 2 "" H 1200 1000 50  0001 C CNN
F 3 "" H 1200 1000 50  0001 C CNN
	1    1200 1000
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP32-WROOM-32D U?
U 1 1 5C657D5C
P 4700 4400
F 0 "U?" H 4700 5978 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 4700 5887 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 4700 2900 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 4400 4450 50  0001 C CNN
	1    4700 4400
	1    0    0    -1  
$EndComp
$Comp
L 4xxx_IEEE:4066 U?
U 2 1 5C658035
P 1200 1650
F 0 "U?" H 1200 2066 50  0000 C CNN
F 1 "4066" H 1200 1975 50  0000 C CNN
F 2 "" H 1200 1650 50  0001 C CNN
F 3 "" H 1200 1650 50  0001 C CNN
	2    1200 1650
	1    0    0    -1  
$EndComp
$Comp
L 4xxx_IEEE:4066 U?
U 3 1 5C6580B1
P 1200 2200
F 0 "U?" H 1200 2616 50  0000 C CNN
F 1 "4066" H 1200 2525 50  0000 C CNN
F 2 "" H 1200 2200 50  0001 C CNN
F 3 "" H 1200 2200 50  0001 C CNN
	3    1200 2200
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB9_Female_MountingHoles J?
U 1 1 5C65A0B0
P 3800 1400
F 0 "J?" H 3980 1403 50  0000 L CNN
F 1 "DB9_Female_MountingHoles" H 3980 1312 50  0000 L CNN
F 2 "" H 3800 1400 50  0001 C CNN
F 3 " ~" H 3800 1400 50  0001 C CNN
	1    3800 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB9_Female_MountingHoles J?
U 1 1 5C65A122
P 5950 1450
F 0 "J?" H 6130 1453 50  0000 L CNN
F 1 "DB9_Female_MountingHoles" H 6130 1362 50  0000 L CNN
F 2 "" H 5950 1450 50  0001 C CNN
F 3 " ~" H 5950 1450 50  0001 C CNN
	1    5950 1450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_MountingPin J?
U 1 1 5C65A2B3
P 6400 3150
F 0 "J?" H 6455 3467 50  0000 C CNN
F 1 "Barrel_Jack_MountingPin" H 6455 3376 50  0000 C CNN
F 2 "" H 6450 3110 50  0001 C CNN
F 3 "~" H 6450 3110 50  0001 C CNN
	1    6400 3150
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D?
U 1 1 5C65A496
P 2650 2550
F 0 "D?" H 2650 2766 50  0000 C CNN
F 1 "1N4001" H 2650 2675 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2650 2375 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2650 2550 50  0001 C CNN
	1    2650 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C65A5CD
P 2600 1850
F 0 "#PWR?" H 2600 1700 50  0001 C CNN
F 1 "+5V" H 2615 2023 50  0000 C CNN
F 2 "" H 2600 1850 50  0001 C CNN
F 3 "" H 2600 1850 50  0001 C CNN
	1    2600 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5C666DF0
P 2550 3300
F 0 "#PWR?" H 2550 3150 50  0001 C CNN
F 1 "+5V" H 2565 3473 50  0000 C CNN
F 2 "" H 2550 3300 50  0001 C CNN
F 3 "" H 2550 3300 50  0001 C CNN
	1    2550 3300
	1    0    0    -1  
$EndComp
$Comp
L 4xxx_IEEE:4066 U?
U 4 1 5C658124
P 1200 2900
F 0 "U?" H 1200 3316 50  0000 C CNN
F 1 "4066" H 1200 3225 50  0000 C CNN
F 2 "" H 1200 2900 50  0001 C CNN
F 3 "" H 1200 2900 50  0001 C CNN
	4    1200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5000 5900 5000
Wire Wire Line
	5300 4700 5900 4700
Wire Wire Line
	5300 4600 5900 4600
Wire Wire Line
	5300 4300 5900 4300
Wire Wire Line
	5300 4200 5900 4200
Text GLabel 5900 5000 2    50   Input ~ 0
J1UP
Text GLabel 5900 4700 2    50   Input ~ 0
J1DOWN
Text GLabel 5900 4600 2    50   Input ~ 0
J1LEFT
Text GLabel 5900 4300 2    50   Input ~ 0
J1RIGHT
Text GLabel 5900 4200 2    50   Input ~ 0
J1FIRE
$EndSCHEMATC
