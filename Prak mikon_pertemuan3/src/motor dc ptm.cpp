#include <Arduino.h>

const int in1 = 17;
const int in2 = 18;
const int pwmPin = 16;
const int stby = 19;
const int potPin = 34; // Pin untuk membaca potensiometer

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(stby, OUTPUT);
  
  digitalWrite(stby, HIGH); 
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(pwmPin, 0);
  
  Serial.begin(115200); 
}

void loop() {
  int potValue = analogRead(potPin); 
  int motorSpeed = map(potValue, 0, 4095, 0, 255); 
  
  ledcWrite(0, motorSpeed);
  
  delay(50); // Jeda singkat agar pembacaan stabil dan tidak membebani ESP32
}