#include <Arduino.h>

//#include "gps.h";
#include "comms.h";
#include "timer.h";

void setup() {
  Serial.begin(115200);
  setupTimer(1500000);
  initComms();

}

void loop() {


  if(timer_fired){
    Serial.println("Timer fired");
    timer_fired = false;
    getGPS();
  }

  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  while (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
