#include "ModeWall.h"

int switchPin = 25;
int mode = 2;    //贴墙模式
void setup() {
  Serial.begin(9600);  //调试用串口
  pinMode(switchPin, INPUT_PULLUP);
  Motion::motionSetup();
  ModeWall::modeSetup();
  Gyroscope::gyroscopeSetup();
  Ultrasonic::ultrasonicSetup();
}

void loop() {
  if (!digitalRead(switchPin)) {
    switch (mode) {
      case 2:
        ModeWall::modeLoop();
    }
  }
  else {
    Motion::motionStop();
  }
}
