/**
 * MyMqtt.h
 * Benjamin Hartmann | 10/2025
 */

#ifndef _MY_MQTT_H_
#define _MY_MQTT_H_

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MqttCredentials.h"

// MQTT Topics and Settings
#define MQTT_ALL_TOPICS "My_SmartHome/Benjamin/#"  // alle Topic subscribe

#define MQTT_LWT_TOPIC "My_SmartHome/Benjamin/WifiStatus"  // Last Will & Testament
#define MQTT_DEVICE_NAME_TOPIC "My_SmartHome/Benjamin/DeviceName"
#define MQTT_DEVICE_PLACE_TOPIC "My_SmartHome/Benjamin/DevicePlace"
#define MQTT_WIFI_SSID_TOPIC "My_SmartHome/Benjamin/WiFi_SSID"
#define MQTT_WIFI_IP_TOPIC "My_SmartHome/Benjamin/WiFi_IP"

#define MQTT_TIMESTAMP_TOPIC "My_SmartHome/Benjamin/TimeStamp"
#define MQTT_DEBUG_TOPIC "My_SmartHome/Benjamin/Debug_Info"

#define MQTT_BME280_TEMPERATURE_TOPIC "My_SmartHome/Benjamin/BME280_Temperature_°C" // Temperature
#define MQTT_BME280_HUMIDITY_TOPIC "My_SmartHome/Benjamin/BME280_Humidity_%" // Humidity
#define MQTT_BME280_PRESSURE_TOPIC "My_SmartHome/Benjamin/BME280_Pressure_hPa" // Pressure
#define MQTT_BME280_ALTITUDE_TOPIC "My_SmartHome/Benjamin/BME280_Altitude_m" // Altitude

#define DEVICE_NAME "Benjamin's D1 Mini ESP8266"
#define DEVICE_PLACE "Benjamin's Zimmer"

#define QOS 1       // Quality of Service Level
#define RETAIN true // retained message

// Create a unique client ID
String clientId = "ESP-" + String(ESP.getChipId()) + "-" + String(random(0xffff), HEX);

WiFiClient espClient;
PubSubClient client(espClient);

/**
 * Send initial MQTT messages (LWT, device info, WiFi info).
 */
void sendInitMessages() {
  client.publish(MQTT_LWT_TOPIC, "online", RETAIN);
  client.publish(MQTT_DEVICE_NAME_TOPIC, DEVICE_NAME, RETAIN);
  client.publish(MQTT_DEVICE_PLACE_TOPIC, DEVICE_PLACE, RETAIN);
  client.publish(MQTT_WIFI_SSID_TOPIC, WiFi.SSID().c_str(), RETAIN);
  client.publish(MQTT_WIFI_IP_TOPIC, WiFi.localIP().toString().c_str(), RETAIN);
}

/**
 * Connect to the MQTT broker.
 * This function is blocking.
 */
void connect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientId.c_str(), MY_MQTT_USERNAME, MY_MQTT_PASSWORD, MQTT_LWT_TOPIC, QOS, RETAIN, "offline")) {
      Serial.printf(" - Connected to MQTT Broker: %s:%d\n", MY_MQTT_BROKER, MY_MQTT_PORT);

      client.subscribe(MQTT_ALL_TOPICS); // Subscribe to all interesting topics
      sendInitMessages();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**
 * MQTT message callback function.
 */
void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, MQTT_ALL_TOPICS) == 0) { // if topic matches
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  }
}

/**
 * Initialize MQTT client and connect to the broker.
 */
void initMqtt() {
  client.setServer(MY_MQTT_BROKER, MY_MQTT_PORT);
  client.setCallback(callback);

  connect();
}

/**
 * Maintain MQTT connection and process incoming messages.
 */
void loopMqtt() {
  // Ensure the client is connected
  if (!client.connected()) {
    connect();
  }

  // Maintain MQTT connection
  client.loop();
}

/**
 * Publish BME280 sensor data to MQTT topics.
 */
void publishSensorData(String temperature, String humidity, String pressure, String altitude) {
  client.publish(MQTT_BME280_TEMPERATURE_TOPIC, temperature.c_str(), RETAIN);
  client.publish(MQTT_BME280_HUMIDITY_TOPIC, humidity.c_str(), RETAIN);
  client.publish(MQTT_BME280_PRESSURE_TOPIC, pressure.c_str(), RETAIN);
  client.publish(MQTT_BME280_ALTITUDE_TOPIC, altitude.c_str(), RETAIN);
}

/**
 * Publish current time to MQTT topic.
 */
void publishTimeStamp(String timeStamp) {
  client.publish(MQTT_TIMESTAMP_TOPIC, timeStamp.c_str(), RETAIN);
}

#endif  // _MY_MQTT_H_
