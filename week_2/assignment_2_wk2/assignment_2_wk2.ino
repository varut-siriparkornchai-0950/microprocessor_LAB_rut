int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, LP, RP,permis;
int leftP=4, rightP=5;
int posi = 0, poten; 

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
  if(p>7)                                   //go throught left
  {
    p = 0;
  }
  else if(p<0)                              //go through right
  {
    p = 7;
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

// Serial.print(a0);
// Serial.println(a1);
// Serial.println(p);
// Serial.println(check0);
// Serial.println(check1);

}

void LEDup(int position_LED)                //function shift position
{
  int LED = 0b0000000000000001;
  LED = LED << position_LED;
  updateDATA(LED);
}
