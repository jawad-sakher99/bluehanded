#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== WiFi Test ===");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting");
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 40) {
    delay(500);
    Serial.print(".");
    tries++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi: CONNECTED");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("Signal (RSSI): %d dBm\n", WiFi.RSSI());
  } else {
    Serial.println("WiFi: FAILED (check SSID/password, use a 2.4 GHz network)");
  }
}

void loop() {
  delay(1000);
}