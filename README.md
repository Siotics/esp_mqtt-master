# ESP8266 MQTT Client Documentation

This documentation provides an overview and explanation of the ESP8266 MQTT client code.

## Prerequisites

To use this code, you need to have the following:

- Arduino IDE with ESP8266 board support installed.
- Wi-Fi network credentials (SSID and password).
- MQTT broker/server address and port.
- `ESP8266WiFi` library installed.
- `PubSubClient` library installed.

## Code Overview

The code establishes a connection between an ESP8266 module and an MQTT broker, and publishes the chip ID to a specified topic.

### Importing Libraries

The required libraries, `ESP8266WiFi` and `PubSubClient`, are imported.

```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
```
### Wi-Fi and MQTT Configuration

The Wi-Fi credentials, MQTT server address, port, and topic are defined.

```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqttServer = "192.168.100.11";
const int mqttPort = 1883;
const char* mqttTopic = "esp/init";
```

### Initializing Objects

The code initializes the `WiFiClient` and `PubSubClient` objects.
```cpp
WiFiClient espClient;
PubSubClient client(espClient);
```
### Setup Function
The setup() function is executed once at the beginning. It connects to the Wi-Fi network, sets up the MQTT server and port, connects to the MQTT broker, and publishes the chip ID to the specified topic.

```cpp
void setup() {
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Set up MQTT server and port
  client.setServer(mqttServer, mqttPort);

  // Connect to MQTT broker
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, retrying in 5 seconds...");
      delay(5000);
    }
  }

  // Get and publish chip ID
  char chipId[12];
  sprintf(chipId, "%06X", ESP.getChipId());
  client.publish(mqttTopic, chipId);
}
```

### Loop Function

The loop() function runs repeatedly after the setup() function. It calls the client.loop() method to maintain the MQTT connection.

```cpp
void loop() {
  // Maintain MQTT connection
  client.loop();
}
```

### Usage

To use this code:
<ol>
  <li>Set the ssid and password variables to your Wi-Fi network credentials.</li>
  <li>Set the mqttServer and mqttPort variables to the MQTT broker/server address and port.</li>
  <li>Compile and upload the code to your ESP8266 module using the Arduino IDE.</li>
  <li>Open the serial monitor to view the status messages.</li>
  <li>The ESP8266 module will connect to the Wi-Fi network and MQTT broker, and publish the chip ID to the specified topic.</li>
</ol> 
    
Note: Make sure to install the required libraries and set the correct values for Wi-Fi, MQTT, and topic configurations.

> IMPORTANT: Replace "YOUR_SSID", "YOUR_PASSWORD", and "192.168.100.11" with your own values.

