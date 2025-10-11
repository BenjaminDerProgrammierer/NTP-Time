/**
 * MyTime.h
 * Benjamin Hartmann | 10/2025
 */

#include <Arduino.h>
#include <time.h>

#ifndef _MY_TIME_H_
#define _MY_TIME_H_

#define MY_TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3"  // Europe/Vienna

/**
 * Get the current local time as a formatted string.
 * @returns A string representing the current local time.
 */
String getLocalTimeString() {
  String timeStr;

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Failed to obtain time";
  }

  char buf[64];
  if (strftime(buf, sizeof(buf), "%A, %B %d %Y %H:%M:%S (zone %Z %z)",
               &timeinfo)) {
    timeStr = String(buf);
  } else {
    return "Failed to format time";
  }
  return timeStr;
}

/**
 * Initialize time using an NTP server and set timezone.
 */
void initTime() {
  struct tm timeinfo;

  configTime(0, 0, "pool.ntp.org");

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  setenv("TZ", MY_TIMEZONE, 1);
  tzset();

  Serial.printf("Time initialized: %s\n", getLocalTimeString().c_str());
}

#endif  // _MY_TIME_H_