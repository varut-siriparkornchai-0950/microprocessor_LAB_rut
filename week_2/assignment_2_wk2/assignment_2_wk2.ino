int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, LP, RP,permis;
int leftP=4, rightP=5;
int posi = 0, poten, p;
String check0 = "open", check1 = "open"; 

void updateDATA(uint16_t updata);
void LEDup(int position_LED);

void setup()
{
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
 pinMode(leftP,INPUT);
 pinMode(rightP,INPUT);
 Serial.begin(9600);
}

void loop()
{
  LP=digitalRead(leftP);
  RP=digitalRead(rightP);
  if(p>15)                                   //go throught left
  {
    p = 0;
  }
  else if(p<0)                              //go through right
  {
    p = 15;
  }
  LEDup(p);                                 //turn-on LED

//     _________Door of filter clicker_________

  if((LP == 1)&&(check0 == "open"))         //A0 button   DOOR open & finger up
  {
    check0 = "close";
  }
  else if((LP == 0)&&(check0 == "close"))   // DOOR close & finger down
  {
    p++;
    check0 = "open";
  }
  else if((RP == 1)&&(check1 =="open"))      //A1 button   DOOR open & finger up 
  {
    check1 = "close";
  }
  else if((RP == 0)&&(check1 == "close"))   // DOOR close & finger down
  {
    p--;
    check1 = "open";
  }


}

void updateDATA(uint16_t updata)
{
 digitalWrite(latch_pin,LOW);
 for(int i = 0 ; i < 16 ; i++)
 {
  digitalWrite(data_pin,(updata>>(15-i)) & 0b0000000000000001);      // & 0x01 for checking last bit, is that True?
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
 }
 digitalWrite(latch_pin,HIGH);
 delay(100);
}

void LEDup(int position_LED)                //function shift position
{
  int LED = 0b0000000000000001;
  LED = LED << position_LED;
  updateDATA(LED);
}
