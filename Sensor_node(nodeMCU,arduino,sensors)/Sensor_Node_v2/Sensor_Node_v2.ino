#include<SoftwareSerial.h>
#include<ArduinoJson.h>
#include <Wire.h>
#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 2
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];
SoftwareSerial s(5,6);

int soil_moist, water_level, LDR_val; 
float nitrogen, phosphorus, pottasium;
const int sm_pin = A0;
const int wl_pin = A1;
const int NPK = A2;

void setup(){
  Serial.begin(9600);
  s.begin(9600);
  pinMode(NPK,INPUT);
  pinMode(sm_pin,INPUT);
  pinMode(wl_pin,INPUT);
   
  Wire.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop(){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
 
  soil_moist = int(analogRead(sm_pin));
  water_level = int(analogRead(wl_pin));
  
  leds[0] = CRGB::Blue;
  FastLED.show();
  LDR_val = analogRead(NPK);
  nitrogen = LDR_val/204.6;
  delay(1000);

  leds[0] = CRGB::Green;
  FastLED.show();
  LDR_val = analogRead(NPK);
  phosphorus = LDR_val/204.6;
  delay(1000);

  leds[0] = CRGB::Red;
  FastLED.show();
  LDR_val = analogRead(NPK);
  pottasium = LDR_val/204.6;
  delay(1000);

  root["sm"] = soil_moist;
  root["wl"] = water_level;
  root["n"] = nitrogen;
  root["p"] = phosphorus;
  root["k"] = pottasium;
  
  root.prettyPrintTo(Serial);
  root.printTo(s);
  delay(17000);
}
