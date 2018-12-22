// intializing pins 
const int analogInPin = A0; // main input 
int sensorValue = 0;
int outputValue = 0;
const int redLED = 9;
const int greenLED = 10;


void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	// initializes pins as outputs
	pinMode(redLED, OUTPUT);
	pinMode(greenLED, OUTPUT);
	
	intitializeSequence();
}

// air: 255
// dry soil: > 150
// moist soil: 80 - 150
// wet soil: < 80
// in terms of outputValue



// the loop routine runs over and over again forever:
void loop() {
	sensorConversion();
	moistureRange();
	delay(150);        // delay in between reads for stability
}


// // ------------------------- Functions -------------------------------- //

void intitializeSequence() {
	// initialize sequence... need to add error function if intialize sequence doesnt complete
	digitalWrite(greenLED, HIGH);
	digitalWrite(redLED, LOW);
	delay(1500);
	digitalWrite(greenLED, LOW);
	digitalWrite(redLED, HIGH);
	delay(1500);
	digitalWrite(greenLED, HIGH);
	digitalWrite(redLED, LOW);
}

void moistureRange() {
	// hardcoded values will be modified with self-calibrated values once number pad is integrated

	if (outputValue < 80) {
		// Switching LED's based off threshold
		digitalWrite(redLED, HIGH);
		digitalWrite(greenLED, HIGH);
		Serial.println("\n TOO WET");
	} else if (outputValue > 80 & outputValue < 150) {
		digitalWrite(greenLED, HIGH);
		digitalWrite(redLED, LOW);
		Serial.println("\n PERFECT");
	} else {
		digitalWrite(greenLED, LOW);
		digitalWrite(redLED, HIGH);
		Serial.println("\n NEEDS WATERING");
	}
}

void sensorConversion() {
	// read the input on analog pin 0:
	sensorValue = analogRead(analogInPin);
	// convert to range of 0 - 255 
	outputValue = map(sensorValue, 0, 1023, 0, 255);
}