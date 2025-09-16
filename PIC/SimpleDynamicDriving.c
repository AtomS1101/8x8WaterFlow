/*
 * File:   newmain.c
 * Author: atom
 *
 * Created on September 9, 2025, 5:04 PM
 */

/*
[PIN Info]
            |~~~~~U~~~~~|
    RA2    =| 1       18|= RA1
    RA3    =| 2       17|= RA0
    RA4    =| 3       16|= RA7
    RA5    =| 4       15|= RA6
    VSS    =| 5       14|= VDD
    RB0    =| 6       13|= RB7
    RB1    =| 7       12|= RB6
    RB2    =| 8       11|= RB5
    RB3    =| 9       10|= RB4
            ~~~~~~~~~~~~~
*/

#include <xc.h>

// ???????????1???
#pragma config FOSC  = INTOSC   // ???????????(INTOSC)
#pragma config WDTE  = OFF      // ???????????????(OFF)
#pragma config PWRTE = ON       // ??ON??64ms??????????????(ON)
#pragma config MCLRE = OFF      // ??????????????????????(RA5)??????(OFF)
#pragma config CP    = OFF      // ?????????????????(OFF)
#pragma config CPD   = OFF      // ??????????????(OFF)
#pragma config BOREN = ON       // ????????????ON(ON)
#pragma config CLKOUTEN = OFF   // CLKOUT????RA6????????(OFF)
#pragma config IESO  = OFF      // ????????????????????(OFF)
#pragma config FCMEN = OFF      // ???????????(FCMEN_OFF)

// ???????????2???
#pragma config WRT    = OFF     // Flash??????????(OFF)
#pragma config PLLEN  = OFF     // ???????32MHz????????(OFF)
#pragma config STVREN = ON      // ?????????????????????????????(ON)
#pragma config BORV   = HI      // ????????????(2.5V)??(HI)
#pragma config LVP    = OFF     // ?????????????????(OFF)


#define _XTAL_FREQ  8000000 // delay 8MHz
//#define _XTAL_FREQ 16000000 // delay 16MHz

void latch(void) {
    RB6 = 0; // U2 Latch LOW
    RB5 = 0; // U3 Latch LOW
    NOP();
    RB6 = 1; // U2 Latch HIGH
    RB5 = 1; // U3 Latch HIGH
    NOP();
}

void shiftCathode(unsigned char i) {
	RB7 = 1; // Shift CLK HIGH
    NOP();
    RA0 = (i == 7) ? 0 : 1;
	RB7 = 0; // Shift CLK LOW
    NOP();
}

void setAnode(unsigned char row) {
	for (unsigned char i=0; i<8; i++) {
		RA6 = 1;  // Shift CLK HIGH
        NOP();
		RA1 = (row >> (7 - i)) & 1;
		RA6 = 0;  // Shift CLK LOW
        NOP();
	}
    RA6 = 1;
    RA6 = 0;
}

void reset(void) {
	OSCCON = 0b01110010;   // Make clock 8MHz
	// OSCCON = 0b01111010;   // Make clock 16MHz
	ANSELA = 0b00000000;   // Set all pins digital
	TRISA  = 0b00000000;   // 0 -> OUTPUT/ 1 -> INPUT (RA5 INPUT only)
	PORTA  = 0b00000000;   // Write all A pins LOW
	TRISB  = 0b00000000;   // 0 -> OUTPUT/ 1 -> INPUT
	PORTB  = 0b00000000;   // Write all B pins LOW

	RA1 = 0; // U2 SER
	RA0 = 1; // U3 SER
	RA6 = 0; // U2 SRCLK
	RB7 = 0; // U3 SRCLK
	RB6 = 0; // U2 RCLK
	RB5 = 0; // U3 RCLK

	// Fill with HIGH
	for (unsigned char i=0; i<8; i++) {
		RB7 = 1; // Shift CLK HIGH
		RB7 = 0; // Shift CLK LOW
	}
	RB5 = 0; // Latch LOW
    RB5 = 1; // Latch HIGH
    RB5 = 0; // Latch LOW
}

void main(void) {
	reset();
	unsigned char matrix[8] = {
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111100,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	};

	while (1) {
		for (unsigned char i=0; i<8; i++) {
			setAnode(matrix[i]);
			shiftCathode(i);
            latch();
			__delay_ms(2);
		}
	}
}
