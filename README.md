# Thermistor LCD Thermometer

This repository contains a simple clinical-style thermometer build using a thermistor and a 16x2 I2C LCD. It includes three sketch variants:

- An Arduino Uno version that prints the temperature locally on the LCD and Serial Monitor.
- An ESP32 version that joins an existing Wi-Fi network and serves the temperature over a small web page.
- An ESP32 access point version that creates its own Wi-Fi hotspot and serves the temperature page directly.

All three sketches use the same basic thermistor conversion approach based on the Beta equation.

## Project Layout

- `arduino_thermometer/` - Arduino Uno sketch
- `esp32_thermometer/` - ESP32 sketch for connecting to an existing Wi-Fi network
- `esp32_hostspot_sending_themometer/` - ESP32 sketch that runs as a Wi-Fi access point

## Hardware

Typical parts used in this build:

- Thermistor, 10k class
- Fixed resistor, 10k class, used as the voltage divider partner
- 16x2 LCD with I2C backpack
- Arduino Uno or ESP32 development board
- Breadboard and jumper wires

## Wiring

The exact wiring depends on the board, but the sketches are written for these connections:

### Arduino Uno

- Thermistor divider output to analog pin A0
- LCD SDA to A4
- LCD SCL to A5
- LCD VCC to 5V
- LCD GND to GND

### ESP32

- Thermistor divider output to GPIO 34
- LCD SDA to GPIO 21
- LCD SCL to GPIO 22
- LCD VCC to 3.3V or 5V depending on the LCD backpack and board compatibility
- LCD GND to GND

## How It Works

Each sketch reads the ADC value from the thermistor divider, converts that reading to resistance, then calculates temperature in Celsius using the thermistor Beta formula. A calibration offset is applied in the ESP32 sketches to fine-tune the reading.

The LCD shows the live temperature locally. The ESP32 sketches also expose a web page with a live-updating temperature readout at `/` and a plain text endpoint at `/temp`.

## Getting Started

1. Open the sketch you want to use in the Arduino IDE or PlatformIO.
2. Install the required libraries:
	- `LiquidCrystal_I2C`
	- `Wire`
	- `WiFi` and `WebServer` for the ESP32 sketches
3. Select the correct board and serial port.
4. Update the calibration values if needed.
5. Upload the sketch to your board.

## ESP32 Network Modes

### `esp32_thermometer`

This sketch connects the ESP32 to an existing Wi-Fi network. After upload, check the Serial Monitor for the IP address, then open that address in a browser.

### `esp32_hostspot_sending_themometer`

This sketch creates a Wi-Fi access point named `Thermometer`. Connect to that network, then open the printed IP address in a browser.

## Calibration Notes

The conversion depends on the thermistor and resistor values being close to the values used in the code. If your readings are consistently high or low, adjust:

- `R_FIXED` to match the actual fixed resistor
- `R0` and `BETA` to match your thermistor datasheet
- `CALIBRATION_OFFSET` to fine-tune the final display

## Web Interface

The ESP32 sketches serve a minimal status page that refreshes the temperature every second. The temperature is available from:

- `/` - HTML dashboard
- `/temp` - plain text temperature value

## Notes

- The Arduino sketch uses a 10-bit ADC range, while the ESP32 sketches use a 12-bit ADC range.
- If your LCD shows nothing, verify the I2C address. The code currently uses `0x27`.
- If the display looks scrambled or blank, confirm the LCD backpack voltage requirements before powering it from 3.3V.

