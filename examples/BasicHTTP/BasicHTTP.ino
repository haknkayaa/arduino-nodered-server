#include <noderedServer.h>

String wifiSSID   = "your-wifi-ssid";
String wifiPASS   = "your-wifi-pass";
String host       = "your-host";
String deviceName = "nodemcu";


NodeRedServer server(wifiSSID, wifiPASS, host, deviceName);

int buttonPressed = 0;

void setup() {
  server.begin();
}

void loop() {

  int buttonValue = digitalRead(D1);

  if(buttonValue == 1){
    if(buttonPressed == 0){
      delay(40);
      buttonPressed = 1;
    }
  }

  else{
    if(buttonPressed == 1){
      buttonPressed = 0;
      server.sendMessage("example","bardak", "100");
    }
  }




}
