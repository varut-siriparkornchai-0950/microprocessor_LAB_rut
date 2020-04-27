#define LED1 11
#define INT_PIN 3

int timedelay=1000, mode=1;

void ISR_Callback()           // come here when INT_PIN was not avariable(not emptry)
{
  if(mode>=3)
  {
    mode=1;
    timedelay = 0;
  }
  timedelay = timedelay+1000;
  mode++;
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_Callback, RISING);    // RISING(0v -> 5v) or FALLING(5v -> 0v) or CHANGE(0v -> 5v or 5v -> 0v)
}

void loop()
{
  digitalWrite(LED1, HIGH);
  delay(timedelay);
  digitalWrite(LED1, LOW);
  delay(timedelay);
  
  Serial.println(timedelay);
}
