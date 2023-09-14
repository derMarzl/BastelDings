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

void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)


  display.display();
  //delay(2000);

  display.clearDisplay();



  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Marcels");
  display.println("Wetter-");
  display.println("Station");
  display.display();
  delay(3000);




  unsigned status;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("init");
  display.display();
  // default settings
  //status = bme.begin();
  status = bme.begin(0x76, &Wire); // nicht 0x77

    if (!status) {
      display.println("no Sensor");
      display.display();
    }
    display.print(bme.sensorID(),16);
    display.display();
    delay(2000);
}

void printValues() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(bme.readTemperature(),1);
  display.println("  C");
  display.println();
  display.print(bme.readHumidity(),1);
  display.println("  % rF");
  display.println();
  display.print(bme.readPressure() / 100.0F,1);
  display.println(" hPa");

  display.display();
}


void loop() {
  printValues();
  delay(5000);
}