# Arduino-thermistor-LCD-thermometer
Arduino Clinical Thermometer
A simple, accurate clinical thermometer built using an Arduino Uno, a 16x2 LCD with an I2C interface, and an NTC thermistor using the Steinhart-Hart equation.

Hardware Components
Microcontroller: Arduino Uno (or compatible board)

Display: 16x2 LCD Display with I2C adapter (Default address: 0x27)

Sensor: 10k NTC Thermistor

Resistor: 10kΩ Fixed Resistor (used in a voltage divider circuit)

Miscellaneous: Breadboard and jumper wires

Circuit Wiring
I2C LCD Display
VCC -> Arduino 5V

GND -> Arduino GND

SDA -> Arduino A4 (or dedicated SDA pin)

SCL -> Arduino A5 (or dedicated SCL pin)

Thermistor Voltage Divider
5V -> Thermistor -> Arduino A0 -> 10kΩ Resistor -> GND
(Note: Pin A0 reads the voltage between the thermistor and the fixed resistor).

Software Dependencies
The project requires the following Arduino IDE libraries:

Wire.h (Built-in for I2C communication)

LiquidCrystal_I2C.h (Install via the Arduino Library Manager)

Configuration
Before uploading, check your hardware values and update these constants in the code if necessary:

R_FIXED: The exact measured resistance of your 10kΩ resistor (e.g., 10030.0).

BETA: The Beta coefficient from your thermistor's datasheet (commonly 3950).

LiquidCrystal_I2C lcd(0x27, 16, 2): Change 0x27 to 0x3F if your LCD screen does not clear or display text.

How to Use
Connect the hardware according to the wiring guide.

Open the code in the Arduino IDE.

Install the LiquidCrystal_I2C library.

Upload the sketch to your Arduino board.

The LCD will display "Clinical Temp" for 5 seconds before showing live temperature readings in Celsius.

Open the Serial Plotter (9600 baud) to view real-time temperature graphing.