#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  Serial.begin(115200);
  Wire.begin(15, 16); // Pin I2C Sensor
  ina219.begin();
}

void loop() {
  float arus_mA = ina219.getCurrent_mA();
  float tegangan_V = ina219.getBusVoltage_V();
  float daya_mW = ina219.getPower_mW();

  Serial.print("Tegangan: "); Serial.print(tegangan_V); Serial.println(" V");
  Serial.print("Arus: "); Serial.print(arus_mA); Serial.println(" mA");
  Serial.print("Daya: "); Serial.print(daya_mW); Serial.println(" mW");
  Serial.println("-----------------------");
  
  delay(1000);
}