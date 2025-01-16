#include<LiquidCrystal_I2C.h>

const int trigPin = 9;   // Pin connected to Trig pin of the sensor
const int echoPin = 10;  // Pin connected to Echo pin of the sensor

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);  // Set trigPin as output
  pinMode(echoPin, INPUT);   // Set echoPin as input
  
}

void loop() {
  long duration, distance;

  // Send a pulse from the sensor
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = (duration / 2) / 29.1;
  
  // Clear the second row before printing
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE:      "); // Clear the previous text (12 characters)
  
  // Print new distance value
  lcd.setCursor(0, 1);  // Set cursor after "DISTANCE:"
  lcd.print(distance);
  lcd.print("cm");

  
  
  delay(500);  // Wait for 500ms
}
