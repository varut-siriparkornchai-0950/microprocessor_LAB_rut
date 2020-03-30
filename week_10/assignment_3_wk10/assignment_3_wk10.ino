// Connect encoder channel Band Detect the direction of motor rotation.

#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

int count = 0, detector=6, speedo=-20;

void speedMotor(int sped)
{
  if(sped>=0)    // CW
  {
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,sped);
    Serial.print("CW : ");
  }
  else if(sped<0) // CCW
  {
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW);
    analogWrite(MOTOR_PWM_PIN,sped/-1);
    Serial.print("CCW : ");
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
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);

  if(speedo<0)
  {
    detector=4;
  }
  
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
  speedMotor(speedo);
  Serial.println(count);
}
