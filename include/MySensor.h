/**
 * MySensor.h
 * Benjamin Hartmann | 10/2025
 */

#ifndef _MY_SENSOR_H_
#define _MY_SENSOR_H_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define MY_BME280_ADDRESS 0x76  // Default I2C address for BME280
Adafruit_BME280 bme;

/**
 * Initialize the BME280 sensor.
 */
void initBME280() {
  if (!bme.begin(MY_BME280_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1); // Loop forever
  }
}

/**
 * Print BME280 sensor values to the Serial Monitor.
 */
void printSensorValues() {
  Serial.printf("BME280 Sensor Values:\n");
  Serial.printf("Temperature = %.2f °C\n", bme.readTemperature());
  Serial.printf("Temperature = %.2f °F\n", 1.8 * bme.readTemperature() + 32);
  Serial.printf("Pressure = %.2f hPa\n", bme.readPressure() / 100.0F);
  Serial.printf("Approx. Altitude = %.2f m\n", bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.printf("Humidity = %.2f %%\n", bme.readHumidity());
  Serial.println();
}

#endif  // _MY_SENSOR_H_
