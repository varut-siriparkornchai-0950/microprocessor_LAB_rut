
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
       buff = " ";
       Serial.println("L");
    }
    if((inByte =='1')&&(c == 1))
    {
      buff = " ";
      LED_PIN = LED_PIN1;
      Serial.println("1 pos");
    }
    if(inByte =='2'&&(c == 1))
    {
      buff = " ";
      LED_PIN = LED_PIN2;
      Serial.println("2 pos");
    }
    if(inByte =='B')
    {
      buff = " ";
      Serial.println("B");
    }
    if(('0'<= inByte) && (inByte <= '9'))
    {
      buff += inByte;
      Serial.println("count");
      Serial.println(buff);
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
