const int pirPin = 2;    // Pin connected to the PIR sensor
const int ledPin = 13;   // Pin connected to the LED

void setup() {
  pinMode(pirPin, INPUT);   // Set the PIR pin as input
  pinMode(ledPin, OUTPUT);  // Set the LED pin as output
}

void loop() {
  int motionState = digitalRead(pirPin);  // Read the PIR sensor

  if (motionState == HIGH) {  // If motion is detected
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(5000);                // Keep the LED on for 5 seconds
    digitalWrite(ledPin, LOW);   // Turn off the LED
  }
}
