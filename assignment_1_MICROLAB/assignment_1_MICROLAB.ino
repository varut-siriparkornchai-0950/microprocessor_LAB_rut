void setup() 
{
  DDRD=0xFF;
  DDRB=0xFF;
}

void loop() 
{
 PORTD=0b00000100;
 PORTB=0b00000000;
 delay(200);
 for(int b=0;b<=4;b++)
 {
   PORTD=PORTD<<1;
   delay(200);
   if(b>=4)
   {
     PORTD=0x00;
     PORTB=0b00000001;
     delay(200);
     PORTB=PORTB<<1;
     delay(200);
   }
 }
}
