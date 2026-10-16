/*!
 * @file SAMD21_I2C_HTTP.ino
 * @brief SAMD21-compatible I2C HTTP demo for DFRobot WiFi IoT Module
 * @n Connect the module via I2C (SDA/SCL) and use HTTP GET/POST.
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

// HTTP
const char *HTTP_SERVER = "maker.ifttt.com";
const char *GET_URL     = "/trigger/Your_Event/key/Your_Key";
const char *POST_URL    = "/trigger/Your_Event/key/Your_Key";
const char *POST_DATA   = "value1=Hello&value2=from&value3=SAMD21";

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

  // Init HTTP
  while (IOT.HTTPBegin(HTTP_SERVER) != 0) {
    Serial.println("HTTP server empty!");
    delay(100);
  }
  Serial.println("HTTP configured");
}

void loop() {
  // HTTP GET
  String getResp = IOT.HTTPGet(GET_URL);
  Serial.println("GET response: " + getResp);

  // HTTP POST
  String postResp = IOT.HTTPPost(POST_URL, POST_DATA);
  Serial.println("POST response: " + postResp);

  delay(5000);
}