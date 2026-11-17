#include <Arduino.h>
#include <WiFi.h>
#define ssid "hayolohyo"
#define password "apaantuh"

WiFiServer server(80);
String header;
String output13State = "off";
String output11State = "off";
const int output13 = 13;
const int output11 = 11;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(output13, OUTPUT);
  pinMode(output11, OUTPUT);
  digitalWrite(output13, LOW);
  digitalWrite(output11, LOW);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /11/on") >= 0) {
              Serial.println("GPIO 11 on");
              output11State = "on";
              digitalWrite(output11, HIGH);
            } else if (header.indexOf("GET /11/off") >= 0) {
              Serial.println("GPIO 11 off");
              output11State = "off";
              digitalWrite(output11, LOW);
            } else if (header.indexOf("GET /11/on") >= 0) {
              Serial.println("GPIO 11 on");
              output11State = "on";
              digitalWrite(output11, HIGH);
            } else if (header.indexOf("GET /11/off") >= 0) {
              Serial.println("GPIO 11 off");
              output11State = "off";
              digitalWrite(output11, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            client.println("<p>GPIO 13 - State " + output13State + "</p>");
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("<p>GPIO 11 - State " + output11State + "</p>");
            if (output11State=="off") {
              client.println("<p><a href=\"/11/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              // Baris terpotong pada button OFF pin 11 sudah digabungkan
              client.println("<p><a href=\"/11/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("<p>GPIO 11 - State " + output11State + "</p>");
            if (output11State=="off") {
              client.println("<p><a href=\"/11/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              // Baris terpotong pada button OFF pin 11 sudah digabungkan
              client.println("<p><a href=\"/11/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}