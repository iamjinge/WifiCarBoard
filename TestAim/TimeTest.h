#include "Arduino.h"
namespace TimeTest{
    int last = 0;
void setup(){
Serial.begin(9600);
};
void loop(){
int now = millis();
if (now - last>1000){
    Serial.println(now - last);
    last = now;
}
};
}
