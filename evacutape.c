#include <dht.h>
#include <FastLED.h>
#include <Wire.h>
#include "MPU9250.h"
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);

dht DHT;
int led = 13;
#define  DHT11_PIN 7
const int gasPin = A2;
#define LED_PIN     13
#define NUM_LEDS    40
CRGB leds[NUM_LEDS];
int i = 0;


unsigned long lastFrame = 0;
int frameRate = 100;
int chk = DHT.read11(DHT11_PIN); 
unsigned int sensorValue = analogRead(gasPin); 
unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); 
Serial.println(DHT.temperature);


void setup(){
  pinMode(led,OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(2000);   
  Serial.begin(9600);
}
void loop() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  display.setTextSize(1.9);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Temp:");
  display.println(DHT.temperature);

  display.setTextSize(1.9);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("PPM:");
  display.println(outputValue);
  

  display.display();

  delay(5000);
  if(DHT.temperature >= 10 && outputValue >= 10) {
  
    for (i = 0; i <= 30; i = i + 2) {
     leds[i] = CRGB(255, 0, 0); 
    FastLED.show();
    delay(100);
    }
    delay(100);
    for (i = 0; i <= 30; i = i + 2) {
     leds[i] = CRGB(255, 0, 0); 
    FastLED.clear(); 
      
    }
}



  
}
