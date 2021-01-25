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
L dk_Embedded-Microcontrollers:ATTINY85-20PU U?
U 1 1 600EA4F5
P 2500 5725
AR Path="/5FFDBE64/600EA4F5" Ref="U?"  Part="1" 
AR Path="/6008A670/600EA4F5" Ref="U?"  Part="1" 
AR Path="/600EA4F5" Ref="U1"  Part="1" 
F 0 "U1" H 2728 5728 60  0000 L CNN
F 1 "ATTINY85-20PU" H 2728 5622 60  0000 L CNN
F 2 "digikey-footprints:DIP-8_W7.62mm" H 2700 5925 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en589894" H 2700 6025 60  0001 L CNN
F 4 "ATTINY85-20PU-ND" H 2700 6125 60  0001 L CNN "Digi-Key_PN"
F 5 "ATTINY85-20PU" H 2700 6225 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 2700 6325 60  0001 L CNN "Category"
F 7 "Embedded - Microcontrollers" H 2700 6425 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en589894" H 2700 6525 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/ATTINY85-20PU/ATTINY85-20PU-ND/735469" H 2700 6625 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MCU 8BIT 8KB FLASH 8DIP" H 2700 6725 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 2700 6825 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2700 6925 60  0001 L CNN "Status"
	1    2500 5725
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 600EA4FB
P 2500 4325
AR Path="/5FFDBE64/600EA4FB" Ref="J?"  Part="1" 
AR Path="/6008A670/600EA4FB" Ref="J?"  Part="1" 
AR Path="/600EA4FB" Ref="J1"  Part="1" 
F 0 "J1" H 2550 4642 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 2550 4551 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 2500 4325 50  0001 C CNN
F 3 "~" H 2500 4325 50  0001 C CNN
	1    2500 4325
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4225 1800 4225
Wire Wire Line
	2800 4225 3300 4225
Wire Wire Line
	2300 4325 1800 4325
Wire Wire Line
	2300 4425 1800 4425
Wire Wire Line
	2800 4325 3300 4325
Wire Wire Line
	2800 4425 3300 4425
Text Label 1800 4225 0    50   ~ 0
MISO_DATA
Text Label 1800 4325 0    50   ~ 0
SCK
Text Label 1800 4425 0    50   ~ 0
RST
Text Label 3300 4225 0    50   ~ 0
VCC
Text Label 3300 4325 0    50   ~ 0
MOSI_SDA
Text Label 3300 4425 0    50   ~ 0
GND
Wire Wire Line
	2600 5325 2600 5125
Wire Wire Line
	2600 6225 2600 6325
$Comp
L Device:C C?
U 1 1 600EA50F
P 3200 5275
AR Path="/5FFDBE64/600EA50F" Ref="C?"  Part="1" 
AR Path="/6008A670/600EA50F" Ref="C?"  Part="1" 
AR Path="/600EA50F" Ref="C1"  Part="1" 
F 0 "C1" H 3315 5321 50  0000 L CNN
F 1 "0.1uF" H 3315 5230 50  0000 L CNN
F 2 "Capacitor_SMD:C_1812_4532Metric_Pad1.57x3.40mm_HandSolder" H 3238 5125 50  0001 C CNN
F 3 "~" H 3200 5275 50  0001 C CNN
	1    3200 5275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 5125 2900 5125
Wire Wire Line
	2900 5125 2900 4975
Connection ~ 2900 5125
Wire Wire Line
	2900 5125 3200 5125
Wire Wire Line
	3200 5425 3200 6325
Wire Wire Line
	2600 6325 2900 6325
Wire Wire Line
	2900 6325 2900 6525
Connection ~ 2900 6325
Wire Wire Line
	2900 6325 3200 6325
Text Label 2900 4975 0    50   ~ 0
VCC
Text Label 2900 6525 0    50   ~ 0
GND
Text Label 1300 5525 0    50   ~ 0
MOSI_SDA
Text Label 1300 5625 0    50   ~ 0
MISO_DATA
Text Label 1300 5725 0    50   ~ 0
SCK
$Comp
L Device:R R?
U 1 1 600EA523
P 1800 6225
AR Path="/5FFDBE64/600EA523" Ref="R?"  Part="1" 
AR Path="/6008A670/600EA523" Ref="R?"  Part="1" 
AR Path="/600EA523" Ref="R1"  Part="1" 
F 0 "R1" H 1870 6271 50  0000 L CNN
F 1 "10K" H 1870 6180 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 1730 6225 50  0001 C CNN
F 3 "~" H 1800 6225 50  0001 C CNN
	1    1800 6225
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 6025 1800 6025
Wire Wire Line
	1800 6025 1800 6075
