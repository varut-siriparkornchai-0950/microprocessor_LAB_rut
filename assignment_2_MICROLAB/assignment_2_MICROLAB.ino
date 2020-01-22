int p=0, a0, a1, check = 2;
 
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
  if((p>7)||(p<0))             //reset p = 0
  {
    p = 0;
  }
  ledOn(p);

  if((a0 == 1)&&(check ==3))
  {
    check = 2;
  }
  else if((a0 == 0)&&(check == 2))
  {
    p++;
    check = 3;
  }
//  if((a1 == 1)&&(check ==3))
//   {
//     check = 2;
//   }
  else if((a1 == 0)&&(check == 2))
  {
    p--;
    check = 3;
  }

  
 Serial.print(a0);
 Serial.println(p);
 Serial.println(p);

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
