/**
 * MyWifi.h
 * Benjamin Hartmann | 10/2025
 */

#ifndef _MY_WIFI_H_
#define _MY_WIFI_H_

#include <ESP8266WiFi.h>
#include "WifiCredentials.h"

/**
 * Connect to a WiFi network using the predefined credentials from ``WifiCredentials.h``.
 */
void connectToWiFi() {
  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" - Connected to WiFi!");
}

/**
 * Get the current WiFi connection status.
 * @return true if connected, false otherwise
 */
bool getWifiConnectedState() {
  return WiFi.status() == WL_CONNECTED;
}

/**
 * Get the current WiFi SSID.
 * @return The SSID of the connected WiFi network.
 */
String getWifiSSID() {
  return WiFi.SSID();
}

/**
 * Get the current WiFi IP address.
 * @return The IP address of the connected WiFi network.
 */
String getWifiIP() {
  return WiFi.localIP().toString();
}

#endif  // _MY_WIFI_H_
