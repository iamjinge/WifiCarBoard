#include "ModeFree.h"

int switchPin = 25;
int mode = 1;    //避障模式
void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  Motion::motionSetup();
  ModeFree::modeSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.println(digitalRead(switchPin));
  if (!digitalRead(switchPin)) {
    Serial.println(digitalRead(switchPin));
    switch (mode) {
      case 1:
        ModeFree::modeLoop();
    }
  }
  else {
    Motion::motionStop();
  }
  //Serial.println(digitalRead(22));
}
