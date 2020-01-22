void setup()
{
  DDRD=0xFF;
  DDRB=0xFF;
  Serial.begin(9600);
}

void loop()
{
  PORTD=0b00000100;
 PORTB=0b000000;
 delay(500);
 
}
