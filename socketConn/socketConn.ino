#include "SocketInit.h"
//#include "Motor.h"
#include "Steering.h"

void setup() {
  SocketInit::setup();
  Motor::setup();
  Steering::setup();
}

void loop() {
  SocketInit::loop();

}
