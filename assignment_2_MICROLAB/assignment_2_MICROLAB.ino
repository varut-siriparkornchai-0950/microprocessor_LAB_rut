int p=0, a0, a1;
String check0 = "open", check1 = "open";
void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  DDRD=0b11111100;         
  DDRB=0b00000011;  
  Serial.begin(9600);   
  LEDup(0); 
}

void loop()
{
  a0=digitalRead(A0);
  a1=digitalRead(A1);
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

  if((a0 == 1)&&(check0 == "open"))         //A0 button   DOOR open & finger up
  {
    check0 = "close";
  }
  else if((a0 == 0)&&(check0 == "close"))   // DOOR close & finger down
  {
    p++;
    check0 = "open";
  }
  else if((a1 == 1)&&(check1 =="open"))      //A1 button   DOOR open & finger up 
  {
    check1 = "close";
  }
  else if((a1 == 0)&&(check1 == "close"))   // DOOR close & finger down
  {
    p--;
    check1 = "open";
  }

  
 Serial.print(a0);
 Serial.println(a1);
 Serial.println(p);
 Serial.println(check0);
 Serial.println(check1);


}

void LEDup(int position_LED)                //function shift position
{
  byte LED_D=0b00000100;
  byte LED_B=0b00000001;
  if(position_LED>=0 && position_LED<=5)
  {
    PORTB = 0x00;
    PORTD = LED_D << position_LED;
  }
  else if(position_LED ==6 || position_LED ==7)
  {
    PORTD = 0x00;
    PORTB = LED_B << (position_LED % 6);
  }
}
