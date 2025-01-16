const int tempValue = A0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int temp = analogRead(tempValue);
  float voltage = temp*(5.0/1023.0);
  float temperature = voltage*100.0;
  Serial.print("Temperauture :");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(1000);
}