#include <SoftwareSerial.h>
#include "bme280_0x76.h"
#include "PMS.h"

// WIFI
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h"

BME280<> bme;

const byte rxPin = 14;
const byte txPin = 12;
SoftwareSerial pmsSerial (rxPin, txPin);

PMS pms(pmsSerial);
PMS::DATA data;

#ifndef APSSID
#define APSSID "Smog"
#define APPSK "smog"
#endif

const char *ssid = "Smog";
const char *password = "smog";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void handleJson() {
  String json = "{";

  json += "\"pm_1_0\":" + String(data.PM_AE_UG_1_0) + ",";
  json += "\"pm_2_5\":" + String(data.PM_AE_UG_2_5) + ",";
  json += "\"pm_10\":" + String(data.PM_AE_UG_10_0) + ",";

  json += "\"temperature\":" + String(bme.temperature) + ",";
  json += "\"humidity\":" + String(bme.humidity) + ",";
  json += "\"pressure\":" + String(bme.pressure);

  json += '}';

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(9600);
  pmsSerial.begin(9600);
  
  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1) delay(10);
  }

  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/api", handleJson);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  if (pms.read(data))
  {
    // Serial.print("PM 1.0 (ug/m3): ");
    // Serial.println(data.PM_AE_UG_1_0);

    // Serial.print("PM 2.5 (ug/m3): ");
    // Serial.println(data.PM_AE_UG_2_5);

    // Serial.print("PM 10.0 (ug/m3): ");
    // Serial.println(data.PM_AE_UG_10_0);

    bme.refresh();

    // Serial.print("Temp: ");
    // Serial.println(bme.temperature);

    // Serial.print("Humidity: ");
    // Serial.println(bme.humidity);

    // Serial.println();
  }
}
