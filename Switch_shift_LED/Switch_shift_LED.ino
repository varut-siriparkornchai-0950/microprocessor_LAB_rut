void setup() {
DDRD=0xFC; //0b1111 1100
DDRB=0x03; //0b0000 0011
pinMode(A0,INPUT);
Serial.begin(9600);

}

void loop() {
  int b1 = digitalRead(A0);
  PORTD=0b00000100;
  delay(1000);
  if(PORTB=!0b000100){
    Serial.print(PORTD);
    PORTD=PORTD<<1;
    delay(1000);
  }
}
