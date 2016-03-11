#ifndef FILE_DataCenter
#include "DataCenter.h"
#endif
#include "Gyroscope.h"
#ifndef FILE_SOCKET_CTRL
#include "SocketCtrl.h"
#endif
#ifndef FILE_MOTOR
#include "Motor.h"
#endif

namespace BackToAim {
byte getAim; // 0: finding aim, 1: no aim, 2: find aim
byte motionType; // 0: motion over, 1: straight, 2: trun, 3: pause and finding aim
int startMS;
short keepMS;
float startAngle;
float targetAngle;

short pauseAfterMotion = 1800;

void setup() {
  SocketCtrl::getAim();
  motionType = 3;
}

void loop() {
  if (motionType == 0) {
    if (millis() - startMS > keepMS) {
      SocketCtrl::getAim();
      motionType = 3;
      startMS = millis();
      keepMS = 0;
    }
  } else if (motionType == 1) {
    int current = millis();
    if (millis() - startMS > keepMS) {
      Serial.print(current);
      Serial.println("straight over");
      startMS = millis();
      keepMS = pauseAfterMotion;
      motionType = 0;
      Motor::motorSpeed(0, 0);
    }
  } else if (motionType == 2) {
    Gyroscope::update();
    float currentAngle = Gyroscope::getAngleZ();
    Serial.print("current ");
    Serial.println(currentAngle);
    float diff = currentAngle - targetAngle;
    if (diff >= -1.5 && diff <= 1.5) {
      Serial.println("turn over " + String(startAngle));
      Serial.println(currentAngle);
      startMS = millis();
      keepMS = pauseAfterMotion;
      motionType = 0;
      Motor::motorSpeed(0, 0);
    } else {
      if (diff > 0) {
        Motor::motorSpeed(120, 0);
      } else {
        Motor::motorSpeed(0, 150);
      }
    }
  } else if (motionType == 3) {
    if (DataCenter::flagGetAim) {
      int angle = DataCenter::aimAngle;
      int distance = DataCenter::aimDistance;
      Serial.print("get aim in back: ");
      Serial.print(distance);
      Serial.print("  ");
      Serial.println(angle);
      if (angle >= -30 && angle <= 30 && distance != 1) {
        if (distance <= 15) {
          SocketCtrl::getAim();
          Serial.println("distance : " + distance);
        } else {
          if (angle >= -8 && angle <= 8) {
            motionType = 1;
            startMS = millis();
            if (distance > 100) keepMS = 600;
            else if (distance > 50) keepMS = 450;
            else if (distance > 30) keepMS = 250;
            else keepMS = 150;
            Motor::motorSpeed(160, 200);
            Serial.print(startMS);
            Serial.println("go straight");
          } else {
            motionType = 2;
            Gyroscope::update();
            startAngle = Gyroscope::getAngleZ();
            targetAngle = startAngle + angle;
            if (targetAngle > 180) targetAngle -= 360;
            if (targetAngle <= -180) targetAngle += 360;
            if (angle > 0) {
              Motor::motorSpeed(0, 150);
            } else {
              Motor::motorSpeed(120, 0);
            }
            Serial.print("turn ");
            Serial.println(angle);
          }
        }
      } else {
        motionType = 2;
        Gyroscope::update();
        startAngle = Gyroscope::getAngleZ();
        if (DataCenter::aimAngle >= 0) {
          targetAngle = startAngle + 30;
          targetAngle -= targetAngle > 180 ? 360 : 0;
          Motor::motorSpeed(0, 150);
        } else {
          targetAngle = startAngle - 30;
          targetAngle += targetAngle <= -180 ? 360 : 0;
          Motor::motorSpeed(120, 0);
        }
        Serial.print(targetAngle);
        Serial.println("turn to find aim");
      }
    } else {
      if (millis() - startMS > keepMS) {
        startMS = millis();
        keepMS = 500;
        SocketCtrl::getAim();
      }
    }
  }
}
}
