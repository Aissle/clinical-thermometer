//A clinical thermometer build using an Arduino uno, a LCD with and I2C, and a Thermistor

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Common I2C LCD addresses are 0x27 or 0x3F - run an I2C scanner sketch if unsure
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int thermistorPin = A0;
const float R_FIXED = 10030.0;   // your fixed resistor value
const float R0 = 10000.0;        // thermistor resistance at 25C
const float T0 = 298.15;         // 25C in Kelvin
const float BETA = 3950.0;       // check your thermistor's datasheet

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Clinical Temp"); delay(5000);
}

float readTemperatureC() {
  int adcValue = analogRead(thermistorPin);
  float resistance = R_FIXED * adcValue / (1023.0 - adcValue);
  //float resistance = R_FIXED * (1023.0 / adcValue - 1.0);
  float tempK = 1.0 / (1.0 / T0 + log(resistance / R0) / BETA);
  return tempK - 273.15;
}

void loop() {
  float tempC = readTemperatureC();

  // For calibration/monitoring via Serial Plotter
  Serial.println(tempC);

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print(" C   ");  // trailing spaces clear leftover digits

  delay(500);
}