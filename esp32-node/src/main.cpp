#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <math.h>

const int SCAN_SECONDS = 5;
const int RSSI_AT_1M = -60;
const int MIN_RSSI = -90;   
const float PATH_LOSS_N = 2.5;

int totalSeen = 0;
BLEScan* pScan;

float rssiToDistance(int rssi) {
  return pow(10.0, (RSSI_AT_1M - rssi) / (10.0 * PATH_LOSS_N));
}

class MyCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice device) {
    int rssi = device.getRSSI();
    if (rssi< MIN_RSSI){
      return;
    }
    totalSeen++;
    float dist = rssiToDistance(rssi);

    const char* name = "(no name)";
    String nameStr;
    if (device.haveName()) {
      nameStr = String(device.getName().c_str());
      name = nameStr.c_str();
    }

    Serial.printf("MAC: %s | Name: %s | RSSI: %d dBm | ~%.1f m\n",
                  device.getAddress().toString().c_str(), name, rssi, dist);
  }
};

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== BLE Scanner ===");

  BLEDevice::init("");
  pScan = BLEDevice::getScan();
  pScan->setAdvertisedDeviceCallbacks(new MyCallbacks());
  pScan->setActiveScan(false);
  pScan->setInterval(100);
  pScan->setWindow(99);
}

void loop() {
  totalSeen = 0;
  Serial.println("Scanning...");
  pScan->start(SCAN_SECONDS, false);
  pScan->clearResults();

  Serial.printf("Scan done. Devices seen: %d\n", totalSeen);
  Serial.println("------------------------------");
  delay(2000);
}