Wire Wire Line
	1800 6025 1300 6025
Connection ~ 1800 6025
Wire Wire Line
	1800 6375 2100 6375
Text Label 2100 6375 0    50   ~ 0
VCC
Text Label 1300 6025 0    50   ~ 0
RST
Wire Wire Line
	2300 5825 1300 5825
Wire Wire Line
	2300 5925 1300 5925
Text Label 1300 5825 0    50   ~ 0
SCL1
Text Label 1300 5925 0    50   ~ 0
SDA1
Wire Wire Line
	2300 5725 1300 5725
Wire Wire Line
	2300 5625 1300 5625
Wire Wire Line
	2300 5525 1300 5525
$Comp
L power:GND #PWR?
U 1 1 600EA537
P 1650 7075
AR Path="/5FFDBE64/600EA537" Ref="#PWR?"  Part="1" 
AR Path="/6008A670/600EA537" Ref="#PWR?"  Part="1" 
AR Path="/600EA537" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1650 6825 50  0001 C CNN
F 1 "GND" H 1655 6902 50  0000 C CNN
F 2 "" H 1650 7075 50  0001 C CNN
F 3 "" H 1650 7075 50  0001 C CNN
	1    1650 7075
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 7075 1650 6825
Text Label 1650 6825 0    50   ~ 0
GND
$Comp
L power:+5V #PWR?
U 1 1 600EA53F
P 2100 6825
AR Path="/5FFDBE64/600EA53F" Ref="#PWR?"  Part="1" 
AR Path="/6008A670/600EA53F" Ref="#PWR?"  Part="1" 
AR Path="/600EA53F" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 2100 6675 50  0001 C CNN
F 1 "+5V" H 2115 6998 50  0000 C CNN
F 2 "" H 2100 6825 50  0001 C CNN
F 3 "" H 2100 6825 50  0001 C CNN
	1    2100 6825
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 6825 2100 7075
Text Label 2100 7075 0    50   ~ 0
VCC
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 600EA547
P 2750 6875
AR Path="/5FFDBE64/600EA547" Ref="J?"  Part="1" 
AR Path="/6008A670/600EA547" Ref="J?"  Part="1" 
AR Path="/600EA547" Ref="J2"  Part="1" 
F 0 "J2" H 2858 7056 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2858 6965 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2750 6875 50  0001 C CNN
F 3 "~" H 2750 6875 50  0001 C CNN
	1    2750 6875
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 6875 3300 6875
Wire Wire Line
	2950 6975 3300 6975
Text Label 3300 6875 0    50   ~ 0
VCC
Text Label 3300 6975 0    50   ~ 0
GND
$Comp
L power:PWR_FLAG #FLG?
U 1 1 600EA551
P 2650 7375
AR Path="/5FFDBE64/600EA551" Ref="#FLG?"  Part="1" 
AR Path="/6008A670/600EA551" Ref="#FLG?"  Part="1" 
AR Path="/600EA551" Ref="#FLG01"  Part="1" 
F 0 "#FLG01" H 2650 7450 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 7548 50  0000 C CNN
F 2 "" H 2650 7375 50  0001 C CNN
F 3 "~" H 2650 7375 50  0001 C CNN
	1    2650 7375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 7375 3000 7375
