#include "Arduino.h"

namespace Motor {
//pin assignments
int L_EN = 7;    // L293驱动板（LEN）
int R_EN = 6;    // L293驱动板（REN）
int L_Pos = 5;   // L293驱动板（L+）
int L_Neg = 4;   // L293驱动板（L-）
int R_Pos = 3;   // L293驱动板（R+）
int R_Neg = 2;   // L293驱动板（R-）

int leftPwm;
int rightPwm;

void decode(byte*);
void changeState(int, int);

void decode(byte * code) {
  int left = 2 * code[1];
  if (code[1] > 0x7f) {
    left = 2 * (code[1] - 0xff);
  }
  int right = 2 * code[2];
  if (code[2] > 0x7f) {
    right = 2 * (code[2] - 0xff);
  }
  changeState(left, right);
}

void changeState(int LP, int RP) {
  leftPwm = LP;
  rightPwm = RP;
  if (leftPwm > 0) {
    analogWrite(L_Pos, leftPwm);
    analogWrite(L_Neg, 0);
  }
  else {
    analogWrite(L_Pos, 0);
    analogWrite(L_Neg, -leftPwm);
  }

  if (rightPwm > 0) {
    analogWrite(R_Pos, rightPwm);
    analogWrite(R_Neg, 0);
  }
  else {
    analogWrite(R_Pos, 0);
    analogWrite(R_Neg, -rightPwm);
  }
}

void setup() {
  pinMode(L_Pos, OUTPUT);
  pinMode(L_Neg, OUTPUT);
  pinMode(R_Pos, OUTPUT);
  pinMode(R_Neg, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);

  digitalWrite(L_Pos, LOW);
  digitalWrite(L_Neg, LOW);
  digitalWrite(R_Pos, LOW);
  digitalWrite(R_Neg, LOW);
  digitalWrite(L_EN, HIGH);
  digitalWrite(L_EN, HIGH);
}

}
