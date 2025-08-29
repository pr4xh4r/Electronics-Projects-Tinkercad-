int enA = 9;   // PWM pin (speed control)
int in1 = 7;   // Direction control
int in2 = 8;   // Direction control

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter value 0-20:");
}

void loop() {
  if (Serial.available() > 0) {
    int inputVal = Serial.parseInt();  // read integer from Serial

    if (inputVal >= 0 && inputVal <= 10) {
      // Clockwise
      if (inputVal == 0) {
        stopMotor();
      } else {
        int speed = calcSpeed(inputVal, 10); // scale 0–10 → 0–255
        moveMotor(speed, true);  // true = clockwise
      }
    } 
    else if (inputVal >= 11 && inputVal <= 20) {
      // Anti-clockwise
      if (inputVal == 11) {
        stopMotor();
      } else {
        int speed = calcSpeed(inputVal - 11, 9); // scale 0–9 → 0–255
        moveMotor(speed, false); // false = anti-clockwise
      }
    } 
    else {
      Serial.println("Invalid! Enter 0-20 only.");
    }
  }
}

// 🧮 Custom function to replace map()
int calcSpeed(int val, int maxVal) {
  
  return (val * 255) / maxVal;
}

void moveMotor(int speed, bool clockwise) {
  speed = constrain(speed, 0, 255); // ensure PWM range
  if (clockwise) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(enA, speed);
  Serial.print("Motor running ");
  Serial.print(clockwise ? "Clockwise" : "Anti-clockwise");
  Serial.print(" | Speed: ");
  Serial.println(speed);
}

void stopMotor() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  Serial.println("Motor Stopped");
}

