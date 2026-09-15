#include <Arduino.h>

const int potPin = 33; 
const int ledMerah = 12;
const int ledKuning = 13;
const int ledHijau = 14;
const int buttonPin = 32; 

const float teganganReferensi = 3.3; 
const float hambatanTotal = 10000.0; 

void setup() {
  Serial.begin(115200);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  delay(1000);
  Serial.println("--- Mulai Sistem Indikator Tegangan (Dengan Tombol Override) ---");
}

void loop() {
  int statusTombol = digitalRead(buttonPin);
  int rawADC = analogRead(potPin);
  
  float tegangan = (rawADC / 4095.0) * teganganReferensi;
  float hambatan = (rawADC / 4095.0) * hambatanTotal;

  Serial.print("Tegangan: ");
  Serial.print(tegangan);
  Serial.print(" V   |   Tombol: ");
  
  if (statusTombol == LOW) {
    Serial.println("DITEKAN (Semua LED Mati)");
  } else {
    Serial.println("DILEPAS (Indikator Aktif)");
  }

  if (statusTombol == LOW) {
    digitalWrite(ledMerah, LOW);
    digitalWrite(ledKuning, LOW);
    digitalWrite(ledHijau, LOW);
  } 
  else {
    if (tegangan >= 0.00 && tegangan <= 1.10) {
      digitalWrite(ledMerah, HIGH);
      digitalWrite(ledKuning, LOW);
      digitalWrite(ledHijau, LOW);
    } 
    else if (tegangan > 1.10 && tegangan <= 2.20) {
      digitalWrite(ledMerah, LOW);
      digitalWrite(ledKuning, HIGH);
      digitalWrite(ledHijau, LOW);
    } 
    else if (tegangan > 2.20 && tegangan <= 3.33) {
      digitalWrite(ledMerah, LOW);
      digitalWrite(ledKuning, LOW);
      digitalWrite(ledHijau, HIGH);
    }
  }

  delay(500); 
}