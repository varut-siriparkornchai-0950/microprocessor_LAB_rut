#define LED1 11
#define LED2 10
#define INT_PIN 3

int toggle=1;

void ISR_Callback()           // come here when INT_PIN was not avariable(not emptry)
{
  digitalWrite(LED2, toggle);
  toggle= !toggle;            // meaning "toggle = negative toggle"
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(INT_PIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN), 
                            ISR_Callback, RISING);    // RISING(0v -> 5v) or FALLING(5v -> 0v) or CHANGE(0v -> 5v or 5v -> 0v)
}

void loop()
{
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);
}
