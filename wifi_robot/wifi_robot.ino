
//pin assignments
int L_EN = 7;    // L293驱动板（LEN）
int R_EN = 6;    // L293驱动板（REN）
int L_Pos= 5;    // L293驱动板（L+）  
int L_Neg= 4;    // L293驱动板（L-）  
int R_Pos= 3;    // L293驱动板（R+） 
int R_Neg= 2;    // L293驱动板（R-）

//cmd
typedef enum{
  cmd_forward  = 0x01,
  cmd_backward = 0x02,
  cmd_left     = 0x04,
  cmd_right    = 0x03,
  cmd_stop     = 0x00,
  cmd_error    = 0xff,
}cmd;

int comdata[5];

void setup()
{
    Serial3.begin(9600);               //设置波特率为9600bps
    pinMode(L_Pos,OUTPUT);
    pinMode(L_Neg,OUTPUT);
    pinMode(R_Pos,OUTPUT);
    pinMode(R_Neg,OUTPUT);
    pinMode(L_EN,OUTPUT);
    pinMode(R_EN,OUTPUT);

    digitalWrite(L_Pos,LOW);
    digitalWrite(L_Neg,LOW);
    digitalWrite(R_Pos,LOW);
    digitalWrite(R_Neg,LOW);
    digitalWrite(L_EN,HIGH);
    digitalWrite(L_EN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(receiveCMD())
  {
    case cmd_forward: Forward(200);break;
    case cmd_backward:Backward(180);break;
    case cmd_left:    Left(150);break;
    case cmd_right:   Right(150);break;
    case cmd_stop:    Stop();break;
   }
}

int receiveCMD(void)
{
  int i;
  if(Serial3.available())
  {
    for(i=0;i<5;i++)
    {
      comdata[i]=Serial3.read();
      delay(5);
     }
     for (i = 0; i < 5; i++){
       Serial3.write(comdata[i]);
     }
     if((comdata[0]&comdata[4])==0xff) return comdata[2];
  }
  return cmd_error;
}

void Forward(int pwm)
{
      analogWrite(L_Pos,pwm);
      analogWrite(L_Neg,0); 
      analogWrite(R_Pos,pwm);
      analogWrite(R_Neg,0); 
}

void Backward(int pwm)
{
      analogWrite(L_Pos,0);
      analogWrite(L_Neg,pwm); 
      analogWrite(R_Pos,0);
      analogWrite(R_Neg,pwm); 
}

void Left(int pwm)
{
      analogWrite(L_Pos,0);
      analogWrite(L_Neg,0); 
      analogWrite(R_Pos,pwm);
      analogWrite(R_Neg,0); 
}

void Right(int pwm)
{
      analogWrite(L_Pos,pwm);
      analogWrite(L_Neg,0); 
      analogWrite(R_Pos,0);
      analogWrite(R_Neg,0); 
}

void Stop(void)
{
      analogWrite(L_Pos,0);
      analogWrite(L_Neg,0); 
      analogWrite(R_Pos,0);
      analogWrite(R_Neg,0); 
}