Text Label 3000 7375 0    50   ~ 0
VCC
$Comp
L power:PWR_FLAG #FLG?
U 1 1 600EA559
P 2650 7625
AR Path="/5FFDBE64/600EA559" Ref="#FLG?"  Part="1" 
AR Path="/6008A670/600EA559" Ref="#FLG?"  Part="1" 
AR Path="/600EA559" Ref="#FLG02"  Part="1" 
F 0 "#FLG02" H 2650 7700 50  0001 C CNN
F 1 "PWR_FLAG" H 2650 7798 50  0000 C CNN
F 2 "" H 2650 7625 50  0001 C CNN
F 3 "~" H 2650 7625 50  0001 C CNN
	1    2650 7625
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 7625 3000 7625
Text Label 3000 7625 0    50   ~ 0
GND
Text Notes 950  4625 0    50   ~ 0
Implements a I2C interface to the master system.
Text Notes 650  4725 0    50   ~ 0
Drives shift registers via SPI like protocol using SPI hardware (or software transfer)
Text Notes 800  4825 0    50   ~ 0
ISP used for programming, shares pins with master system I2C
$Comp
L Analog_ADC:MAX11616 U2
U 1 1 600EB4BF
P 4875 2900
F 0 "U2" H 4875 3781 50  0000 C CNN
F 1 "MAX11616" H 4875 3690 50  0000 C CNN
F 2 "Package_SO:QSOP-16_3.9x4.9mm_P0.635mm" H 5325 2250 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX11612-MAX11617.pdf" H 4975 3700 50  0001 C CNN
	1    4875 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 3000 5675 3000
Wire Wire Line
	4875 2200 5150 2200
Wire Wire Line
	5150 2200 5150 2050
Wire Wire Line
	4875 3700 5050 3700
Wire Wire Line
	5050 3700 5050 3875
Text Label 5050 3875 0    50   ~ 0
GND
Text Label 5150 2050 0    50   ~ 0
VCC
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 600F2456
P 6600 1575
F 0 "J3" H 6518 1250 50  0000 C CNN
F 1 "Conn_01x03" H 6518 1341 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 6600 1575 50  0001 C CNN
F 3 "~" H 6600 1575 50  0001 C CNN
	1    6600 1575
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Network12 RN1
U 1 1 600F5C54
P 4650 1400
F 0 "RN1" V 3833 1400 50  0000 C CNN
F 1 "10K" V 3924 1400 50  0000 C CNN
F 2 "2021-01-25_15-47-38:4814P-2-103LF" V 5325 1400 50  0001 C CNN
F 3 "http://www.vishay.com/docs/31509/csc.pdf" H 4650 1400 50  0001 C CNN
	1    4650 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 800  5200 800 
Text Label 5200 800  0    50   ~ 0
VCC
Wire Wire Line
	6800 1475 7150 1475
Wire Wire Line
	7150 1575 6800 1575
Wire Wire Line
	6800 1675 7150 1675
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 60100AC4
P 6600 2125
F 0 "J4" H 6518 1800 50  0000 C CNN
F 1 "Conn_01x03" H 6518 1891 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 6600 2125 50  0001 C CNN
F 3 "~" H 6600 2125 50  0001 C CNN
	1    6600 2125
	-1   0    0    1   
$EndComp
Wire Wire Line
	6800 2025 7150 2025
Wire Wire Line
	7150 2125 6800 2125
Wire Wire Line
	6800 2225 7150 2225
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 60101FC0
P 6600 2675
F 0 "J5" H 6518 2350 50  0000 C CNN
F 1 "Conn_01x03" H 6518 2441 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 6600 2675 50  0001 C CNN
F 3 "~" H 6600 2675 50  0001 C CNN
	1    6600 2675
	-1   0    0    1   
$EndComp
Wire Wire Line
	6800 2575 7150 2575
Wire Wire Line
	7150 2675 6800 2675
Wire Wire Line
	6800 2775 7150 2775
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 6010216D
P 6600 3225
F 0 "J6" H 6518 2900 50  0000 C CNN
F 1 "Conn_01x03" H 6518 2991 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 6600 3225 50  0001 C CNN
F 3 "~" H 6600 3225 50  0001 C CNN
	1    6600 3225
	-1   0    0    1   
$EndComp
Wire Wire Line
	6800 3125 7150 3125
Wire Wire Line
	7150 3225 6800 3225
Wire Wire Line
	6800 3325 7150 3325
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 60104034
P 7800 1575
F 0 "J7" H 7718 1250 50  0000 C CNN
F 1 "Conn_01x03" H 7718 1341 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 7800 1575 50  0001 C CNN
F 3 "~" H 7800 1575 50  0001 C CNN
	1    7800 1575
	-1   0    0    1   
$EndComp
Wire Wire Line
	8000 1475 8350 1475
Wire Wire Line
	8350 1575 8000 1575
