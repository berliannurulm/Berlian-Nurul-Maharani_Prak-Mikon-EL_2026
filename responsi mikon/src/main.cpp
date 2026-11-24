#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

const int pinSDA = 21;
const int pinSCL = 22;
const int pwmPin = 18;
const int freq = 5000;
const int pwmChannel = 0;
const int resolution = 8;

const float tempMin = 25.0; 
const float tempMax = 35.0; 
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(pinSDA, pinSCL);
  
  if (!bme.begin(0x76)) {
    Serial.println("Sensor BME280 tidak ditemukan! Cek wiring.");
    while (1);
  }

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(pwmPin, pwmChannel);
}

void loop() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();

  int dutyCycle = map((long)(temperature * 100), (long)(tempMin * 100), (long)(tempMax * 100), 0, 255);

  dutyCycle = constrain(dutyCycle, 0, 255);

  ledcWrite(pwmChannel, dutyCycle);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("PWM Duty Cycle: ");
  Serial.print(dutyCycle);
  Serial.println(" / 255");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(1000); 
}