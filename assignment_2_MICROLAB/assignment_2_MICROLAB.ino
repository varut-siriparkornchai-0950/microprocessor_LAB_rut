int p=0, a0, a1;
String check0 = "open", check1 = "open";
void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  DDRD=0b11111100;         
  DDRB=0b00000011;  
  Serial.begin(9600);   
  ledOn(0); 
}

void loop()
{
  a0=digitalRead(A0);
  a1=digitalRead(A1);
  if(p>7)             //reset go left
  {
    p = 0;
  }
  else if(p<0)      
  {
    p = 7;
  }
  ledOn(p);

  if((a0 == 1)&&(check0 == "open"))
  {
    check0 = "close";
  }
  else if((a0 == 0)&&(check0 == "close"))
  {
    p++;
    check0 = "open";
  }
  else if((a1 == 1)&&(check1 =="open"))
  {
    check1 = "close";
  }
  else if((a1 == 0)&&(check1 == "close"))
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

void ledOn(int position_LED)
{
  byte LED_D=0b00000100;
  byte LED_B=0b000001;
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
