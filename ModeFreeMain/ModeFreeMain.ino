#include "ModeFree.h"
int mode=1;      //避障模式
void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Motion::motionSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(mode){
    case 1:
    ModeFree::modeLoop();
  }
}
