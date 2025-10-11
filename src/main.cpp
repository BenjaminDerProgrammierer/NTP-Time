#include <Arduino.h>

#include "MyOledDisplay.h"
#include "MyWifi.h"
#include "MyTime.h"

int displayState = 0;

unsigned long lastTimeUpdate = 0;
int timeUpdateInterval = 3000; // Update time every 3 seconds

void setup() {
    Serial.begin(115200);
    Serial.println();

    initOledDisplay();
    displayWiFiInfo();
    connectToWiFi();
    initTime();
}

void loop() {
    switch (displayState) {
        case 0:
            displayWiFiInfo();
            break;
        case 1:
            displayTime();
            break;
        default:
            displayState = 0;
            break;
    }

    if (millis() - lastTimeUpdate >= timeUpdateInterval) {
        lastTimeUpdate = millis();
        displayState = (displayState + 1) % 2; // Toggle display state
    }
}
