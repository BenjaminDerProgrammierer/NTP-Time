/**
 * MySensor.h
 * Benjamin Hartmann | 10/2025
 */
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#ifndef _MY_SENSOR_H_
#define _MY_SENSOR_H_

#define MY_BME280_ADDRESS 0x76  // Default I2C address for BME280
Adafruit_BME280 bme;

void initBME280() {
  if (!bme.begin(MY_BME280_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1); // Loop forever
  }
}

void printSensorValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
  
  // Convert temperature to Fahrenheit
  Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" °F");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

#endif  // _MY_SENSOR_H_
