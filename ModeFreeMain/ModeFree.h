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


unsigned long keepTime = 0;

void modeSetup() {
  pinMode(detectLeft, INPUT);
  pinMode(detectRight, INPUT);
  pinMode(detectMid, INPUT);
}

void modeLoop() {
  bool mid = !digitalRead(detectMid);
  bool left = !digitalRead(detectLeft);
  bool right = !digitalRead(detectRight);
  if (mid) {                        //前方检测到障碍物
    Motion::backward(backwardPWM, 500, true);
    //int randomAngle=random()
    Motion::turnLeft(turnLeftPWM);
    keepTime=millis()+1500;         //左转需要持续的时间为1500m，下同
  }
  else if (!left && !right) {      //全部无检测到障碍物
    if (millis() >= keepTime) {
      Motion::forward(forwardPWM);
      //    Motion::forward(forwardPWM,1000);
      //    Serial.println("1");
    }
  }
  else if (left && right) {        //左右传感器均检测到障碍物
    Motion::backward(backwardPWM, 500, true);
    //int randomAngle=random()
    Motion::turnLeft(turnLeftPWM);
    keepTime=millis()+1500;         //左转需要持续的时间为1500m，下同
    //    Serial.println("2");
  }
  else if (left) {                //仅左边检测到障碍物
    Motion::backward(backwardPWM, 200);
    Motion::turnRight(turnRightPWM);
    keepTime=millis()+1000;         //左转需要持续的时间为1000m，下同
    //    Serial.println("3");
  }
  else {                          //仅邮编检测到障碍物
    Motion::backward(backwardPWM, 200);
    Motion::turnLeft(turnLeftPWM);
    keepTime=millis()+1000;         //左转需要持续的时间为1000m
    //    Serial.println("4");
  }
  //  Serial.print(left);
  //  Serial.print(' ');
  //  Serial.println(right);
}
};
