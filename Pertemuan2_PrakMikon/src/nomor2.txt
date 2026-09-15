#include <Arduino.h>

const int ledMerah = 2;
const int ledKuning = 4;
const int ledHijau = 5;
const int buttonPin = 22;

void setup() {
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int statusTombol = digitalRead(buttonPin);

  if (statusTombol == LOW) {
    digitalWrite(ledMerah, HIGH);
    digitalWrite(ledKuning, HIGH);
    digitalWrite(ledHijau, HIGH);
  } else {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledHijau, LOW);
  }
}