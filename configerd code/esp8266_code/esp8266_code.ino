
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "SLT-LTE-WIFI"; // Enter your WiFi name
const char* password =  "rrba671aj6b"; // Enter WiFi password

const char* mqttServer = "tailor.cloudmqtt.com"; //soldier.cloudmqtt.com
const int mqttPort = 14183;
const char* mqttUser = "ileliujf";
const char* mqttPassword = "or_W8gVd5_XD";

WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(9600); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
}
 
void loop() {
  //client.loop();

 while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }


 char data[30];
 String datastr;
 if(Serial.available()>0)    //Checks is there any data in buffer 
  {
    datastr = Serial.readString();
    Serial.println(datastr);
    datastr.toCharArray(data,30); 
    Serial.println(data);
    
    client.publish("data", data ); //Topic, data

  }else
  {
    client.publish("data", "Data not received" ); 
    delay(1000);
    }
  // data[] = "                             ";
  
}
