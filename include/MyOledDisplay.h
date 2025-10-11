/**
 * MyOledDisplay.h
 * Benjamin Hartmann | 10/2025
 */

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>

#include "MyLogos.h"
#include "MyWifi.h"
#include "MyTime.h"
#include "MySensor.h"

#ifndef _MY_OLED_DISPLAY_H
#define _MY_OLED_DISPLAY_H

// Possible Libraries:
// - Adafruit libraries for SH1106 -> Adafruit_SH110X & Adafruit_GFX libraries
// - U8g2 library for SH1106

// OLED display
#define OLED_DISPLAY_ADDRESS 0x3C // OLED I2C address. Common values are 0x3C and 0x3D
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // You can set an oled reset pin if desired
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// My BME280: 0x76
// My OLED:   0x3C (SH1106)

/**
 * Print the I2C addresses of connected devices to the Serial Monitor.
 * May only work with one device connected at a time.
 */
void printI2CScanner() {
  Serial.println("I2C Scanner");

  Wire.begin();

  byte count = 0;

  for (byte i = 1; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.printf("- Found address: %d (0x%02X)\n", i, i);
      count++;
      delay(1);
    }
  }

  Serial.printf("Done. Found %d device(s).\n", count);
}

/**
 * Initialize the OLED display.
 */
void initOledDisplay() {
  display.begin(OLED_DISPLAY_ADDRESS, true);

  // display.setContrast(0); // dim display

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
}

/**
 * Display current SSID and IP address on the OLED display.
 */
void displayWiFiInfo() {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  if (WiFi.status() != WL_CONNECTED) {
    display.println("WiFi Info:");
    display.println("----------");
    display.println("Connecting...");
  } else {
    display.println("WiFi Info:");
    display.println("----------");
    display.print("SSID: ");
    display.println(WiFi.SSID());
    display.print("IP: ");
    display.println(WiFi.localIP().toString().c_str());
  }

  display.display();
}

/**
 * Display current time on the OLED display.
 */
void displayTime() {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  display.println("Current Time:");
  display.println("-------------");
  display.println(getLocalTimeString());

  display.display();
}

/**
 * Display BME280 sensor values on the OLED display.
 */
void displaySensorValues(Adafruit_BME280 &bme) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  display.println("Sensor Values:");
  display.println("--------------");

  display.print("Temp: ");
  display.print(bme.readTemperature());
  display.print(' ');
  display.print((char)247); // degree symbol 
  display.println('C');

  display.print("Pres: ");
  display.print(bme.readPressure() / 100.0F);
  display.println(" hPa");

  display.print("Hum:  ");
  display.print(bme.readHumidity());
  display.println(" %");

  display.print("Alt:  ");
  display.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  display.println(" m");

  display.display();
}

#endif  // _MY_OLED_DISPLAY_H_
