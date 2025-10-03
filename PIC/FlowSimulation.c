/*
 * File:   newmain.c
 * Author: atom
 *
 * Created on September 29, 2025, 6:49 PM
 */

/*
[PIN Info]
         |~~~~~U~~~~~|
    RA2 =|1        18|= RA1
    RA3 =|2        17|= RA0
    RA4 =|3        16|= RA7
    RA5 =|4        15|= RA6
    VSS =|5        14|= VDD
    RB0 =|6        13|= RB7
    RB1 =|7        12|= RB6
    RB2 =|8        11|= RB5
    RB3 =|9        10|= RB4
         |~~~~~~~~~~~|
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

#define _XTAL_FREQ 16000000 // delay 16MHz

// =======================================================================

#define SIZE 8
#define PARTICLE 30
#define VISCOUS 50

#define SET_ANODE_SHIFT(value)   RA6 = value
#define SET_CATHODE_SHIFT(value) RB7 = value
#define SET_ANODE_SER(value)     RA1 = value
#define SET_CATHODE_SER(value)   RA0 = value
#define LATCH_ALL() RB6 = 0; RB5 = 0; RB6 = 1; RB5 = 1

#define TRUE 1
#define FALSE 0
#define FIT(value, low, high) (value < low) ? low : (value > high) ? high : value
#define WRITE(byte, x, y) byte[y] |= (1 << x)

unsigned char matrix[2][SIZE];
unsigned char randomByte = 0xAA;

unsigned char fastRandom() {
	randomByte ^= randomByte << 3;
	randomByte ^= randomByte >> 5;
	randomByte ^= randomByte << 1;
	return randomByte;
}

void updateScreen() {
	for (unsigned char row=0; row<SIZE; row++){
		// Set Anode
		for (unsigned char i=0; i<SIZE; i++) {
			SET_ANODE_SHIFT(1);
			SET_ANODE_SER((matrix[0][row] >> (7 - i)) & 1);
			SET_ANODE_SHIFT(0);
		}
		SET_ANODE_SHIFT(1); // Adjust to 8bit
		SET_ANODE_SHIFT(0); // Adjust to 8bit

		SET_CATHODE_SHIFT(1);
		SET_CATHODE_SER(row != 7); // Return 0 if row == 7
		SET_CATHODE_SHIFT(0);
		LATCH_ALL();
		__delay_ms(1);
	}
}

void isVacant(signed char *newX, signed char *newY, unsigned char *vacant, signed char index){
	const signed char directionX[] = {1, 1,  1,  0, -1, -1, -1, 0};
	const signed char directionY[] = {1, 0, -1, -1, -1,  0,  1, 1};
	index &= 7; // Ensure index is within 0 to 7
	*newX += directionX[index];
	*newY += directionY[index];
	*newX = FIT(*newX, 0, SIZE - 1);
	*newY = FIT(*newY, 0, SIZE - 1);
	*vacant = (matrix[0][*newY] & (1 << *newX)) == 0 && (matrix[1][*newY] & (1 << *newX)) == 0;
}

void moveParticle(const unsigned char x, const unsigned char y, const unsigned int angle) {
	const unsigned int angleSteps[] = {22, 67, 112, 157, 202, 247, 292, 337};
	unsigned char flag = TRUE;
	for (signed char i=0; i<7; i++) {
		if (angle >= angleSteps[i] && angle < angleSteps[i + 1]) {
			flag = FALSE;
			signed char newX, newY;
			unsigned char vacant;

			newX = (signed char)x; newY = (signed char)y;
			isVacant(&newX, &newY, &vacant, i);
			if (vacant) { WRITE(matrix[1], newX, newY); return; }

			newX = (signed char)x; newY = (signed char)y; // Reset position
			signed char randomDirect = (fastRandom() & 1) * 2 - 1; // Gives -1 or 1
			isVacant(&newX, &newY, &vacant, i + randomDirect);
			if (vacant) { WRITE(matrix[1], newX, newY); return; }

			newX = (signed char)x; newY = (signed char)y; // Reset position
			unsigned char randomNum = (unsigned char)(fastRandom() % VISCOUS);
			randomDirect = randomNum == 0 ? -2 : randomNum == 1 ? 2 : 0;
			isVacant(&newX, &newY, &vacant, i + randomDirect);
			if (vacant) { WRITE(matrix[1], newX, newY); return; }

			// Default
			WRITE(matrix[1], x, y); // Stay there
			break;
		}
	}

	if (flag) {
		signed char newX, newY;
		unsigned char vacant;

		newX = (signed char)x; newY = (signed char)y;
		isVacant(&newX, &newY, &vacant, 7);
		if (vacant) { WRITE(matrix[1], newX, newY); return; }

		newX = (signed char)x; newY = (signed char)y; // Reset position
		signed char randomDirect = (fastRandom() & 1) * 2 - 1; // Gives -1 or 1
		isVacant(&newX, &newY, &vacant, 7 + randomDirect);
		if (vacant) { WRITE(matrix[1], newX, newY); return; }

		newX = (signed char)x; newY = (signed char)y; // Reset position
		unsigned char randomNum = (unsigned char)(fastRandom() % VISCOUS);
		randomDirect = randomNum == 0 ? -2 : randomNum == 1 ? 2 : 0;
		isVacant(&newX, &newY, &vacant, 7 + randomDirect);
		if (vacant) { WRITE(matrix[1], newX, newY); return; }

		// Default
		WRITE(matrix[1], x ,y); // Stay there
	}
}

inline void shiftBuffer() {
	for (unsigned char i=0; i<SIZE; i++) {
		matrix[0][i] = matrix[1][i]; // Shift
		matrix[1][i] = 0b00000000;   // Clear second buffer
	}
}

void refresh(unsigned int angle) {
	for (unsigned char y=0; y<SIZE; y++) {
		for (unsigned char x=0; x<SIZE; x++) {
			if (matrix[0][y] & (1 << x)) {
				moveParticle(x, y, angle);
			}
		}
	}
}

void setMatrix() {
	unsigned char yAxis = PARTICLE / SIZE;
	unsigned char xAxis = PARTICLE % SIZE;
	// Full with 0
	for (unsigned char i=0; i<SIZE; i++) {
		matrix[0][i] = 0b00000000;
		matrix[1][i] = 0b00000000;
	}
	for (unsigned char y=0; y<yAxis; y++) { matrix[0][y] = 0b11111111; }
	for (unsigned char x=0; x<xAxis; x++) { WRITE(matrix[0], x, yAxis); }
}

void setup() {
	OSCCON = 0b01111010; // Make clock 16MHz
	ANSELA = 0b00000000; // Set all pins digital
	TRISA  = 0b00000000; // 0 -> OUTPUT/ 1 -> INPUT (RA5 INPUT only)
	PORTA  = 0b00000000; // Write all A pins LOW
	TRISB  = 0b00000000; // 0 -> OUTPUT/ 1 -> INPUT
	PORTB  = 0b00000000; // Write all B pins LOW

	RA1 = 0; // U2 SER
	RA0 = 1; // U3 SER
	RA6 = 0; // U2 SRCLK
	RB7 = 0; // U3 SRCLK
	RB6 = 0; // U2 RCLK
	RB5 = 0; // U3 RCLK
}

void main(void) {
	setup(); // Initialize Shift Registers
	setMatrix();
	unsigned int angle = 0;

	while (1) {
		for (unsigned char i=0; i<2; i++) {
			refresh(angle);
			shiftBuffer();
			updateScreen();
			__delay_ms(1);
		}
		angle += 3;
		if (angle >= 360) { angle = 0; }
	}
}
