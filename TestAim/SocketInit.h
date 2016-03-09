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
    byte input[8];
    Serial3.readBytes(input, 8);
    int i = 0;
    for (i = 0; i < 8; i++) if (input[i] == 0x62) break;
    if (i > 0) {
      byte addition[i];// = new byte[i];
      Serial3.readBytes(addition, i);
      byte tmp[8];
      for (int j = 0; j < 8; j++) {
        tmp[j] = input[j];
      }
      for (int index = i; index < 8; index++) {
        if (i + index < 8)
          input[index] = tmp[i + index];
        else input[index] = addition[index + i - 8];
      }
    }
    handleInput(input);
  }
  int outputNum = Serial3.availableForWrite();
  if (bytesToSend[0] == CODE_BEGIN && bytesToSend[7] == CODE_END) {
    Serial3.write(bytesToSend, CODE_LENGTH);
    bytesToSend[0] = 0x00; // make bytesToSend invalid
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
        int angle =  inputBytes[4];
        if (angle > 127) angle -= 256;
        int distance = inputBytes[2] * 256 + inputBytes[3];
        DataCenter::aimDistance = distance;
        DataCenter::aimAngle = angle;
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

