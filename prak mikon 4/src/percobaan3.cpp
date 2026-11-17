#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN 12 

Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire1, -1);

const float BATAS_ARUS = 500.0; // Contoh batas: 500 mA

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  Wire.begin(15, 16); 
  
  Wire1.begin(8, 9); 
  
  ina219.begin();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {

  float arus_mA = ina219.getCurrent_mA();
  float tegangan_V = ina219.getBusVoltage_V();
  
  Serial.print("Arus Aktual: "); Serial.print(arus_mA); Serial.println(" mA");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  
  display.print("Arus: "); display.print(arus_mA); display.println(" mA");
  display.println("");
  
  display.setTextSize(2);
  
  if (arus_mA > BATAS_ARUS) {
    display.println("OVERLOAD");
    digitalWrite(BUZZER_PIN, HIGH); // Buzzer menyala saat overload
    Serial.println("Status: OVERLOAD");
  } else {
    display.println("NORMAL");
    digitalWrite(BUZZER_PIN, LOW);  // Buzzer mati saat aman
    Serial.println("Status: NORMAL");
  }
  
  Serial.println("-----------------------");
  
  display.display();
  
  delay(500);
}