#include "Arduino.h"
namespace Sheering {
int servopin = 9; //设置舵机驱动脚到数字口9
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;
int targetAngle;
int actionTime;

void servo(int width) {
  digitalWrite(servopin, HIGH); //将舵机接口电平置高
  delayMicroseconds(width);//延时脉宽值的微秒数
  digitalWrite(servopin, LOW); //将舵机接口电平置低
}

void setup() {
  pinMode(servopin, OUTPUT);
  Serial.begin(9600);//设置波特率为9600
}
void loop() {
  int result = 0;
  int v = Serial.read();
  while (v >= '0' && v <= '9') {
    result = result * 10 + v - '0';
    v = Serial.read();
  }
  if (result > 700 && result < 2700) {
      targetAngle = result;
      actionTime = 0;
    Serial.println(result);
  }
  if (actionTime < 10){
      servo(targetAngle);
      actionTime ++;
  }
  delay(30);

};
}
