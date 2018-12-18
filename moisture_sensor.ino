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
}

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

	if (outputValue < 150) {
		// Switching LED's based off threshold
		digitalWrite(redLED, HIGH);
		digitalWrite(greenLED, LOW);
	} else {
		digitalWrite(greenLED, HIGH);
		digitalWrite(redLED, LOW);
		Serial.println("\n NEEDS WATERING");
	}

	delay(150);        // delay in between reads for stability
}
