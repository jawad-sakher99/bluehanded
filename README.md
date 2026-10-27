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

## Uploading code to the ESP32

If the upload hangs on `Connecting......`, the board is not in download mode. Do this:

1. Click Upload (the arrow icon in PlatformIO's bottom status bar, or the right-arrow button in Arduino IDE).
2. When `Connecting......` appears, press and hold the `BOOT` button on the ESP32.
3. While holding `BOOT`, press and release the `EN` (reset) button.
4. Release `BOOT` once the upload starts (you will see `Writing at 0x...`).

Notes:
- Use a USB cable that supports data, not a charge-only cable.
- Close the Serial Monitor before uploading, because it can block the port.
