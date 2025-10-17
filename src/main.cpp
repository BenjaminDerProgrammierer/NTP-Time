#include <Arduino.h>

#include "MyOledDisplay.h"
#include "MyWifi.h"
#include "MyTime.h"
#include "MySensor.h"
#include "MyMqtt.h"

int displayState = 0;

unsigned long lastTimeUpdate = 0;
#define UPDATE_INTERVAL 3000 // Update time every 3 seconds

static unsigned long lastMqttPublish = 0;
#define PUBLISH_INTERVAL 1000 // Publish MQTT data every second

void setup() {
    Serial.begin(115200);
    Serial.println();

    printI2CScanner();
    initOledDisplay();
    displayWiFiInfo();
    connectToWiFi();
    initTime();
    initBME280();
    initMqtt();
}

void loop() {
    switch (displayState) {
        case 0:
            displayWiFiInfo(getWifiConnectedState(), getWifiSSID(), getWifiIP());
            break;
        case 1:
            displayTime(getLocalTimeString());
            break;
        case 2:
            displaySensorValues(
                bme.readTemperature(),
                bme.readHumidity(),
                bme.readPressure() / 100.0F,
                bme.readAltitude(SEALEVELPRESSURE_HPA)
            );
            break;
        default:
            displayState = 0;
            break;
    }

    if (millis() - lastTimeUpdate >= UPDATE_INTERVAL) {
        lastTimeUpdate = millis();
        Serial.print(displayState);
        Serial.print(" -> ");
        displayState = (displayState + 1) % 3; // Toggle display state
        Serial.println(displayState);
    }

    loopMqtt();

    if (millis() - lastMqttPublish >= PUBLISH_INTERVAL) {
        lastMqttPublish = millis();
        String temperature = String(bme.readTemperature());
        String humidity = String(bme.readHumidity());
        String pressure = String(bme.readPressure() / 100.0F);
        String altitude = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
        publishSensorData(temperature, humidity, pressure, altitude);
        publishTimeStamp(getLocalTimeString());
    }
}
