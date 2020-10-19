#include "LiquidCrystal.h"
// intializing pins 
const int analogInPin = A0; // main input 
int sensorValue = 0;
int outputValue = 0;
const int redLED = 9;
const int greenLED = 10;
const int enable = 8, rs = 12, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
//String displayString = "";
//const int nMOS = 3; //variable for pin connected to MOSFET
LiquidCrystal lcd(enable, rs, d4, d5, d6, d7);

void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	// initializes pins as outputs
	pinMode(redLED, OUTPUT);
	pinMode(greenLED, OUTPUT);
	// pinMode(nMOS, OUTPUT);
  //  begin LCD screen output
  lcd.begin(16, 2);
  // Print these words to my LCD screen (bad lcd means first two letters get cut off, hence the 2 spaces)

	String str = "Level: ";
	intitializeSequence();
}


// dry soil: > 80
// moist soil: 50 - 80
// wet soil: < 50
// in terms of outputValue

void loop() {
	sensorConversion();
	moistureRange();
	delay(1000);        // delay in between reads for stability
}


// // ------------------------- Functions -------------------------------- //

void intitializeSequence() {
	// initialize sequence... need to add error function if intialize sequence doesnt complete
	digitalWrite(greenLED, HIGH);
	digitalWrite(redLED, LOW);
	delay(100);
	digitalWrite(greenLED, LOW);
	digitalWrite(redLED, LOW);
	delay(100);
	digitalWrite(greenLED, HIGH);
	digitalWrite(redLED, LOW);
}

void moistureRange() {
  String str = "Level: ";
  String value = String(outputValue, DEC);
  String displayString = str += value ;
	if (outputValue <= 50) {
		// Switching LED's based off threshold
		digitalWrite(redLED, HIGH);
		digitalWrite(greenLED, HIGH);
		Serial.println("\n TOO WET");
    lcd.print(displayString);
    	// digitalWrite(nMOS, LOW);
	} else if (outputValue > 50 & outputValue < 80) {
		digitalWrite(greenLED, HIGH);
		digitalWrite(redLED, LOW);
		Serial.println("\n PERFECT");
    lcd.print(displayString);
    	// digitalWrite(nMOS, LOW);
	} else {
		digitalWrite(greenLED, LOW);
		digitalWrite(redLED, HIGH);
		Serial.println("\n NEEDS WATERING");
    lcd.print(displayString);
    	// digitalWrite(nMOS, HIGH);
	}
}

void sensorConversion() {
	// read the input on analog pin 0:
	sensorValue = analogRead(analogInPin);
	// convert to range of 0 - 255 
	outputValue = map(sensorValue, 0, 1023, 0, 255);
 	Serial.println(outputValue);
  lcd.clear();
}
