#define buzzer 10
char recieve = ' ';

void onLED(void)
{
  byte LED_D=0b00000100;
  byte LED_B=0b000001;
  
  for(int j=0;j<6;j++)
  {
   PORTB = 0x00;
   PORTD = LED_D << j;
   delay(700);
  }
  for(int i=0;i<2;i++)
  {
    PORTD = 0x00;
    PORTB = LED_B << i;
    delay(700);
  }
  PORTD = 0x00;
  PORTB = 0x00;
}

void bomb(void)
{
  analogWrite(buzzer,127);
  delay(3000);
  analogWrite(buzzer,0);
}

void setup()
{
  DDRD=0b11111100;          //0b1111 1100
  DDRB=0b00000011;          //ob0000 0011

  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 if(Serial.available())
   {
      char recieve = Serial.read();
      if (recieve == 'g') 
      {
        onLED();
        bomb();
      }
   }
}
