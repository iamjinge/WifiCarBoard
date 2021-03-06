#define FILE_MOTION
#include "Arduino.h"



namespace Motion {
int L_EN = 7;    // L293驱动板（LEN）
int R_EN = 6;    // L293驱动板（REN）
int L_Pos = 5;   // L293驱动板（L+）
int L_Neg = 4;   // L293驱动板（L-）
int R_Pos = 3;   // L293驱动板（R+）
int R_Neg = 2;   // L293驱动板（R-）
int motionState=0;//0-stop;1-forward;2-back;3-left;4-right;5-turnForward
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
  motionState=0;
}
void motionStop() {
  analogWrite(L_Pos, 0);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, 0);
  analogWrite(R_Neg, 0);
  motionState=0;
}
void turnLeft(int pwm, int mtime = 0, bool needStop = false, int mode = 0) {
  pwm = constrain(pwm, 0, 255);
  switch (mode) {
    case 1:
      analogWrite(L_Pos, 0);
      analogWrite(L_Neg, pwm);
      analogWrite(R_Pos, 0);
      analogWrite(R_Neg, 0);
      break;
    case 2:
      analogWrite(L_Pos, 0);
      analogWrite(L_Neg, pwm);
      analogWrite(R_Pos, pwm);
      analogWrite(R_Neg, 0);
      break;
    default:
      analogWrite(L_Pos, 0);
      analogWrite(L_Neg, 0);
      analogWrite(R_Pos, pwm);
      analogWrite(R_Neg, 0);
  }
  motionState=3;
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}
void turnRight(int pwm, int mtime = 0, bool needStop = false, int mode = 0) {
  pwm = constrain(pwm, 0, 255);
  switch (mode) {
    case 1:
      analogWrite(L_Pos, 0);
      analogWrite(L_Neg, 0);
      analogWrite(R_Pos, 0);
      analogWrite(R_Neg, pwm);
      break;
    case 2:
      analogWrite(L_Pos, pwm);
      analogWrite(L_Neg, 0);
      analogWrite(R_Pos, 0);
      analogWrite(R_Neg, pwm);
      break;
    default:
      analogWrite(L_Pos, pwm);
      analogWrite(L_Neg, 0);
      analogWrite(R_Pos, 0);
      analogWrite(R_Neg, 0);
  }
  motionState=4;
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
  motionState=1;
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
  motionState=2;
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}
void turnForward(int lpwm,int rpwm, int mtime = 0, bool needStop = false) {
  lpwm = constrain(lpwm, 0, 255);
  rpwm = constrain(rpwm, 0, 255);
  analogWrite(L_Pos, lpwm);
  analogWrite(L_Neg, 0);
  analogWrite(R_Pos, rpwm);
  analogWrite(R_Neg, 0);
  motionState=5;
  delay(mtime);
  if (needStop) {
    motionStop();
  }
}

};

