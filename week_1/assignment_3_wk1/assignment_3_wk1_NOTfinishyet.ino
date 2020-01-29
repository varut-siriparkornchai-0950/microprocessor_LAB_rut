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

int p=0, a0, a1, a2, cow = 0;
String check0 = "open", check1 = "open";

void setup()
{
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  DDRD = 0b11111100;         
  DDRB = 0b00000011;  
  Serial.begin(9600);   
  LEDup(0); 
}

void loop()
{
  a0 = digitalRead(A0);
  a1 = digitalRead(A1);
  a2 = analogRead(A2);

  Serial.println(a0);
  Serial.println(a1);
  Serial.println(cow);

 PORTD=0b00000100;
 PORTB=0b00000000;
 delay(a2);

  if((a0 == 1)&&(check0 == "open"))                    //A0 button   DOOR open & finger up _________________ A0 _______________
  {
    check0 = "close";
  }

  else if((a0 == 0)&&(check0 == "close")&&(a1 == 1))   // DOOR close & finger down
  {
    while(a1 == 1)
    {
      for(cow;cow<=8;cow++)
      {
        if(cow == 8)
        {
          cow = 0;
        }
        Serial.print(cow);
        a1 = digitalRead(A1);
        if(a1 == 1)
        {
          LEDup(cow);
          delay(200);
        }
      }
      check0 = "open";
    }
  }

  else if((a1 == 1)&&(check1 =="open"))                //A1 button   DOOR open & finger up _________________ A1 _______________ 
  {
    check1 = "close";
  }

  else if((a1 == 0)&&(check1 == "close")&&(a0 == 1))   // DOOR close & finger down
  {
      check1 = "open";
   }
    
  }
  
