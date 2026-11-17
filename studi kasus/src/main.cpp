#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int in1 = 17;
const int in2 = 18;
const int pwmPin = 16;
const int stby = 19;
const int potPin = 34;
const int ledPin = 2;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(stby, HIGH); 
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(pwmPin, 0);

  ina219.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  int potValue = analogRead(potPin); 
  int pwmValue = map(potValue, 0, 4095, 0, 255); 
  int persenPWM = map(potValue, 0, 4095, 0, 100); 

  ledcWrite(0, pwmValue);

  if (potValue >= 4050) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  float arus = ina219.getCurrent_mA();
  float tegangan_V = ina219.getBusVoltage_V();

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("PWM      : ");
  display.print(persenPWM);

  display.setCursor(0, 16);
  display.print("Tegangan : ");
  display.print(tegangan_V);

  display.setCursor(0, 32);
  display.print("Arus     : ");
  display.print(arus);

  display.display();
  delay(1000);
}