#include "Arduino.h"
#include "Motor.h"
#include "DataCenter.h"

namespace SocketInit {
int CODE_LENGTH = 8;

byte CODE_BEGIN = 'b';  // begin byte of the code
byte CODE_END = 'e';    // end byte of the code
byte CODE_RETUEN = 's'; // byte to tell state

const byte CODE_MOTOR = 0x01;
const byte CODE_STEERING = 0x02;
const byte CODE_GET_AIM = 0x03;
const byte CODE_REQUEST_AIM = 0x83;

byte bytesToSend[8];

void send(byte*);
void getAim();
bool handleInput(byte*);

void setup() {
  Serial3.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int inputNum = Serial3.available();
  if (inputNum > 0) {
    byte inputBytes[CODE_LENGTH];
    Serial3.readBytes(inputBytes, CODE_LENGTH);
    handleInput(inputBytes);
  }
  int outputNum = Serial3.availableForWrite();
  if (bytesToSend[0] == CODE_BEGIN && bytesToSend[7] == CODE_END) {
    Serial3.write(bytesToSend, CODE_LENGTH);
    bytesToSend[0] == 0x00; // make bytesToSend invalid
  }
}

bool handleInput(byte* inputBytes) {
  if (inputBytes[0] == CODE_BEGIN && inputBytes[CODE_LENGTH - 1] == CODE_END) {
    byte validCode[6];
    for (int i = 0; i < 6; i++) {
      validCode[i] = inputBytes[i + 1];
    }
    switch (inputBytes[1]) {
      case CODE_MOTOR:
        Motor::decode(validCode);
        break;
      case CODE_GET_AIM:
        DataCenter::aimDistance = inputBytes[2] << 8 + inputBytes[3];
        DataCenter::aimAngle = inputBytes[4];
        break;
    }
    Serial3.write(inputBytes, CODE_LENGTH);
  }
}

void getAim() {
  bytesToSend[0] = CODE_BEGIN;
  bytesToSend[1] = CODE_GET_AIM;
  bytesToSend[7] = CODE_END;
  for (int i = 2; i < 7; i ++)
    bytesToSend[i] = 0;
  DataCenter::flagGetAim = false;
}

void send(byte* bytes) {
  for (int i = 0; i < CODE_LENGTH; i++) {
    bytesToSend[i] = bytes[i];
  }
}
};