Wire Wire Line
	8000 1675 8350 1675
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 60104211
P 7800 2125
F 0 "J8" H 7718 1800 50  0000 C CNN
F 1 "Conn_01x03" H 7718 1891 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 7800 2125 50  0001 C CNN
F 3 "~" H 7800 2125 50  0001 C CNN
	1    7800 2125
	-1   0    0    1   
$EndComp
Wire Wire Line
	8000 2025 8350 2025
Wire Wire Line
	8350 2125 8000 2125
Wire Wire Line
	8000 2225 8350 2225
$Comp
L Connector_Generic:Conn_01x03 J9
U 1 1 6010421E
P 7800 2675
F 0 "J9" H 7718 2350 50  0000 C CNN
F 1 "Conn_01x03" H 7718 2441 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 7800 2675 50  0001 C CNN
F 3 "~" H 7800 2675 50  0001 C CNN
	1    7800 2675
	-1   0    0    1   
$EndComp
Wire Wire Line
	8000 2575 8350 2575
Wire Wire Line
	8350 2675 8000 2675
Wire Wire Line
	8000 2775 8350 2775
$Comp
L Connector_Generic:Conn_01x03 J10
U 1 1 6010422B
P 7800 3225
F 0 "J10" H 7718 2900 50  0000 C CNN
F 1 "Conn_01x03" H 7718 2991 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 7800 3225 50  0001 C CNN
F 3 "~" H 7800 3225 50  0001 C CNN
	1    7800 3225
	-1   0    0    1   
$EndComp
Wire Wire Line
	8000 3125 8350 3125
Wire Wire Line
	8350 3225 8000 3225
Wire Wire Line
	8000 3325 8350 3325
$Comp
L Connector_Generic:Conn_01x03 J11
U 1 1 60109BA0
P 8850 1600
F 0 "J11" H 8768 1275 50  0000 C CNN
F 1 "Conn_01x03" H 8768 1366 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 8850 1600 50  0001 C CNN
F 3 "~" H 8850 1600 50  0001 C CNN
	1    8850 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 1500 9400 1500
Wire Wire Line
	9400 1600 9050 1600
Wire Wire Line
	9050 1700 9400 1700
$Comp
L Connector_Generic:Conn_01x03 J12
U 1 1 60109DDD
P 8850 2150
F 0 "J12" H 8768 1825 50  0000 C CNN
F 1 "Conn_01x03" H 8768 1916 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 8850 2150 50  0001 C CNN
F 3 "~" H 8850 2150 50  0001 C CNN
	1    8850 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 2050 9400 2050
Wire Wire Line
	9400 2150 9050 2150
Wire Wire Line
	9050 2250 9400 2250
$Comp
L Connector_Generic:Conn_01x03 J13
U 1 1 60109DEA
P 8850 2700
F 0 "J13" H 8768 2375 50  0000 C CNN
F 1 "Conn_01x03" H 8768 2466 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 8850 2700 50  0001 C CNN
F 3 "~" H 8850 2700 50  0001 C CNN
	1    8850 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9050 2600 9400 2600
Wire Wire Line
	9400 2700 9050 2700
Wire Wire Line
	9050 2800 9400 2800
Wire Wire Line
	4450 800  4000 800 
Wire Wire Line
	4450 900  4000 900 
Wire Wire Line
	4450 1000 4000 1000
Wire Wire Line
	4450 1100 4000 1100
Wire Wire Line
	4450 1200 4000 1200
Wire Wire Line
	4450 1300 4000 1300
Wire Wire Line
	4450 1400 4000 1400
Wire Wire Line
	4450 1500 4000 1500
Wire Wire Line
	4450 1600 4000 1600
Wire Wire Line
	4450 1700 4000 1700
Wire Wire Line
	4450 1800 4000 1800
Wire Wire Line
	4450 1900 4000 1900
Wire Wire Line
	4375 2400 4000 2400
Wire Wire Line
	4375 2500 4000 2500
Wire Wire Line
	4375 2600 4000 2600
Wire Wire Line
	4375 2700 4000 2700
Wire Wire Line
	4375 2800 4000 2800
Wire Wire Line
	4375 2900 4000 2900
Wire Wire Line
	4375 3000 4000 3000
Wire Wire Line
	4375 3100 4000 3100
Wire Wire Line
	4375 3200 4000 3200
