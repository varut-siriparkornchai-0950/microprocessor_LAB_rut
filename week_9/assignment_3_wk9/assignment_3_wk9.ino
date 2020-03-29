int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS
byte number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int pos = 0,timer1_counter;

void setLed(uint8_t _state)
{
  digitalWrite(latch_pin,LOW);
  for(int i = 0 ; i < 8 ; i++){
  digitalWrite(data_pin,(_state >> (7-i)) & 0x01);
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH);
}

void playnum(int pos)
{
  setLed(number[pos%10]);
}

ISR(TIMER1_OVF_vect){
  TCNT1 = timer1_counter;
  playnum(pos);
  pos++;
}

void setup() {
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  
  noInterrupts();         
  TCCR1A = 0;       //reset timer
  TCCR1B = 0;       //reset timer

  timer1_counter = 1;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);

  interrupts();
  
  Serial.begin(9600);
  setLed(0x3F);
}

void loop() {
  Serial.println(pos);
}
