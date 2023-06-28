#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqttServer = "192.168.100.11";
const int mqttPort = 1883;
const char* mqttTopic = "esp/init";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  char response[length + 1];
  memcpy(response, payload, length);
  response[length] = '\0';
  Serial.println(response);
  Serial.println(topic);
}

void setup() {
  // Menghubungkan ke jaringan Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Mengatur server dan port MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);


  // Menghubungkan ke broker MQTT
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, retrying in 5 seconds...");
      delay(5000);
    }
  }

  // Mengambil dan mempublikasikan ID chip
  char chipId[12];
  sprintf(chipId, "%06X", ESP.getChipId());
  String chipIdStr = chipId;
  String msg = "{\"espId\":\"" + chipIdStr + "\"}";
  client.publish(mqttTopic, msg.c_str());

  //Subcribe ke URI Chip
  String topic = "esp/" + String(chipId) + "/response";
  client.subscribe(topic.c_str());
}

void loop() {
  // Tetapkan waktu tunggu jika diperlukan
    client.loop();
}
