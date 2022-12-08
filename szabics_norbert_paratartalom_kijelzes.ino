#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
#define DHTPIN D4
#define DHTTYPE DHT11
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() 
{
  Serial.begin(9600);
  Serial.println("Indítás!");
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(0.2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
  delay(2000);
  display.clearDisplay();
}
 
void loop() 
{
  delay(1500);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
 
  if (isnan(humidity) || isnan(temperature)) 
  {
    Serial.println("Nem sikerült adatot beolvasni!");
    return;
  }
  display.setCursor(0,0);
  display.println("Humidity:");
  display.print(humidity, 1);
  display.println("%");

  if(humidity <= 45) {
      display.println("Alacsony");
      display.println("A P'ra");
      display.println("Tartalom");
  } else if (humidity >= 50){
      display.println("Kapcsolja be");
      display.println("a pa'ra");
      display.println("g'pet");
  } else {
      display.println("");
      display.println("Temperature:");
      display.print(temperature, 1);
      display.print("C");    
  }

  display.display();
  delay(1500);
  display.clearDisplay();

 
  //Logolás a Serial monitorra
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" % --- ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
}
