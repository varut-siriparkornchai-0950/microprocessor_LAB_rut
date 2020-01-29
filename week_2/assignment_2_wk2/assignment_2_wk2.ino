int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, a0, a1;

void updateDATA(uint16_t updata);
void LEDup(int position_LED);

void setup() {
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
}

void loop() {
  
  a0 = digitalRead(A0);
  a1 = digitalRead(A1);
  
  if(a0 == 0 && a1 == 1)
  {
    for(int i = 0; i<=15; i++)
    {
      a1 = digitalRead(A1);
     if(a1 == 1)
     {
       led = LEDup(i);
       updateDATA(led);
     }
     else
     {
       break;
     }
    }
  }
 /* led = 0b0000000000000001;
  delay(500);
  for(int i=0;i<=15;i++)
  {
    updateDATA(led);
    led = led << 1 ;
    delay(500);
  }*/
 // updateDATA(0x9FF9);
    
}


/*int8_t
uint8_t
int16_t

0b1000 0000 >> 7 = 0b0000 0001
0b1110 0000 >> 4 = 0b0000 1110 -> & 0b0000 0001*/

void updateDATA(uint16_t updata){
 digitalWrite(latch_pin,LOW);
 for(int i = 0 ; i < 16 ; i++){
  digitalWrite(data_pin,(updata>>(15-i)) & 0b0000000000000001);      // & 0x01 for checking last bit, is that True?
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
 }
 digitalWrite(latch_pin,HIGH);
 delay(100);
}
    
void LEDup(int position_LED)                //function shift position
{
  int LED=0b0000000000000001;
  if(position_LED>=0 && position_LED<=5)
  {
    PORTD = LED << position_LED;
    delay(500);
  }
}
