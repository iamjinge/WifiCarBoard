#include "Arduino.h"
#include"Motion.h"

namespace ModeFree {
bool detectLeft = 22;  //左侧红外避障模块检测
bool detectRight = 23;  //右侧红外避障模块检测
const static int forwardPWM = 150;
const static int backwardPWM = 150;
const static int turnLeftPWM = 150;
const static int turnRightPWM = 150;

void modeLoop() {
  bool left = ~digitalRead(detectLeft);
  bool right = ~digitalRead(detectRight);
  if (~left && ~right) {
    Motion::forward(forwardPWM);
  }
  else if (left && right) {
    Motion::backward(backwardPWM, 500, true);
    //int randomAngle=random()
    Motion::turnLeft(turnLeftPWM, 1500, true);
  }
  else if (left) {
    Motion::backward(backwardPWM, 200);
    Motion::turnRight(turnRightPWM, 1000, true);
  }
  else {
    Motion::backward(backwardPWM, 200);
    Motion::turnLeft(turnLeftPWM, 1000, true);
  }
}
};
