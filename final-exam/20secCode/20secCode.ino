int sensorState = 0, timer = 0, movement;
volatile int timer1_counter;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  timer++;
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
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
  movement = digitalRead(2);
  
  if (movement == HIGH && timer >= 20) {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    Serial.println("your hands are CLEAN !!!");
  } 
  else if(movement == HIGH){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    Serial.println(timer);
  }
  else{
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    timer = 0;
  }
}
