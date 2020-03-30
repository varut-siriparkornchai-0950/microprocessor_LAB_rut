// Write the function for control dc motor.Input of thefunctionis the speed of motorinrange-255 to 255

#define MOTOR_D1_PIN 7
#define MOTOR_D2_PIN 8
#define MOTOR_PWM_PIN 6

bool previous_read;
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

void setup()
{
  pinMode(MOTOR_D1_PIN,OUTPUT);
  pinMode(MOTOR_D2_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("TestEncoder");
  
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,255);
}

void loop()
{
  bool current_read = digitalRead(2);      // value from encoder pulse
  if((previous_read == 0) && (current_read == 1)) // detect rising leg
  {
    count++;
    Serial.println(count);
  }
  previous_read = current_read;
  
  speedMotor(-20);        // edit HERE
}
