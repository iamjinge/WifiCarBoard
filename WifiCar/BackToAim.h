#include "DataCenter.h"
#include "SocketCtrl.h"

namespace BackToAim {
bool aimInVision;
int motionOver;
int startMS;
int keepMS;
float startAngle;

void setup() {
  SocketCtrl::getAim();
  aimInVision = false;
  motinOver = false;
}

void loop() {
  if (aimInVision) {
    if (motionOver) {
      SocketCtrl::getAim();
      aimInVision = false;
      motionOver = false;
    } else {
      if (startMS - millis() > keepMs) {
          
        motionOver = true;
      }
    }
  } else {
    int angle = DataCenter::aimAngle;
    int distance = DataCenter::aimDistance;
    if (distance >= 20 && angle >= -30 && angle <= 30) {
      aimInVision = true;
    }

    if (distance > 20) {
      if (angle > 10) {
        Motor::changeState(0, 120);
      } else if (angle < -10 ) {
        Motor::changeState(90, 0);
      } else {
        if (distance < 50) {
          Motor::changeState(90, 120);
        } else if (distance < 100) {
          Motor::changeState(120, 150);
        } else {
          Motor::changeState(160, 200);
        }
      }
    } else if (distance == 1) {
      if (angle < 0) {
        Motor::changeState(90, 0);
      } else {
        Motor::changeState(0, 120);
      }
    } else if (distance == 0) {
      Motor::changeState(0, 0);
    } else {
      Motor::changeState(0, 0);
    }
  }
}
}
