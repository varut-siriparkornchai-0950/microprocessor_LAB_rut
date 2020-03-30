// From encoder example, change to use external interrupt for count the encoder.

#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

int count = 0;

void speedMotor(int sped)
{
  if(sped>=0)
  {
    digitalWrite(MOTOR_D1_PIN,LOW);
    digitalWrite(MOTOR_D2_PIN,HIGH);
    analogWrite(MOTOR_PWM_PIN,sped);
  }
  else if(sped<0)
  {
    digitalWrite(MOTOR_D1_PIN,HIGH);
    digitalWrite(MOTOR_D2_PIN,LOW);
    analogWrite(MOTOR_PWM_PIN,sped/-1);
  }
}

void callMeback()
{
  count++;
}

void setup()
{
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),callMeback, RISING);
  
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,255);
}

void loop()
{ 
  speedMotor(-20);
  Serial.println(count);
}
