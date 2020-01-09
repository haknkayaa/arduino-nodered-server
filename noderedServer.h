#ifndef NODEREDSERVER_H
#define NODEREDSERVER_H

#include <Arduino.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>

//WiFiClient client;
//HTTPClient http;



class NodeRedServer{

  public:
 
    
    NodeRedServer(String ssid, String pass, String host, String deviceName);
    
    void begin();
    
    void setDigital(int pin, int value);
    int readDigital(int pin);
    void setAnalog(int pin, int value);
    int readAnalog(int pin);
    void sendMessage(String type, String variable, String value);

  private:
    String ssid;
    String pass;
    String host;
    String deviceName;

};

#endif
