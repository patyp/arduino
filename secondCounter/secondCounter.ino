
#include "Arduino.h"
/*
 4 Digital 8-Segment LED Display
 Display four numbers on 4 Digital 8-Segment LED Display
 In this sketch, we use D2-D9 to control A/B/C/D/E/F/G/DP segment respectively. And use D10/D11/D12/D13 to control the anode of DIG1-DIG4 respectively.
 */
int DIG[4] = { 10, 11, 12, 13 }; //The pins used to controll the anode of the 4 bit,DIG1-DIG4.
//char Str[4] = {'2', '0', '1', '4', };//The number to be displayed.
byte Numcode[11] = { 0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6,
		0x00 }; //the character code for number 1-9 and empty character
void setup() {
	int i = 2;
	//Set D2-D13 as OUTPUT
	for (i = 2; i < 14; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	int k = 0;
	for (k = 0; k < 4; k++) {
		digitalWrite(DIG[k], LOW);
	}
	Serial.begin(9600);
}
void loop() {
	int i = 0;
	int j;
	int k = 0;

	int cas = millis() / 100;
	String text = String(cas);

	int tLength = text.length();

	int pad = 4 - tLength; // number of digits which will not be displaying effective value (from left) - padding
	//Display DIG1-DIG4
	for (k = 0; k < 4; k++) {
		char c;
		if (k < pad) {
			c = ':'; // it will represents empty character
		} else {
			c = text.charAt(k - pad);
		}

		i = c - 48; //find out the number's position in the character code array.
		//display the number
		for (j = 0; j < 8; j++) {
			if (Numcode[i] & 1 << j)
				digitalWrite(9 - j, LOW);
			else
				digitalWrite(9 - j, HIGH);
		}
		if (k == 2) { // decimal point on this place
			digitalWrite(9, LOW);
		}
		digitalWrite(DIG[k], HIGH);
		delay(3);
		digitalWrite(DIG[k], LOW);
	}
}
