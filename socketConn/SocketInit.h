#include "Arduino.h"
#include "Motor.h"

namespace SocketInit {
int CODE_LENGTH = 8;

byte CODE_BEGIN = 'b';  // begin byte of the code
byte CODE_END = 'e';    // end byte of the code
byte CODE_RETUEN = 's'; // byte to tell state

const byte CODE_MOTOR = 0x01;
const byte CODE_STEERING = 0x02;

byte bytesToSend[8];

void send(byte*);

void setup() {
  Serial3.begin(9600);
}

void loop() {
  if (Serial3.available()) {

    byte inputBytes[CODE_LENGTH];
    Serial3.readBytes(inputBytes, CODE_LENGTH);
    // check if the input bytes is valid.
    if (inputBytes[0] == CODE_BEGIN && inputBytes[CODE_LENGTH - 1] == CODE_END) {
      byte validCode[6];
      for (int i = 0; i < 6; i++) {
        validCode[i] = inputBytes[i + 1];
      }
      switch (inputBytes[1]) {
        case CODE_MOTOR:
          Motor::decode(validCode);
          break;
      }

      Serial3.write(inputBytes, CODE_LENGTH);
    }

    if (bytesToSend[0] == CODE_BEGIN && bytesToSend[CODE_LENGTH - 1] == CODE_END) {
      Serial3.write(bytesToSend, CODE_LENGTH);
      bytesToSend[0] == 0x00; // make bytesToSend invalid
    }

  }
}

void send(byte* bytes) {
  for (int i = 0; i < CODE_LENGTH; i++) {
    bytesToSend[i] = bytes[i];
  }
}
};

