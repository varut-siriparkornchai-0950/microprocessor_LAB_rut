//Create speed controller and function receivenumber in range -100 to 100 for set the speed


#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

volatile int count = 0, detector= 6,setRPM = 100, deltaTIME, deltaCOUNT, sumERROR, rateERROR, Kp, Ki, Kd ;
volatile int controlSPEED=100;
volatile float previousTIME=0, previousRPM=0,previousERROR=0,previousCOUNT=0;
volatile float currentTIME, currentRPM, currentERROR;
int timer1_counter;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  currentTIME = millis();
  deltaTIME = (currentTIME - previousTIME)/1000;

  deltaCOUNT = abs(count) - previousCOUNT;
  currentRPM = int((deltaCOUNT*60)/(229*deltaTIME));
  currentERROR = setRPM - currentRPM;
  
  sumERROR += currentERROR*deltaTIME;

  rateERROR = (currentERROR - previousERROR)/deltaTIME;

  controlSPEED = (Kp*currentERROR)+(Ki*sumERROR)+(Kd*rateERROR);
  
  previousCOUNT = count;
  previousERROR = currentERROR;
  previousTIME = currentTIME;
}

void speedMotor(int sped)
{
  if(sped>=0)    // CW
  {
    if(sped>255){
     sped = 255;
    }
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,sped);
  }
  else if(sped<0) // CCW
  {
    if(sped<-255){
     sped = -255;
    }
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW);
    analogWrite(MOTOR_PWM_PIN,sped/-1);
  }
}

void CW()
{
  if(detector == 6)
  {
    count++;
  }
}
void CCW()
{
  if(detector == 4)
  {
    count--;
  }
}

void setup()
{
  //..... interrupt timer ..........
  noInterrupts();         
  TCCR1A = 0;       //reset timer
  TCCR1B = 0;       //reset timer

  timer1_counter = 59286;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);

  interrupts();
  //...............................
  
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),CW, RISING);
  attachInterrupt(digitalPinToInterrupt(3),CCW, RISING);
  
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,255);
}

void loop()
{ 
  if(controlSPEED>=0){
    detector = 6;
  }
  else{
    detector = 4;
  }
  speedMotor(int(controlSPEED));
  Serial.println(count);
}
