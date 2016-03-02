#include "Arduino.h"



namespace Motion {
int L_EN = 7;    // L293驱动板（LEN）
int R_EN = 6;    // L293驱动板（REN）
int L_Pos = 5;   // L293驱动板（L+）
int L_Neg = 4;   // L293驱动板（L-）
int R_Pos = 3;   // L293驱动板（R+）
int R_Neg = 2;   // L293驱动板（R-）
void motionSetup() {
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
void motionStop() {
  analogWrite(L_Pos, 0);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, 0);
  analogWrite(R_Neg, 0);
}
void turnLeft(int pwm, int mtime = 0, bool needStop = false) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(L_Pos, 0);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, pwm);
  analogWrite(R_Neg, 0);
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}
void turnRight(int pwm, int mtime = 0, bool needStop = false) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(L_Pos, pwm);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, 0);
  analogWrite(R_Neg, 0);
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}
void forward(int pwm, int mtime = 0, bool needStop = false) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(L_Pos, pwm);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, pwm);
  analogWrite(R_Neg, 0);
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}
void backward(int pwm, int mtime = 0, bool needStop = false) {
  pwm = constrain(pwm, 0, 255);
  analogWrite(L_Pos, 0);
  analogWrite(L_Neg, pwm);
  analogWrite(R_Pos, 0);
  analogWrite(R_Neg, pwm);
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}

};

