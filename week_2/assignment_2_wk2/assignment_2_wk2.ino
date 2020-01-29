
int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, LP, RP;
int leftP=4, rightP=5;
int posi = 0; 

void updateDATA(uint16_t updata);
int posy(int pos, int direction);

void setup() {
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
 pinMode(leftP,INPUT);
 pinMode(rightP,INPUT);
 Serial.begin(9600);
}

void loop() 
{ 
  LP = digitalRead(leftP);
  RP = digitalRead(rightP);
  
  if(LP == 0)
  {
    posi = posy(posi,4);
  }
  else if(RP == 0)
  {
    posi = posy(posi,6);
  }

}      //  end void loop()


//____________________________________________FUNCTION BELOW___________________________

void updateDATA(uint16_t updata)
{
 digitalWrite(latch_pin,LOW);
 for(int i = 0 ; i < 16 ; i++)
 {
  digitalWrite(data_pin,(updata>>(15-i)) & 0b0000000000000001);      // & 0x01 for checking last bit, is that True?
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
 }
 digitalWrite(latch_pin,HIGH);
 delay(100);
}

int posy(int pos,int direction)
{
  if(direction == 4)
  {
    for(pos; pos<=15; pos++)
    {
      RP = digitalRead(rightP);
      led = 0x1 << pos;
      updateDATA(led);
      delay(200);
      
      if(pos == 15)
      {
        pos = -1;
      }
      
      if(RP == 0)
      {
        break;
      }
    }
  } 
  else if(direction == 6)
    {
      for(pos; pos<=16; --pos)
      {
        if(pos == -1)
        {
          pos = 15;
        }
        else if(pos == -2)
        {
          pos = 14;
        }
        LP = digitalRead(leftP);
        led = 0x1 << pos;
        updateDATA(led);
        delay(200);
        if(LP == 0)
        {
          break;
        }
        
      }
    }
  return pos;
}
