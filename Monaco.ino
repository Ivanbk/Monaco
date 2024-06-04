#include <Arduino.h>

//#include "gps.h";
#include "comms.h";
#include "timer.h";
#include "display.h";
#include "control.h";
#include "CAN.h";

void setup() {
  Serial.begin(115200);
  //display_init();
  initComms();
  setupTimer(1500000);
}

void loop() {


  if(timer_fired){
    Serial.println("Timer fired");
    timer_fired = false;
    getGPS();
    sendToServer();
    //lcd.print("Lat: ");
    //lcd.setCursor(4, 0);
    //lcd.print(latitude, 6);
    //lcd.setCursor(0, 1);
    //lcd.print("Long: ");
    //lcd.setCursor(6, 1);
    //lcd.print(longitude, 6);
  }

  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  while (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
