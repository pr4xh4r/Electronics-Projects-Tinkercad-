#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};  // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};  // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Connect RS, E, D4, D5, D6, D7

String inputString = "";
char operatorChar;
int num1, num2, result;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Arduino Calc");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);  // Initialize the Serial Monitor
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      inputString += key;
      lcd.setCursor(0, 1);
      lcd.print(inputString);
      Serial.print(key);  // Print the key to the Serial Monitor
    } else if (key == 'C') {
      inputString = "";
      lcd.clear();
      Serial.println("\nCleared");  // Notify Serial Monitor that input has been cleared
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      num1 = inputString.toInt();
      operatorChar = key;
      inputString = "";
      lcd.setCursor(0, 1);
      lcd.print(operatorChar);
      Serial.print(" ");  // Space for readability in Serial Monitor
      Serial.print(operatorChar);  // Print the operator to the Serial Monitor
      Serial.print(" ");  // Space for readability in Serial Monitor
    } else if (key == '=') {
      num2 = inputString.toInt();
      lcd.setCursor(0, 1);
      lcd.print("=");
      switch (operatorChar) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num2 != 0 ? num1 / num2 : 0; break;
      }
      lcd.print(result);
      Serial.println(num2);  // Print the second number to the Serial Monitor
      Serial.print(" = ");
      Serial.println(result);  // Print the result to the Serial Monitor
      inputString = String(result);
    }
  }
}
