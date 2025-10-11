/**
 * MyWifi.h
 * Benjamin Hartmann | 10/2025
 */

#include <ESP8266WiFi.h>

#ifndef _MY_WIFI_H_
#define _MY_WIFI_H_

#include "WifiCredentials.h"

/**
 * Connect to a WiFi network using predefined credentials.
 */
void connectToWiFi() {
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi!");
}

#endif  // _MY_WIFI_H_
