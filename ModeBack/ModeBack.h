#include "Motion.h"
#include "Gyroscope.h"

namespace{
float targetDistance;
float targetAngle;
void modeSetup();
void modeLoop();

void modeSetup(){
  pinMode(detectLeft, INPUT);
  pinMode(detectRight, INPUT);
  pinMode(detectMid, INPUT);
}

void modeLoop(){
  
}

};
