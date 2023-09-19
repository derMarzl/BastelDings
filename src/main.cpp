#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);


#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Adafruit_BME280 bme; // I2C

#define LED_PIN 2
float Temperatur;
float Feuchte;
float Druck;

void LEDan() {
  //digitalWrite(BUILTIN_LED, LOW);
  digitalWrite(LED_PIN, LOW);
}

void LEDaus() {
  //digitalWrite(BUILTIN_LED, HIGH);
  digitalWrite(LED_PIN, HIGH);
}

void setup()   {
  pinMode(LED_PIN, OUTPUT);
  LEDan();
  Serial.begin(115200);
  
  //digitalWrite(BUILTIN_LED, LOW); // einschlaten .... ist invertiert
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48) 3C 3D
  display.display();
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Marcels");
  display.println("Wetter-");
  display.println("Station");
  display.println("");
  display.println("BME280");
  display.display();
  delay(4000);

  unsigned status;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("init");
  display.display();

  status = bme.begin(0x76, &Wire); // 0x76 nicht 0x77
  if (!status) {
    status = bme.begin(0x77, &Wire); // 0x76 nicht 0x77
  }
  if (!status) {
    display.println("no Sensor");
    display.display();
  }
  display.println("SensorID=");
  display.print("0x");
  display.print(bme.sensorID(),16);
  display.display();
  delay(2000);
  LEDaus();
}

void printValues() {
  Temperatur = bme.readTemperature();
  Feuchte = bme.readHumidity(); // readTemperature in der Funktion auskommentieren
  Druck = bme.readPressure(); // readTemperature in der Funktion auskommentieren
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(Temperatur,1);
  display.println("  C");
  display.println();
  display.print(Feuchte,1);
  display.println("  % rF");
  display.println();
  display.print(Druck / 100.0F,1);
  display.println(" hPa");
  display.display();
}

void loop() {
  LEDan();
  printValues();
  //delay(10);
  LEDaus();
  delay(30000);
}