#include<SoftwareSerial.h>
#include <ESP8266WiFi.h> 
#include <PubSubClient.h>
#include<ArduinoJson.h>

SoftwareSerial s(D6,D5);		     //serial pins used

const char* ssid = "********";               // wifi ssid
const char* password =  "*********";         // wifi password
const char* mqttServer = "***.***.*.*";      // IP adress Raspberry Pi
const int mqttPort = ****;		     
const char* mqttUser = "********";		     // if you don't have MQTT Username, no need input
const char* mqttPassword = "*********";    // if you don't have MQTT Password, no need input

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(9600);			   //baud rate
  s.begin(9600);

  WiFi.begin(ssid, password);               
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client")) {
      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
  client.subscribe("esp8266");
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------"); 
}

void loop(){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  
  String soil_moist = root["sm"];
  String water_level = root["wl"];
  String n = root["n"];
  String p = root["p"];
  String k = root["k"];

  String s = soil_moist + ":" +  water_level + ":" + n + ":" + p + ":" + k;
  
  const char * msg = s.c_str();
  
  Serial.println("-------------xxx---------------");
  client.publish("esp8266",msg);
  Serial.println("after publish");
}
