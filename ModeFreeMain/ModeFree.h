#include "Arduino.h"
#include"Motion.h"

namespace ModeFree {
int detectLeft = 22;    //左侧红外避障模块检测
int detectRight = 23;  //右侧红外避障模块检测
int detectMid = 24;    //中间红外避障模块检测

int forwardPWM = 150;
int backwardPWM = 150;
int turnLeftPWM = 150;
int turnRightPWM = 150;

void modeSetup() {
  pinMode(detectLeft, INPUT);
  pinMode(detectRight, INPUT);
  pinMode(detectMid, INPUT);
}

void modeLoop() {
  bool mid = !digitalRead(detectMid);
  bool left = !digitalRead(detectLeft);
  bool right = !digitalRead(detectRight);
  if (mid) {
    Motion::backward(backwardPWM, 500, true);
    //int randomAngle=random()
    Motion::turnLeft(turnLeftPWM, 1500, true);
  }
  else if (!left && !right) {
    
    Motion::forward(forwardPWM);
    //    Motion::forward(forwardPWM,1000);
//    Serial.println("1");
  }
  else if (left && right) {
    Motion::backward(backwardPWM, 500, true);
    //int randomAngle=random()
    Motion::turnLeft(turnLeftPWM, 1500, true);
//    Serial.println("2");
  }
  else if (left) {
    Motion::backward(backwardPWM, 200);
    Motion::turnRight(turnRightPWM, 1000, true);
//    Serial.println("3");
  }
  else {
    Motion::backward(backwardPWM, 200);
    Motion::turnLeft(turnLeftPWM, 1000, true);
//    Serial.println("4");
  }
  //  Serial.print(left);
  //  Serial.print(' ');
  //  Serial.println(right);
}
};
