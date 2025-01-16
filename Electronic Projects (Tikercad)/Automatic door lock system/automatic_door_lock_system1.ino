#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // If using I2C LCD

// Define the password
String password = "1234";
String inputPassword = "";

// Set up the servo
Servo myServo;
int servoPin = 10;

// Set up the LCD (if using I2C)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27 for a 16x2 display

// Set up the keypad
const byte ROWS = 4;  // Four rows
const byte COLS = 4;  // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};   // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};   // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  myServo.attach(servoPin);
  myServo.write(0);  // Lock position
  
  // Initialize the LCD (if using)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '#') {
      if (inputPassword == password) {
        unlockDoor();
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Wrong! Try again");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
      }
      inputPassword = "";  // Clear input
    } else if (key == '*') {
      inputPassword = "";  // Clear input
      lcd.setCursor(0, 1);
      lcd.print("Cleared");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("                ");  // Clear line
    } else {
      inputPassword += key;
      lcd.setCursor(0, 1);
      lcd.print(inputPassword);
    }
  }
}

void unlockDoor() {
  lcd.setCursor(0, 1);
  lcd.print("Access Granted!");
  myServo.write(90);  // Unlock position
  delay(5000);        // Keep the door unlocked for 5 seconds
  myServo.write(0);   // Lock again
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}
