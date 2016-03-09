#include "Gyroscope.h"
void setup() {
  // put your setup code here, to run once:
  Gyroscope::gyroscopeSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  int now = millis();
  Gyroscope::update();
  float angleZ = Gyroscope::getAngleZ();
  Serial.print(now);
  Serial.print("  ");
  Serial.println(angleZ);
}
