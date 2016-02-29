#include "Arduino.h"
#include"Motion.h"

namespace ModeWall {
int detectLeft = 22;    //左侧红外避障模块检测
int detectRight = 23;  //右侧红外避障模块检测
int detectMid = 24;    //中间红外避障模块检测

int forwardPWM = 150;
int backwardPWM = 150;
int turnLeftPWM = 150;
int turnRightPWM = 150;

int stateFlag = 0;
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
  
}
};
