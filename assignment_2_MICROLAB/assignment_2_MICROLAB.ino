void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  DDRD=0xFC;          //0b1111 1100
  DDRB=0xFC;          //ob1111 1100
  Serial.begin(9600);
}

void loop()
{
  int a0=digitalRead(A0);
  int a1=digitalRead(A1);
  delay(500);

  ledOn(1);
 
}

void ledOn(int position_LED)
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
