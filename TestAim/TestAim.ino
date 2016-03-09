#include "SocketInit.h"
#include "GetAim.h"
//#include "TimeTest.h"

void setup() {
  // put your setup code here, to run once:
  SocketInit::setup();
  GetAim::setup();
  Motor::setup();
  Motor::changeState(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  SocketInit::loop();
  GetAim::loop();

}
