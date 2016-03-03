#include "Motion.h"
#include "Gyroscope.h"

namespace {
float targetDistance;
float targetAngle;
void modeSetup();
void modeLoop();

float startLeftAngle = 0, startRightAngle = 0,startAngle=0;
float leftAngle = 0, rightAngle = 0,turnAngle=0;

int stateFlag = 0;

unsigned long keepTime

void modeSetup() {
  pinMode(detectLeft, INPUT);
  pinMode(detectRight, INPUT);
  pinMode(detectMid, INPUT);
}

void modeLoop() {
  //do something
    switch (stateFlag) {
      case 0://START_TO_TURN
        if(TARGET){
          stateFlag=01;
          break;
        }
        else{
        Gyroscope::update();
        startLeftAngle = Gyroscope::getAngleZ();
        Motion::turnLeft(150, 0, false, 2);
        stateFlag = 2;
        break;
        }
      case 2:
        Gyroscope::update();
        leftAngle = Gyroscope::getAngleZ() - startLeftAngle;
        leftAngle += leftAngle < -20 ? 360 : 0;
        if (leftAngle > 20) {
          Motion::stop();
          delay(500);
          stateFlag=0;
        }
        case 01:
        if(!TARGET){
          stateFlag=00;
          break;
        }
        else{
          Gyroscope::update();
          startAngle=Gyroscope::getAngleZ();
          if()
        }
    }
}

};
