#include "SocketCtrl.h"
#include "Motor.h"

void setup() {
  // put your setup code here, to run once:
  SocketCtrl::setup();
  Motor::setup();
  DataCenter::mode = 4;
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!DataCenter::flagModeChange) {
    Motor::loop();
    SocketCtrl::getInput();

    switch (DataCenter::mode) {
      // free mode
      case 1: {
          break;
        }
      case 2: {
          break;
        }
      // back to aim
      case 4: {
          break;
        }
    };
    DataCenter::flagModeChange = false;
  }
}
