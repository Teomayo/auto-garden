// intializing pins 
const int analogInPin = A0; // main input 
int sensorValue = 0;
int outputValue = 0;
const int redLED = 9;
const int greenLED = 10;
const int nMOS = 3; //variable for pin connected to MOSFET

void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	// initializes pins as outputs
	pinMode(redLED, OUTPUT);
	pinMode(greenLED, OUTPUT);
  pinMode(nMOS, OUTPUT);
	
	intitializeSequence();
}


// dry soil: > 80
// moist soil: 50 - 80
// wet soil: < 50
// in terms of outputValue



// the loop routine runs over and over again forever:
void loop() {
	sensorConversion();
	moistureRange();
	delay(50);        // delay in between reads for stability
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
	// hardcoded values will be modified with self-calibrated values once number pad is integrated

	if (outputValue <= 50) {
		// Switching LED's based off threshold
		digitalWrite(redLED, HIGH);
		digitalWrite(greenLED, HIGH);
		Serial.println("\n TOO WET");
    digitalWrite(nMOS, LOW);
	} else if (outputValue > 50 & outputValue < 80) {
		digitalWrite(greenLED, HIGH);
		digitalWrite(redLED, LOW);
		Serial.println("\n PERFECT");
    digitalWrite(nMOS, LOW);
	} else {
		digitalWrite(greenLED, LOW);
		digitalWrite(redLED, HIGH);
		Serial.println("\n NEEDS WATERING");
    digitalWrite(nMOS, HIGH);
	}
}

void sensorConversion() {
	// read the input on analog pin 0:
	sensorValue = analogRead(analogInPin);
	// convert to range of 0 - 255 
	outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(outputValue);
}
