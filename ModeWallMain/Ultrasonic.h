#include "Arduino.h"

namespace Ultrasonic {
int leftTrigPin = 27;
int leftEchoPin = 28;
int rightTrigPin = 29;
int rightEchoPin = 30;
unsigned long leftTime0 = 0;
//unsigned long leftTime1 = 0;
unsigned long rightTime0 = 0;
//unsigned long rightTime1 = 0;
float maxDistance = 500;  //mm
float distance = 0;
int waitForEchoTime=500;  //ms 设置过小可能无法正常工作

void ultrasonicSetup() {
  // put your setup code here, to run once:
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  Serial.begin(9600);
}

float getDistance(int number) {    //0 for left, 1 for right //无法获取Echo时返回-1 距离超出设定上限返回0 
  unsigned long time0=0,time1=0;
  int trigPin=-1,echoPin=-1;
  if(number==0){
    time0=leftTime0;
    trigPin=leftTrigPin;
    echoPin=leftEchoPin;
  } 
  else {
    time0=rightTime0;
    trigPin=rightTrigPin;
    echoPin=rightEchoPin;
  }
  while(micros()-time0<60000);    //防止过于频繁地读取 控制两次读取间隔时间大于60mm
  digitalWrite(trigPin, true);
  delayMicroseconds(10);
  digitalWrite(trigPin, false);
  time0 = micros();
  while (!digitalRead(echoPin) && micros() < time0 + waitForEchoTime);
  time1 = micros();
  if (time1 >= time0 + waitForEchoTime) {
    Serial.println("time out");
    return -1;
  }
  else {
    //   Serial.print("time:");
    //   Serial.println(time1-time0);
    while (digitalRead(echoPin));
    time0 = micros();
    if(number=0){
      leftTime0=time0;
    }
    else{
      rightTime0=time0;
    }
    distance = (time0 - time1) * 340 / 2000;
    if(distance>maxDistance){
      Serial.println("distance out of range");
      return 0;
    }
    else{
//      Serial.print("distance is ");
//      Serial.print(distance);
//      Serial.println("mm");
        return distance;
    }
    //   Serial.print("duration:");
    //   Serial.println(time0-time1);
    
//    delay(1000);
  }
}

};
