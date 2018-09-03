#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//wifi config
const char* ssid = "Dong_Wifi";
const char* password = "11235813";
// MQTT config
const char* mqttServer = "192.168.1.107";
const int mqttPort = 1883;
const char* mqttUserName = "MathewTung";
const char* mqttPwd = "aA11235813";

// NEEDS TO BE CHANGED!!!!
const char* clientID = "DinningRoom_Light_ESP";
const char* sub_topic= "myhouse/out/DinningRoom_Light/command";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect(){
  while (!client.connected()){
    if (client.connect(clientID, mqttUserName, mqttPwd)){
      Serial.println("Mqtt connected.");
      client.subscribe(sub_topic);
    } else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 2 secs.");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  Serial.println("GPIO setup..");

  // Setting up wifi connection.
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Connecting to Wifi..");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  // Print the IP address
  Serial.println(WiFi.localIP());

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUserName, mqttPwd )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  //client.publish("myhouse/Bedroom_Light/status", "Hello from esp...");
  client.subscribe(sub_topic);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  Serial.print((char)payload[0]);

  if ((char)payload[0] == '0'){
    digitalWrite(2, LOW);
  } else{
    digitalWrite(2, HIGH);
  }
  Serial.println();
  Serial.println("-----------------------");
 
}

void loop() {
  // Check if a client has connected
  if (!client.connected()){
    reconnect();
  }
  client.loop();
}
