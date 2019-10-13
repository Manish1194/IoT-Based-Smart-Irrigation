
#include<SoftwareSerial.h>
#include<ArduinoJson.h>
SoftwareSerial s(5,6);

float soil_moist,water_level;
const int sm_pin = A0;
const int wl_pin = A1;

void setup(){
  Serial.begin(9600);      				//baud rate
  s.begin(9600);
  pinMode(sm_pin,INPUT);
  pinMode(wl_pin,INPUT); 
}

void loop(){
  StaticJsonBuffer<1000> jsonBuffer;		        //Buffer size
  JsonObject& root = jsonBuffer.createObject();
 
  soil_moist = analogRead(sm_pin);
  water_level = analogRead(wl_pin);
  
  root["sm"] = soil_moist;
  root["wl"] = water_level;
  
  root.prettyPrintTo(Serial);
 
  root.printTo(s); 
  delay(10000);						//delay for 10 sec
}
