#define LED1 11
#define INT_PIN 3
bool toggle;
int mode=1, timer1_counter, sw, countRound=1;
String check0 = "open"; 

ISR(TIMER1_OVF_vect)
{
  if((mode == 1)&& (countRound == 1))
  {
    TCNT1 = timer1_counter;
    toggle = !toggle;
  }
  else if((mode == 2)&& (countRound == 2))
  {
    TCNT1 = timer1_counter;
    toggle = !toggle;
    countRound=1;
  }
  else if((mode == 3)&& (countRound == 3))
  {
    TCNT1 = timer1_counter;
    toggle = !toggle;
    countRound=1;
  }
  else{
    countRound++;
  }
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  noInterrupts();         
  TCCR1A = 0;       //reset timer
  TCCR1B = 0;       //reset timer

  timer1_counter = 3036;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);

  interrupts();
}

void loop()
{
  sw = digitalRead(INT_PIN);
  if((sw == 1)&&(check0 == "open"))         //sw button   DOOR open & finger up
  {
    check0 = "close";
  }
  else if((sw == 0)&&(check0 == "close"))   // DOOR close & finger down
  {
    if(mode == 3){
      mode = 0;
      countRound = 1;
    }
    mode++;
    check0 = "open";
  }
  digitalWrite(LED1, toggle);
}
