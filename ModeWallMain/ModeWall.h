#include "Arduino.h"
#include"Motion.h"
#include "Gyroscope.h"

namespace ModeWall {
int detectLeft = 22;    //左侧红外避障模块检测
int detectRight = 23;  //右侧红外避障模块检测
int detectMid = 24;    //中间红外避障模块检测

int forwardPWM = 150;
int backwardPWM = 150;
int turnLeftPWM = 150;
int turnRightPWM = 150;

int stateFlag = 0000;
unsigned long keepForwardTime = 0, keepBackTime = 0;
unsigned long keepLeftTime = 0, keepRightTime = 0;
float startLeftAngle = 0, startRightAngle = 0;
float leftAngle = 0, rightAngle = 0;

bool mid = !digitalRead(detectMid);
bool left = !digitalRead(detectLeft);
bool right = !digitalRead(detectRight);

void modeSetup() {
  pinMode(detectLeft, INPUT);
  pinMode(detectRight, INPUT);
  pinMode(detectMid, INPUT);
}

void modeLoop() {
  mid = !digitalRead(detectMid);
  left = !digitalRead(detectLeft);
  right = !digitalRead(detectRight);
  switch (stateFlag) {
    case 0000:                          //丢失目标or初始
      Motion::forward(forwardPWM);
      if (!(mid || left || right)) {
        break;
      }
      else if (right) {
        stateFlag = 1100;    //左贴墙模式
        break;
      }
      else {
        stateFlag = 0100;   //右贴墙模式
        break;
      }
    case 0100:                           //左贴墙壁模式，仅做state判断
      if (left && (!right)) {
        stateFlag = 0110;   //100 110
        break;
      }
      else if (!(mid || left || right)) {
        stateFlag = 0120;   //000
        break;
      }
      else {
        stateFlag = 0130;   //011 001 111 101 010
        break;
      }
    case 0110:
      Motion::turnRight(turnRightPWM,0,false,1);
      stateFlag = 0100;
      break;
    case 0120:
      Motion::forward(forwardPWM);
      keepForwardTime = millis() + 1000;
      stateFlag = 0121;
      break;
    case 0121:
      if (left || mid || right) {
        Motion::motionStop();
        stateFlag = 0100;
        break;
      }
      else {
        if (millis() <= keepForwardTime) {
          break;
        }
        else {
          Gyroscope::update();
          startLeftAngle = Gyroscope::getAngleZ();
          Motion::turnLeft(turnLeftPWM);
          stateFlag = 0122;
          break;
        }
      }
    case 0122:
      if (left || mid || right) {
        Motion::motionStop();
        stateFlag = 0100;
        break;
      }
      else {
        Gyroscope::update();
        leftAngle = Gyroscope::getAngleZ() - startLeftAngle;
        leftAngle += leftAngle < -20 ? 360 : 0;
        Serial.println(leftAngle);
        if (leftAngle <= 120) {
          break;
        }
        else {
          stateFlag = 0000;
//          Serial.println("lose wall");
          break;
        }
      }
    case 0130:
      Motion::backward(backwardPWM);
      keepBackTime = millis() + 400;
      stateFlag = 0131;
      break;
    case 0131:
      if (millis() <= keepBackTime) {
        break;
      }
      else {
        Motion::motionStop();
        Gyroscope::update();
        startRightAngle = Gyroscope::getAngleZ();
        Motion::turnRight(turnRightPWM);
        stateFlag = 0132;
        break;
      }
    case 0132:
      if (left || mid || right) {
        Motion::motionStop();
        stateFlag = 0100;
        break;
      }
      else {
        Gyroscope::update();
        rightAngle = startRightAngle - Gyroscope::getAngleZ() ;
        rightAngle += rightAngle < -20 ? 360 : 0;
        if (rightAngle <= 15) {
          break;
        }
        else {
          Motion::motionStop();
          stateFlag = 0100;
          break;
        }
      }
  }
}
};