Wire Wire Line
	4375 3300 4000 3300
Wire Wire Line
	4375 3400 4000 3400
Wire Wire Line
	4375 3500 4000 3500
Text Label 4000 800  0    50   ~ 0
PULLUP_A
Text Label 4000 900  0    50   ~ 0
PULLUP_B
Text Label 4000 1000 0    50   ~ 0
PULLUP_C
Text Label 4000 1100 0    50   ~ 0
PULLUP_D
Text Label 4000 1200 0    50   ~ 0
PULLUP_E
Text Label 4000 1300 0    50   ~ 0
PULLUP_F
Text Label 4000 1400 0    50   ~ 0
PULLUP_G
Text Label 4000 1500 0    50   ~ 0
PULLUP_H
Text Label 4000 1600 0    50   ~ 0
PULLUP_I
Text Label 4000 1700 0    50   ~ 0
PULLUP_J
Text Label 4000 1800 0    50   ~ 0
PULLUP_K
Text Label 4000 1900 0    50   ~ 0
PULLUP_L
Text Label 5675 2900 0    50   ~ 0
SCL1
Text Label 5675 3000 0    50   ~ 0
SDA1
Text Label 7150 1475 0    50   ~ 0
PULLUP_A
Text Label 8350 1475 0    50   ~ 0
PULLUP_B
Text Label 9400 1500 0    50   ~ 0
PULLUP_C
Text Label 7150 2025 0    50   ~ 0
PULLUP_D
Text Label 8350 2025 0    50   ~ 0
PULLUP_E
Text Label 9400 2050 0    50   ~ 0
PULLUP_F
Text Label 7150 2575 0    50   ~ 0
PULLUP_G
Text Label 8350 2575 0    50   ~ 0
PULLUP_H
Text Label 9400 2600 0    50   ~ 0
PULLUP_I
Text Label 7150 3125 0    50   ~ 0
PULLUP_J
Text Label 8350 3125 0    50   ~ 0
PULLUP_K
Text Label 2500 2125 0    50   ~ 0
PULLUP_L
$Comp
L Device:R R2
U 1 1 60167105
P 2500 2500
F 0 "R2" H 2430 2454 50  0000 R CNN
F 1 "R_MAX (18K)" H 2430 2545 50  0000 R CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 2430 2500 50  0001 C CNN
F 3 "~" H 2500 2500 50  0001 C CNN
	1    2500 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 2350 2500 2125
Wire Wire Line
	2500 2650 2500 2900
Text Label 4000 2400 0    50   ~ 0
A0
Text Label 4000 2500 0    50   ~ 0
A1
Text Label 4000 2600 0    50   ~ 0
A2
Text Label 4000 2700 0    50   ~ 0
A3
Text Label 4000 2800 0    50   ~ 0
A4
Text Label 4000 2900 0    50   ~ 0
A5
Text Label 4000 3000 0    50   ~ 0
A6
Text Label 4000 3100 0    50   ~ 0
A7
Text Label 4000 3200 0    50   ~ 0
A8
Text Label 4000 3300 0    50   ~ 0
A9
Text Label 4000 3400 0    50   ~ 0
A10
Text Label 4000 3500 0    50   ~ 0
AREF
Text Label 2500 2900 0    50   ~ 0
AREF
Text Label 7150 1675 0    50   ~ 0
GND
Text Label 7150 2225 0    50   ~ 0
GND
Text Label 7150 2775 0    50   ~ 0
GND
Text Label 7150 3325 0    50   ~ 0
GND
Text Label 8350 3325 0    50   ~ 0
GND
Text Label 8350 2775 0    50   ~ 0
GND
Text Label 9400 2800 0    50   ~ 0
GND
Text Label 9400 2250 0    50   ~ 0
GND
Text Label 8350 2225 0    50   ~ 0
GND
Text Label 8350 1675 0    50   ~ 0
GND
Text Label 9400 1700 0    50   ~ 0
GND
Text Label 7150 1575 0    50   ~ 0
A0
Text Label 8350 1575 0    50   ~ 0
A1
Text Label 9400 1600 0    50   ~ 0
A2
Text Label 7150 2125 0    50   ~ 0
A3
Text Label 8350 2125 0    50   ~ 0
A4
Text Label 9400 2150 0    50   ~ 0
A5
Text Label 7150 2675 0    50   ~ 0
A6
Text Label 8350 2675 0    50   ~ 0
A7
Text Label 9400 2700 0    50   ~ 0
A8
Text Label 7150 3225 0    50   ~ 0
A9
Text Label 8350 3225 0    50   ~ 0
A10
$Comp
L DisarmedParts:MCP47CXBXX U3
U 1 1 601C1442
P 4950 4950
F 0 "U3" H 4925 5565 50  0000 C CNN
F 1 "MCP47CXBXX" H 4925 5474 50  0000 C CNN
F 2 "Package_SO:MSOP-10-1EP_3x3mm_P0.5mm_EP1.68x1.88mm_ThermalVias" H 4950 4600 50  0001 C CNN
F 3 "" H 4950 4600 50  0001 C CNN
	1    4950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4600 5825 4600
