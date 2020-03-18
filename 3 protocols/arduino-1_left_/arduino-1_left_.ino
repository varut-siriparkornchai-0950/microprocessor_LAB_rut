#include<Wire.h>

#define swL_add 5
#define swR_minus 4
#define sw_start 3
int timec = 0,add,minus,start;
byte arrayT[]={0,0};

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(swL_add, INPUT);
  pinMode(swR_minus, INPUT);
  pinMode(sw_start, INPUT);
}

void loop()
{
  add = digitalRead(swL_add);
  minus = digitalRead(swR_minus);
  start = digitalRead(sw_start);
  Wire.beginTransmission(0b0000001);
  if(add == 0)
  {
    timec += 1;
  }
  else if(minus == 0)
  {
    timec -= 1;
  }
  Serial.print(add);
  Serial.println(minus);
  Serial.print(timec);
  
  if(timec >=100 || timec <=-1)
  {
    timec = 0;
  }
  arrayT[0] = timec;
  arrayT[1] = start;
  for(int i=0;i<2;i++)
  {
   Wire.write(arrayT[i]);
  }

  Wire.endTransmission();
  delay(200);
}
