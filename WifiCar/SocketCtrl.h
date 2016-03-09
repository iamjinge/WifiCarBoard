#include "Arduino.h"
#include "DataCenter.h"

namespace SocketCtrl {
int CODE_LENGTH = 8;

byte CODE_BEGIN = 'b';  // begin byte of the code
byte CODE_END = 'e';    // end byte of the code
byte CODE_RETUEN = 's'; // byte to tell state

const byte CODE_MOTOR = 0x01;
const byte CODE_STEERING = 0x02;
const byte CODE_GET_AIM = 0x03;
const byte CODE_REQUEST_AIM = 0x83;
const byte CODE_CHANGE_MODE = 0x10;

byte output[8];

void sendOutput();
void getAim();
bool handleInput(byte*);

void setup() {
  Serial3.begin(9600);
  Serial.begin(9600);
}

void getInput() {
  int inputNum = Serial3.available();
  if (inputNum > 0) {
    byte input[8];
    Serial3.readBytes(input, 8);
    int i = 0;
    for (i = 0; i < 8; i++) if (input[i] == 0x62) break;
    if (i > 0) {
      byte addition[i];
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
}

bool handleInput(byte* input) {
  if (input[0] == CODE_BEGIN && input[CODE_LENGTH - 1] == CODE_END) {
    switch (input[1]) {
      case CODE_MOTOR: {
          int left = 2 * input[2];
          if (input[1] > 0x7f)  left = 2 * (input[2] - 0xff);
          int right = 2 * input[3];
          if (input[2] > 0x7f)  right = 2 * (input[3] - 0xff);
          DataCenter::motorLeft = left;
          DataCenter::motorRight = right;
          DataCenter::flagMotorChange = true;
          break;
        }
      case CODE_GET_AIM: {
          int angle =  input[4];
          if (angle > 127) angle -= 256;
          int distance = input[2] * 256 + input[3];
          DataCenter::aimDistance = distance;
          DataCenter::aimAngle = angle;
          DataCenter::flagGetAim = true;
          break;
        }
      case CODE_CHANGE_MODE: {
          DataCenter::mode = input[2];
          DataCenter::flagModeChange = true;
          break;
        }
    }
    Serial3.write(input, CODE_LENGTH);
  }
}

void getAim() {
  output[0] = CODE_BEGIN;
  output[1] = CODE_GET_AIM;
  output[7] = CODE_END;
  for (int i = 2; i < 7; i ++)
    output[i] = 0;
  sendOutput();
  DataCenter::flagGetAim = false;
}

void sendOutput() {
  int outputNum = Serial3.availableForWrite();
  if (output[0] == CODE_BEGIN && output[7] == CODE_END) {
    Serial3.write(output, CODE_LENGTH);
    output[0] = 0x00; // make output invalid
  }
}
};

