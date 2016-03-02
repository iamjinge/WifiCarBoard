#include "ModeWall.h"

int switchPin = 25;
int mode = 2;    //贴墙模式
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //调试用串口
  pinMode(switchPin, INPUT_PULLUP);
  Motion::motionSetup();
  ModeWall::modeSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
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