Wire Wire Line
	5400 4700 5825 4700
Wire Wire Line
	5400 4800 5825 4800
Wire Wire Line
	4450 4700 4075 4700
Wire Wire Line
	4450 4800 4075 4800
Wire Wire Line
	4450 4900 4075 4900
Wire Wire Line
	4450 5000 4075 5000
Wire Wire Line
	5400 4900 5825 4900
Wire Wire Line
	5400 5000 5825 5000
Wire Wire Line
	4450 4600 4075 4600
Text Label 4075 4600 0    50   ~ 0
VCC
Text Label 5825 4900 0    50   ~ 0
GND
Text Label 4075 4900 0    50   ~ 0
AOUT0
Text Label 4075 5000 0    50   ~ 0
AOUT1
Text Label 4075 4800 0    50   ~ 0
VCC
Text Label 4075 4700 0    50   ~ 0
GND
Text Label 5825 4800 0    50   ~ 0
GND
Text Label 5825 4600 0    50   ~ 0
SDA1
Text Label 5825 4700 0    50   ~ 0
SCL1
NoConn ~ 5825 5000
$Comp
L Connector_Generic:Conn_01x02 J14
U 1 1 601F1F34
P 8875 3250
F 0 "J14" H 8793 2925 50  0000 C CNN
F 1 "Conn_01x02" H 8793 3016 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 8875 3250 50  0001 C CNN
F 3 "~" H 8875 3250 50  0001 C CNN
	1    8875 3250
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J15
U 1 1 601F31D9
P 8875 3700
F 0 "J15" H 8793 3375 50  0000 C CNN
F 1 "Conn_01x02" H 8793 3466 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 8875 3700 50  0001 C CNN
F 3 "~" H 8875 3700 50  0001 C CNN
	1    8875 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9075 3150 9575 3150
Wire Wire Line
	9075 3250 9575 3250
Wire Wire Line
	9075 3600 9575 3600
Wire Wire Line
	9075 3700 9575 3700
Text Label 9575 3250 0    50   ~ 0
GND
Text Label 9575 3700 0    50   ~ 0
GND
Text Label 9575 3150 0    50   ~ 0
AOUT0
Text Label 9575 3600 0    50   ~ 0
AOUT1
Wire Wire Line
	5675 2900 5375 2900
$Comp
L Device:R R3
U 1 1 600FCA7E
P 5750 3650
F 0 "R3" H 5820 3696 50  0000 L CNN
F 1 "4.7K" H 5820 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 5680 3650 50  0001 C CNN
F 3 "~" H 5750 3650 50  0001 C CNN
	1    5750 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 600FD5EB
P 6250 3650
F 0 "R4" H 6320 3696 50  0000 L CNN
F 1 "4.7K" H 6320 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_1210_3225Metric_Pad1.30x2.65mm_HandSolder" V 6180 3650 50  0001 C CNN
F 3 "~" H 6250 3650 50  0001 C CNN
	1    6250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3500 6000 3500
Wire Wire Line
	6000 3500 6000 3250
Connection ~ 6000 3500
Wire Wire Line
	6000 3500 5750 3500
Wire Wire Line
	5750 3800 5750 4000
Wire Wire Line
	6250 3800 6250 4000
Text Label 6000 3250 0    50   ~ 0
VCC
Text Label 5750 4000 0    50   ~ 0
SCL1
Text Label 6250 4000 0    50   ~ 0
SDA1
$EndSCHEMATC
