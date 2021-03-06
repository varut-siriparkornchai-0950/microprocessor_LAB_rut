int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, LP, RP,permis;
int leftP=4, rightP=5;
int posi = 0, poten; 

void updateDATA(uint16_t updata);
int posy(int pos, int direction);

void setup() {
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
 pinMode(leftP,INPUT);
 pinMode(rightP,INPUT);
 pinMode(A0,INPUT);
 Serial.begin(9600);
}

void loop() 
{ 
  LP = digitalRead(leftP);
  RP = digitalRead(rightP);
  
  if(LP == 0 || permis == 4)
  {
    posi = posy(posi,4,permis);
  }
  else if(RP == 0 || permis == 6)
  {
    posi = posy(posi,6,permis);
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

int posy(int pos,int direction, int &permis)
{
  if(direction == 4)
  {
    for(pos; pos<=15; pos++)
    {
      RP = digitalRead(rightP);
      poten = analogRead(A0);
      led = 0x1 << pos;
      updateDATA(led);
      delay(poten);
      
      if(pos == 15)
      {
        pos = -1;
      }
      
      if(RP == 0)
      {
        permis = 6;
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
        poten = analogRead(A0);
        LP = digitalRead(leftP);
        led = 0x1 << pos;
        updateDATA(led);
        delay(poten);
        if(LP == 0)
        {
          permis = 4;
          break;
        }
        
      }
    }
  return pos;
}
