#include <SoftwareSerial.h>
#include "bme280_0x76.h"
#include "PMS.h"

// WIFI
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

BME280<> bme;

const byte rxPin = 14;
const byte txPin = 12;
SoftwareSerial pmsSerial (rxPin, txPin);

PMS pms(pmsSerial);
PMS::DATA data;

const char *ssid = "Robonomik-stacja_pogodowa";
const char *password = "******";
String serverPath = "http://meteo.ekonomikzamosc.pl/sensor";

String getJson() {
  String json = "{";

  json += "\"pm_1_0\":" + String(data.PM_AE_UG_1_0) + ",";
  json += "\"pm_2_5\":" + String(data.PM_AE_UG_2_5) + ",";
  json += "\"pm_10\":" + String(data.PM_AE_UG_10_0) + ",";

  json += "\"temperature\":" + String(bme.temperature) + ",";
  json += "\"humidity\":" + String(bme.humidity) + ",";
  json += "\"pressure\":" + String(bme.pressure);

  json += '}';

  return json;
}

void setup() {
  Serial.begin(9600);
  pmsSerial.begin(9600);
  
  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  }

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (pms.read(data))
  {
    bme.refresh();

    if(WiFi.status() == WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      http.begin(client, serverPath.c_str());
      http.addHeader("Content-Type", "Content-Type: application/json"); 
      http.POST(getJson());
      http.end();
    }
  }
}
