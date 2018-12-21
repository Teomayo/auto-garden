const int analogInPin = A0; // main input 
int sensorValue = 0;
int outputValue = 0;
const int redLED = 9;
const int greenLED = 10;


// self calibrating ints
bool dryRead = 0;
bool wetRead = 0;

void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	// initializes pins as outputs
	pinMode(redLED, OUTPUT);
	pinMode(greenLED, OUTPUT);
	
	// initialize sequence... need to add error function if intialize sequence doesnt complete
	digitalWrite(greenLED, HIGH);
	delay(150);
	digitalWrite(greenLED, LOW);
	digitalWrite(redLED, HIGH);
	delay(150);
	digitalWrite(greenLED, HIGH);

	// self calibration sequence
	Serial.print("Place sensor in dry soil and wait for reading");
	// sensorValue = analogRead(analogInPin);
	// Serial.print(sensorValue);
	if (Serial.available() > 0) {
        // read the incoming byte:
        dryRead = Serial.read();
        // say what you got:
        Serial.print("Dry Reading: ");
        Serial.println(dryRead);
	}
	

}

// air: 255
// dry soil: > 150
// moist soil: 80 - 150
// wet soil: < 80
// in terms of outputValue



// the loop routine runs over and over again forever:
void loop() {
	// read the input on analog pin 0:
	sensorValue = analogRead(analogInPin);
	// print out the value you read:
	outputValue = map(sensorValue, 0, 1023, 0, 255);
	Serial.print("\n Sensor Value: ");
	Serial.print(sensorValue);
	Serial.print("\n Output Value: ");
	Serial.print(outputValue);

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

	delay(150);        // delay in between reads for stability
}
