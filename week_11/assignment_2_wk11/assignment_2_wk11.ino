#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9

#define statusEncoder 4

#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

volatile int count = 0, detector=6,thousand,hundred;
int map7seg[10] = {
 0x3F,0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};

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
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,sped);
  }
  else if(sped<0) // CCW
  {
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
  if(Serial.available()){
    String speedo = Serial.readString();
    int sped = speedo.toInt();
    if(sped>=0){
      detector = 6;
    }
    else{
      detector = 4;
    }
    speedMotor(sped);
  }
  if(count>=0){
    digitalWrite(statusEncoder, LOW);
  }
  else{
    digitalWrite(statusEncoder, HIGH);
  }
  Serial.println(count);
  thousand = abs(count)/1000;
  hundred = (abs(count)/100)%10;
  LED1(map7seg[thousand]);
  LED2(map7seg[hundred]);
}
