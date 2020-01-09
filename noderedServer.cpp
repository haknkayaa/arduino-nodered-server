#include "noderedServer.h"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient http;

NodeRedServer::NodeRedServer(String ssid, String pass, String host, String deviceName) {
  this->ssid = ssid;
  this->pass = pass;
  this->host = host;
  this->deviceName = deviceName;

}
void wifiConnect(String ssid, String pass, String deviceName) {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(deviceName);
  Serial.println(" WiFi'a baglandi.");
}
void NodeRedServer::begin() {
  Serial.println("BEGIN");
  wifiConnect(ssid, pass, deviceName);
}

void NodeRedServer::setDigital(int pin, int value) {

  String address = "http://" + host + "/device/" + deviceName + "/pin/" + pin + "/value/" + value;

  http.begin(address);
  http.addHeader("Content-Type", "text/plain");

  http.GET();

  http.end();


}

int NodeRedServer::readDigital(int pin) {

  String address = "http://" + host + "/device/" + deviceName + "/pin/" + pin;

  http.begin(address);
  http.addHeader("Content-Type", "text/plain");

  http.GET();

  int value = http.getString().toInt();

  http.end();

  return value;
}

void NodeRedServer::setAnalog(int pin, int value) {

  String address = "http://" + host + "/device/" + deviceName + "/pin/" + pin + "/value/" + value;

  http.begin(address);
  http.addHeader("Content-Type", "text/plain");

  http.GET();

  http.end();
}

int NodeRedServer::readAnalog(int pin) {

  String address = "http://" + host + "/device/" + deviceName + "/pin/" + pin;

  http.begin(address);
  http.addHeader("Content-Type", "text/plain");

  http.GET();

  int value = http.getString().toInt();

  http.end();

  return value;
}

void NodeRedServer::sendMessage(String type, String variable, String value) {
  String url = "http://" + host + "/device/" + deviceName + "/message/";

  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& dataJSON = jsonBuffer.createObject();

  dataJSON["type"]    = type;
  dataJSON["variable"] = variable;
  dataJSON["value"]   = value;

  // JSON serialize
  String data;
  dataJSON.printTo(data);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");


  int httpCode = http.POST(data);

  long currentTime = millis();
  while(httpCode != 200) {
    httpCode = http.POST(data);
    Serial.println("TRY AGAIN");
    if(httpCode == 200){
      Serial.println("SUCCESS");
      break;
    }
    else if(millis()-currentTime>2000){
      Serial.println("TIMEDOUT");
      break;
    }
  }
}
