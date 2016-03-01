#include "Arduino.h"

namespace Gyroscope {
byte gyroData[11];
float a[3], w[3], angle[3], T;   //xyz轴的加速度,角速度和角度;温度
bool update();
void gyroscopeSetup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.setTimeout(100);
  Serial.begin(9600);
  update();
}

bool update() {
  if (Serial1.available()) {
    while (Serial1.available()) {
      Serial1.read();
    }
  }
  int i = 0, j = 0;
  int counter = 0;        //记录成功获取的包的数量,作为成功读取的判断,成功读取时,counter为3

  for (i = 0; i < 3; i++) {
    byte check = 0;          //校验
    Serial1.readBytes(gyroData, 11);
    if (gyroData[0] != 0x55) continue; //检查帧头
    for (j = 0; j < 10; j++) {
      check += gyroData[j];
    }
    if (check != gyroData[10]) {
      //      Serial.println("check code did not match!");
      continue;
    }
    counter++;
    switch (gyroData [1])
    {
      case 0x51:
        a[0] = (short(gyroData [3] << 8 | gyroData [2])) / 32768.0 * 16;
        a[1] = (short(gyroData [5] << 8 | gyroData [4])) / 32768.0 * 16;
        a[2] = (short(gyroData [7] << 8 | gyroData [6])) / 32768.0 * 16;
        T = (short(gyroData [9] << 8 | gyroData [8])) / 340.0 + 36.25;
        break;
      case 0x52:
        w[0] = (short(gyroData [3] << 8 | gyroData [2])) / 32768.0 * 2000;
        w[1] = (short(gyroData [5] << 8 | gyroData [4])) / 32768.0 * 2000;
        w[2] = (short(gyroData [7] << 8 | gyroData [6])) / 32768.0 * 2000;
        T = (short(gyroData [9] << 8 | gyroData [8])) / 340.0 + 36.25;
        break;
      case 0x53:
        angle[0] = (short(gyroData [3] << 8 | gyroData [2])) / 32768.0 * 180;
        angle[1] = (short(gyroData [5] << 8 | gyroData [4])) / 32768.0 * 180;
        angle[2] = (short(gyroData [7] << 8 | gyroData [6])) / 32768.0 * 180;
        T = (short(gyroData [9] << 8 | gyroData [8])) / 340.0 + 36.25;
        break;
    }
  }
  if (counter == 3) {
//    Serial.println("success");
//    Serial.println(angle[2]);
    return true;
  }
  else {
    return false;
  }
}
float getAngleZ(){
return angle[2];
}
};
