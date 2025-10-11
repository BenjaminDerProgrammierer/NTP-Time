#include <Arduino.h>

#include "MyOledDisplay.h"
#include "MyWifi.h"
#include "MyTime.h"
#include "MySensor.h"

int displayState = 0;

unsigned long lastTimeUpdate = 0;
#define UPDATE_INTERVAL 3000 // Update time every 3 seconds

void setup() {
    Serial.begin(115200);
    Serial.println();

    printI2CScanner();
    initOledDisplay();
    displayWiFiInfo();
    connectToWiFi();
    initTime();
    initBME280();
}

void loop() {
    switch (displayState) {
        case 0:
            displayWiFiInfo();
            break;
        case 1:
            displayTime();
            break;
        case 2:
            displaySensorValues(bme);
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
        // Also print Status
        printSensorValues();
        Serial.println(getLocalTimeString());
    }
}

