int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS
byte number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int pos = 0, leftp = 3, rightp = 2, left, right, timer1_counter;
String check0 = "open", check1 = "open"; 
bool sw = 0;

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

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  if(sw == 0){
    playnum(pos);
  }
  else if(sw == 1){
    ++pos;
    playnum(pos);
  }
}

void reseto()
{
  pos = 0;
  playnum(pos);
}

void setup() {
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  pinMode(leftp, INPUT);
  pinMode(rightp, INPUT);

  noInterrupts();         
  TCCR1A = 0;       //reset timer
  TCCR1B = 0;       //reset timer
  timer1_counter = 3036;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  
  attachInterrupt(digitalPinToInterrupt(2), reseto, RISING);  
  Serial.begin(9600);
  setLed(0x3F);
}

void loop() {
  left = digitalRead(leftp);
  right = digitalRead(rightp);
  Serial.println(pos%10);

//     _________Door of filter clicker_________

  if((left == 1)&&(check0 == "open"))         //A0 button   DOOR open & finger up
  {
    check0 = "close";
  }
  else if((left == 0)&&(check0 == "close"))   // DOOR close & finger down
  {
    sw = !sw;
    check0 = "open";
  }
  else if((right == 1)&&(check1 =="open"))      //A1 button   DOOR open & finger up 
  {
    check1 = "close";
  }
  else if((right == 0)&&(check1 == "close"))   // DOOR close & finger down
  {
    check1 = "open";
  }
}

void playnum(int pos)
{
  setLed(number[pos%10]);
}
