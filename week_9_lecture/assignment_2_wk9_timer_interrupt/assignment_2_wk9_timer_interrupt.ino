#define LED1 11
#define LED2 10
#define INT_PIN 3

int toggle=1, timer1_counter;

ISR(TIMER1_OVF_vect)
{
  TCNT1 =timer1_counter;
  digitalWrite(LED2, toggle);
  toggle = !toggle;            // meaning "toggle = negative toggle"
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  noInterrupts();         
  TCCR1A = 0;       //reset timer
  TCCR1B = 0;       //reset timer

  timer1_counter = 1;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);

  interrupts();
}

void loop()
{
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);
}
