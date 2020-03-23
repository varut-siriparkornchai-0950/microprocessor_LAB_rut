#define LED_PIN1 11
#define LED_PIN2 10
int LED_PIN,c=0;
float brightness = 0;
String buff;

void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if(inByte == 'L')
    {
       c = 0;
    }
    if((inByte =='1')&&(c == 1))
    {
      LED_PIN = LED_PIN1;
    }
    if(inByte =='2'&&(c == 1))
    {
      LED_PIN = LED_PIN2;
    }
    if(inByte =='B')
    {
      buff = " ";
    }
    if(('0'<= inByte) && (inByte <= '9'))
    {
      buff += inByte;
    }
    if(inByte == 'n')
    {
       brightness = buff.toInt();
       Serial.println(brightness);
       analogWrite(LED_PIN,int(brightness*2.54));
    }
    c++;
  }
}
