void setup() {
  DDRD=0xFF;
  DDRB=0xFF;
  Serial.begin(9600);
}

void loop() {
 PORTD=0b00000100;
 PORTB=0b000000;
 delay(500);
 for(int b=0;b<=4;b++){
   PORTD=PORTD<<1;
   delay(500);
   Serial.print(b);
   if(b>=4){
     PORTD=0x00;
     PORTB=0b000001;
     delay(500);
     PORTB=PORTB<<1;
     delay(500);
   }
 }
}
