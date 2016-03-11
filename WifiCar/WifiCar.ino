#include "SocketCtrl.h"
#include "BackToAim.h"
#include "ModeFree.h"
#include "ModeWall.h"

void setup() {
  // put your setup code here, to run once:
  SocketCtrl::setup();
  Motor::setup();
  DataCenter::mode = 0;

  BackToAim::setup();
  Gyroscope::setup();
  
  ModeFree::modeSetup();
  
  ModeWall::modeSetup();
  Ultrasonic::setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!DataCenter::flagModeChange) {
    SocketCtrl::getInput();

    switch (DataCenter::mode) {
      // Manual mode
      case 0: {
          break;
        }
      // free mode
      case 1: {
          ModeFree::modeLoop();
          break;
        }
      // wall mode
      case 2: {
          ModeWall::modeLoop();
          break;
        }
      // back to aim
      case 3: {
          BackToAim::loop();
          break;
        }
    };
  }
  Motor::motorSpeed(0,0);
  DataCenter::flagModeChange = false;
}
