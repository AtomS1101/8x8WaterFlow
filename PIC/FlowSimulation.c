#include <stdlib.h>

#define SIZE 8
#define PARTICLE 30
#define VISCOUS 50

#define TRUE 1
#define FALSE 0

unsigned char matrix[2][8];

void updateScreen() {
}

void isVacant(signed char *newX, signed char *newY, unsigned char *vacant, signed char index){
	const signed char directionX[] = {1, 1,  1,  0, -1, -1, -1, 0};
	const signed char directionY[] = {1, 0, -1, -1, -1,  0,  1, 1};
	index = index >= 8 ? index - 8 : index;
	*newX += directionX[index];
	*newY += directionY[index];
	*newX = *newX < 0 ? 0 : *newX >= SIZE ? SIZE - 1 : *newX;
	*newY = *newY < 0 ? 0 : *newY >= SIZE ? SIZE - 1 : *newY;
	*vacant = (matrix[0][*newY] & (1 << *newX)) == 0 && (matrix[1][*newY] & (1 << *newX)) == 0;
}

void moveParticle(const unsigned char x, const unsigned char y, const unsigned int angle) {
	unsigned int steps[] = {22, 67, 112, 157, 202, 247, 292, 337};
	unsigned char flag = FALSE;
	for (signed char i=0; i<7; i++) {
		if (angle >= steps[i] && angle < steps[i + 1]) {
			flag = TRUE;
			signed char newX, newY;
			unsigned char vacant;

			newX = (signed char)x;
			newY = (signed char)y;
			isVacant(&newX, &newY, &vacant, i);
			if (vacant) { matrix[1][newY] |= (1 << newX); return; }

			newX = (signed char)x; // Reset position
			newY = (signed char)y;
			signed char randomDirect = rand() % 2 == 0 ? 1 : -1;
			isVacant(&newX, &newY, &vacant, i + randomDirect);
			if (vacant) { matrix[1][newY] |= (1 << newX); return; }

			newX = (signed char)x; // Reset position
			newY = (signed char)y;
			unsigned char randomNum = (unsigned char)(rand() % VISCOUS);
			randomDirect = randomNum == 0 ? -2 : randomNum == 1 ? 2 : 0;
			isVacant(&newX, &newY, &vacant, i + randomDirect);
			if (vacant) { matrix[1][newY] |= (1 << newX); return; }

			// Default
			matrix[1][y] |= (1 << x);
			break;
		}
	}

	if (!flag) {
		signed char newX, newY;
		unsigned char vacant;

		newX = (signed char)x;
		newY = (signed char)y;
		isVacant(&newX, &newY, &vacant, 7);
		if (vacant) { matrix[1][newY] |= (1 << newX); return; }

		newX = (signed char)x; // Reset position
		newY = (signed char)y;
		signed char randomDirect = rand() % 2 == 0 ? 1 : -1;
		isVacant(&newX, &newY, &vacant, 7 + randomDirect);
		if (vacant) { matrix[1][newY] |= (1 << newX); return; }

		newX = (signed char)x; // Reset position
		newY = (signed char)y;
		unsigned char randomNum = (unsigned char)(rand() % VISCOUS);
		randomDirect = randomNum == 0 ? -2 : randomNum == 1 ? 2 : 0;
		isVacant(&newX, &newY, &vacant, 7 + randomDirect);
		if (vacant) { matrix[1][newY] |= (1 << newX); return; }

		// Default
		matrix[1][y] |= (1 << x);
	}
}

inline void shiftBuffer() {
	for (unsigned char i=0; i<SIZE; i++) {
		matrix[0][i] = matrix[1][i]; // Shift
		matrix[1][i] = 0b00000000;   // Clear
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
	for (unsigned char x=0; x<xAxis; x++) { matrix[0][yAxis] |= (1 << x); }
}

void setup() {
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
	setup(); // Initialize Shift Registers
	setMatrix();
	unsigned int angle = 0;

	while (1) {
		for (unsigned char i=0; i<2; i++) {
			refresh(angle);
			shiftBuffer();
			updateScreen();
			__delay_ms(20);
		}
		angle += 3;
		if (angle >= 360) {
			angle = 0;
		}
	}
}
