# ESP8266 with NTP Time Sync and OLED Display

## Parts required

| Part | Description | aprox. cost |
|------|-------------|-------------|
| [D1 Mini NodeMcu mit ESP8266-12F WLAN Modul](https://www.az-delivery.de/products/d1-mini) | ESP8266 based microcontroller | 7€ |
| [1,3 Zoll OLED I2C 128 x 64 Pixel Display](https://www.az-delivery.de/products/1-3zoll-i2c-oled-display) | OLED Display | 9€ |
| [GY-BME280 Sensor](https://www.az-delivery.de/products/gy-bme280) | Temperature, Humidity and Pressure Sensor | 11€ |

Additionally you will need a Breadboard and some jumper wires.

## Wiring

### OLED Display to D1 Mini

| OLED Pin | D1 Mini Pin |
|----------|-------------|
| GND      | G           |
| VCC      | 3V3         |
| SCL      | D1          |
| SDA      | D2          |

### BME280 to D1 Mini

| BME280 Pin | D1 Mini Pin |
|------------|-------------|
| GND        | G           |
| VCC        | 3V3         |
| SCL        | D1          |
| SDA        | D2          |

## Secrets

You'll need to create a `MqttCredentials.h` and `WiFiCredentials.h` file in the `include` folder with the following content:

```cpp
// MqttCredentials.h
#define MY_MQTT_BROKER "test.mosquitto.org"
#define MY_MQTT_PORT 1883
#define MY_MQTT_USERNAME ""
#define MY_MQTT_PASSWORD ""

// WiFiCredentials.h
#define MY_SSID "ssid"
#define MY_PASSWORD "password"
```
