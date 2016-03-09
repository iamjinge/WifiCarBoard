#include "Arduino.h"
#ifndef FILE_DataCenter
#include "DataCenter.h"
#endif

namespace GetAim {
int startTime;

void setup() {
  Serial.begin(9600);
};

void loop() {
  int now = millis();
  if (now - startTime >= 50) {
    Serial.println(DataCenter::aimAngle);
    Serial.println(DataCenter::aimDistance);
    startTime = now;
    SocketInit::getAim();
  } else {
  }
};
}
