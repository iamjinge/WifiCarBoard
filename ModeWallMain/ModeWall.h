#include "Arduino.h"
#include"Motion.h"
#include "Gyroscope.h"
#include "Ultrasonic.h"

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

float leftDistance0 = 0;
float rightDistance0 = 0;
float leftDistance1 = 0;
float rightDistance1 = 0;

int leftPWM = 150;
int rightPWM = 150;
int deltaPWM = 0;

int PIDInterval = 200; //ms
const float KP = 2, TD = 1, TI = 10;

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
      leftDistance0 = Ultrasonic::getDistance(0);
      if (leftDistance0 > 0 && leftDistance0 < 300) {
        stateFlag = 0100;
        break;
      }
      else {
        rightDistance0 = Ultrasonic::getDistance(1);
        if (rightDistance0 > 0 && rightDistance0 < 300) {
          stateFlag = 1100;
          break;
        }
      }
      if (!(mid || left || right)) {
        break;
      }
      else if (right) {
        stateFlag = 1100;    //右贴墙模式
        break;
      }
      else {
        stateFlag = 0100;   //左贴墙模式
        break;
      }
      
     //left
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
      Motion::turnRight(turnRightPWM, 0, false, 1);
      stateFlag = 0100;
      break;
    case 0120:
      leftDistance0 = Ultrasonic::getDistance(0);
      if (leftDistance0 == -1) {
        Serial.println("error:unable to get distance");
      }
      else if (leftDistance0 == 0 || leftDistance0 > 200) { //TODO目标太远或者丢失
        Gyroscope::update();
        startLeftAngle = Gyroscope::getAngleZ();
        Motion::turnForward(120, 250);                           //TODO丢失找回和大角度转弯
        //        Motion::turnLeft(turnLeftPWM);
        stateFlag = 0122;
        break;
      }
      else {
        if (Motion::motionState != 5) {
          Motion::forward(forwardPWM);
          leftPWM = 150;
          rightPWM = 150;
        }
        else {
          Motion::turnForward(leftPWM, rightPWM);
        }
        keepForwardTime = millis() + PIDInterval;
        stateFlag = 0121;
        break;
      }
      break;
    case 0121:
      if (millis() < keepForwardTime) break;
      else {
        leftDistance1 = Ultrasonic::getDistance(0);
        deltaPWM = KP * (TD * ((leftDistance1 - leftDistance0) * 1000 / PIDInterval) + TI * (leftDistance1 - 100));
        deltaPWM = constrain(deltaPWM, -180, 180);          //TODO PWM调节区间
        leftPWM = 150 - deltaPWM / 2;
        rightPWM = 150 + deltaPWM / 2;
        Serial.print("leftPWM:");
        Serial.println(leftPWM);
        Serial.print("rightPWM:");
        Serial.println(rightPWM);
        Motion::turnForward(leftPWM, rightPWM);
        stateFlag = 0100;
        break;
      }
    case 0122:
      if (Ultrasonic::getDistance > 0) {
        stateFlag = 0120;
        break;
      }
      else {
        if (left || mid || right) {
          stateFlag = 0100;
          break;
        }
        else {
          leftAngle = Gyroscope::getAngleZ() - startLeftAngle;
          leftAngle += leftAngle < -20 ? 360 : 0;
          if (leftAngle < 180)
          {
            break;
          }
          else {
            Serial.println("lose wall");
            stateFlag = 0000;
            break;
          }
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
