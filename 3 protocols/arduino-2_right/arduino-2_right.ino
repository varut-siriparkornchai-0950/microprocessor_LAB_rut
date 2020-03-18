#include <Wire.h>
#include <SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
int deci=0,digi=0,i,j,stopT=0;
byte arrayR[2];
int map7seg[10] = {
 0x3F,0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};

void LED1(unsigned char Data) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Data);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}
void LED2(unsigned char Data) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Data);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
}

void countDown(unsigned char decimal, unsigned char digital){
  for(int i=decimal; i>=0;i--)
  {
    LED1(map7seg[i]);
    j=digital;
    if(i<decimal)
    {
     j=9;
    }
    for(j; j>=0;j--)
    {
      LED2(map7seg[j]);
      delay(1000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Wire.begin(0b0000001);
  Wire.onReceive(receiveEvent);

  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  Serial.begin(9600);  
}

void loop()
{
 delay(100);
}

void receiveEvent(int timec) {
  if(stopT == 0)
  {
    for(int i=0;i<2;i++)
    {
      arrayR[i] = Wire.read();
    }
    deci = arrayR[0]/10;
    digi = arrayR[0]%10;
    Serial.print(digi);
    LED1(map7seg[deci]);
    LED2(map7seg[digi]);
    if((arrayR[1] == 0) && (stopT == 0))
    {
      countDown(deci,digi);
      stopT++;
    }
  }
}
