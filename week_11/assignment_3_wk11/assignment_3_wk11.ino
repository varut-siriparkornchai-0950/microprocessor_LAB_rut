#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9

#define statusEncoder 4

#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

#define potentio A0
volatile int count = 0, detector=6,thousand,hundred;
int map7seg[10] = {
 0x3F,0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};
int setPosy = 500, P=1.0,error=0;

void LED1(unsigned char Data) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Data);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
}
void LED2(unsigned char Data) {
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, Data);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
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
  Serial.begin(9600);
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(statusEncoder, OUTPUT);
  
  pinMode(2, INPUT_PULLUP);

  pinMode(potentio, INPUT);

  attachInterrupt(digitalPinToInterrupt(2),CW, RISING);
  attachInterrupt(digitalPinToInterrupt(3),CCW, RISING);
  
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,255);

  
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x3F);
  digitalWrite (SS_PIN_1, HIGH);
  digitalWrite (SS_PIN_1, LOW);
  digitalWrite (SS_PIN_2, HIGH);
  digitalWrite (SS_PIN_2, LOW);
}

void loop()
{ 
  setPosy = analogRead(potentio);
  error = setPosy - count;
  int sped = P*float(error);
  if(sped>=0){
    detector = 6;
  }
  else{
    detector = 4;
  }
  speedMotor(sped);
  
  //....... LED PART ..................
  if(count>=0){
    digitalWrite(statusEncoder, LOW);
  }
  else{
    digitalWrite(statusEncoder, HIGH);
  }
  //...... plot graph .................
  Serial.print(error);
  Serial.print(",");
  Serial.print(count);
  Serial.print(",");
  Serial.println(setPosy);
  Serial.println(detector);
  //...................................
  
  thousand = abs(count)/1000;
  hundred = (abs(count)/100)%10;
  LED1(map7seg[thousand]);
  LED2(map7seg[hundred]);
  //...................................
}
