# Blue-Handed

Detection and Localization of Unauthorized Wireless Devices.

## About

Blue-Handed is an anti-cheat system for exam halls. ESP32 nodes passively scan Bluetooth Low Energy (BLE) signals, and a Raspberry Pi estimates the location of suspicious devices and alerts the proctor on a web dashboard.

## Team

- Yanal Al-Qudah
- Rashida Khraise
- Yazan Nayfeh
- Jawad Bani Amer

## Structure

- `docs/`: project report and documents
- `esp32-node/`: ESP32 firmware (PlatformIO project, Arduino framework)

## Status

Early development. The current firmware in `esp32-node/src/main.cpp` is **test code**: a passive BLE scanner used to check that each ESP32 board and its Bluetooth work. It is not the final detection system.

## Running the test code

Requirements:
- An ESP32 board (ESP32 Dev Module / WROOM-32) and a USB data cable
- Visual Studio Code with the **PlatformIO IDE** extension
- Git

Steps:
1. Clone the repository and open the **`esp32-node`** folder in VS Code (File > Open Folder...). Open this subfolder, not the repository root, because PlatformIO needs the folder that contains `platformio.ini` to show Project Tasks (Build / Upload / Monitor).
2. Wait for PlatformIO to finish setting up (the first time it downloads the ESP32 tools and takes a few minutes).
3. Connect the ESP32 to the computer with the USB cable.
4. Click **Build** to check that the code compiles (PlatformIO icon > Project Tasks > esp32dev > General > Build).
5. Click **Upload** to flash the board. If it hangs on `Connecting......`, see the next section.
6. Click **Monitor** to open the Serial Monitor (115200 baud).

Expected output (every 5 seconds):

```
Scanning...
MAC: aa:bb:cc:dd:ee:ff | Name: (no name) | RSSI: -62 dBm | ~2.1 m
Scan done. Devices seen: 1
```

Notes:
- Keep a Bluetooth device nearby (phone or smartwatch with Bluetooth on), otherwise nothing is listed.
- BLE devices do not have an IP address. The test prints MAC, name (if advertised), RSSI and an approximate distance.
- The distance uses the log-distance path loss model with default values (`RSSI_AT_1M = -59`, `PATH_LOSS_N = 2.5`). It is approximate and still needs calibration in the real environment.
- Many modern phones randomize their MAC address, so the same device may appear with different addresses.
- The BLE library uses about 90% of the default flash. If we add Wi-Fi and MQTT, we will need a bigger partition table.

## Uploading code to the ESP32

If the upload hangs on `Connecting......`, the board is not in download mode. Do this:

1. Click Upload (the arrow icon in PlatformIO's bottom status bar, or the right-arrow button in Arduino IDE).
2. When `Connecting......` appears, press and hold the `BOOT` button on the ESP32.
3. While holding `BOOT`, press and release the `EN` (reset) button.
4. Release `BOOT` once the upload starts (you will see `Writing at 0x...`).

Notes:
- Use a USB cable that supports data, not a charge-only cable.
- Close the Serial Monitor before uploading, because it can block the port.
