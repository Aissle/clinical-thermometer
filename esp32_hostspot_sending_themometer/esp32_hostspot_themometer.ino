#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
WebServer server(80);

const char* ap_ssid = "Thermometer";
const char* ap_password = "12345678";  // must be at least 8 characters

const int thermistorPin = 34;
const float R_FIXED = 10030.0;
const float R0 = 10000.0;
const float T0_KELVIN = 298.15;
const float BETA = 3950.0;
const float CALIBRATION_OFFSET = -3;

float currentTempC = 0;

float readTemperatureC() {
  int adcValue = analogRead(thermistorPin);
  float resistance = R_FIXED * adcValue / (4095.0 - adcValue);
  float tempK = 1.0 / (1.0 / T0_KELVIN + log(resistance / R0) / BETA);
  return (tempK - 273.15) + CALIBRATION_OFFSET;
}

void handleRoot() {
  String html = "<html><body style='font-family:sans-serif;text-align:center;margin-top:50px'>";
  html += "<h1>Clinical Thermometer</h1>";
  html += "<h2 id='temp' style='font-size:60px'>--</h2>";
  html += "<script>";
  html += "setInterval(function(){";
  html += "fetch('/temp').then(r=>r.text()).then(t=>document.getElementById('temp').innerHTML=t+' &deg;C');";
  html += "}, 1000);";
  html += "</script></body></html>";
  server.send(200, "text/html", html);
}

void handleTemp() {
  server.send(200, "text/plain", String(currentTempC, 1));
}

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  WiFi.softAP(ap_ssid, ap_password);

  IPAddress ip = WiFi.softAPIP();
  Serial.print("Access point started. IP address: ");
  Serial.println(ip);

  lcd.setCursor(0, 0);
  lcd.print(ip);

  server.on("/", handleRoot);
  server.on("/temp", handleTemp);
  server.begin();
}

void loop() {
  server.handleClient();
  currentTempC = readTemperatureC();

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(currentTempC, 1);
  lcd.print(" C   ");

  delay(500);
}