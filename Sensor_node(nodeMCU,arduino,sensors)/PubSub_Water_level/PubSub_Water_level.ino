#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

int sense_Pin = A0; // sensor input at Analog pin A0
int value = 0;
const char* ssid = "********";                   // wifi ssid
const char* password =  "********";         // wifi password
const char* mqttServer = "**.*.*.***";    // IP adress Raspberry Pi
const int mqttPort = ****;
const char* mqttUser = "********";      // if you don't have MQTT Username, no need input
const char* mqttPassword = "********";  // if you don't have MQTT Password, no need input

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){

  Serial.begin(9600);
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
  client.subscribe("waterlevel");
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

void loop() {
    value= analogRead(sense_Pin);
    value= value/10;
    char s[16];
    client.publish("waterlevel", itoa(value, s, 10));
    delay(15000);
    //client.loop();
}
