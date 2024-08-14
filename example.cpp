#include <Arduino.h>
#include <WiFi.h>
#include <Fetchxios.h>
#include <ArduinoJson.h>

Fetchxios fetch;

const char* ssid = "YOUR SSID";
const char* password = "PASS HERE";


void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  fetch.setBaseURL("https://webhook.site");
}

void loop() {
  fetch.GET("/af05e624-3fe5-4cf6-bf35-2254dd270855?name=John");
  DynamicJsonDocument doc(1024);
  doc["name"] = "John";
  doc["age"] = 30;
  const char* payload = "";
  serializeJson(doc, payload);
  fetch.POST("/22c11709-ed1a-4024-a689-fb4759950166", payload);
  
  delay(1000);
}
