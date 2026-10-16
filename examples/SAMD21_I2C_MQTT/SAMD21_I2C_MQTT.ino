/*!
 * @file SAMD21_I2C_MQTT.ino
 * @brief SAMD21-compatible I2C MQTT demo for DFRobot WiFi IoT Module
 * @n Connect the module via I2C (SDA/SCL) and use MQTT to publish/subscribe.
 * @n This demo works on SAMD21 boards (e.g. Arduino Zero, M0 Pro) without SoftwareSerial.
 *
 * Wiring (I2C):
 *   Module SDA -> Board SDA (e.g. pin 21 on SAMD21)
 *   Module SCL -> Board SCL (e.g. pin 20 on SAMD21)
 *   Module VCC -> 3.3V
 *   Module GND -> GND
 *
 * @copyright    Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence      The MIT License (MIT)
 * @author       [Tang](jie.tang@dfrobot.com)
 * @version      V1.0
 * @date         2020-07-13
 * @get          from https://www.dfrobot.com
 * @url          https://github.com/DFRobot/DFRobot_WiFi_IOT_Module
 */
#include "DFRobot_WiFi_IoT_Module.h"

// I2C mode - default Wire object, works on SAMD21
DFRobot_WiFi_IoT_Module_I2C IOT;

// WiFi
const char *WIFI_SSID     = "YourWiFiName";
const char *WIFI_PASSWORD = "YourWiFiPassword";

// MQTT (Easy IoT)
const char *MQTT_SERVER = "iot.dfrobot.com.cn";
const char *MQTT_PORT   = "1883";
const char *MQTT_ID     = "Your_Device_Name";
const char *MQTT_PWD    = "Your_Device_Secret";
const char *SUB_TOPIC   = "Your_Sub_Topic";
const char *PUB_TOPIC   = "Your_Pub_Topic";
const char *SEND_MSG    = "Hello from SAMD21 I2C";

void callback(const char *topic, const char *message) {
  Serial.println("Receive [" + (String)topic + "], Message: " + (String)message);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for serial monitor (SAMD21)

  // Init I2C
  while (IOT.begin() != 0) {
    Serial.println("I2C init failed, retrying...");
    delay(1000);
  }
  Serial.println("I2C init OK");

  // Connect WiFi
  while (IOT.connectWifi(WIFI_SSID, WIFI_PASSWORD) != 0) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nWiFi connected");

  // Connect MQTT
  while (IOT.MQTTBegin(MQTT_SERVER, MQTT_PORT, MQTT_ID, MQTT_PWD) != 0) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("MQTT connected");

  // Set callback and subscribe
  IOT.setCallBack(callback);
  while (IOT.subscribe(SUB_TOPIC) != 0) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Subscribed to " + (String)SUB_TOPIC);
}

void loop() {
  if (IOT.publish(PUB_TOPIC, SEND_MSG) == 0) {
    IOT.loop();
  } else {
    Serial.println("Publish timeout");
  }
  delay(1000);
}