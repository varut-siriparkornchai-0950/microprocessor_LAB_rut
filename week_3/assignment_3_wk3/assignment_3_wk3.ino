int clk_pin = 10; //SHCP
int latch_pin = 9; //STCP
int data_pin = 8; //DS
byte number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int pos = 0, leftp = 7, rightp = 6, left, right;
String check0 = "open", check1 = "open"; 

void setLed(uint8_t _state)
{
  digitalWrite(latch_pin,LOW);
  for(int i = 0 ; i < 8 ; i++){
  digitalWrite(data_pin,(_state >> (7-i)) & 0x01);
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH);
}

void setup() {
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  pinMode(leftp, INPUT);
  pinMode(rightp, INPUT);
  Serial.begin(9600);
  setLed(0x3F);
}

void loop() {
  left = digitalRead(leftp);
  right = digitalRead(rightp);
  
  playnum(pos);                                 //turn-on LED

//     _________Door of filter clicker_________

  if((left == 1)&&(check0 == "open"))         //A0 button   DOOR open & finger up
  {
    check0 = "close";
  }
  else if((left == 0)&&(check0 == "close"))   // DOOR close & finger down
  {
    pos++;
    check0 = "open";
  }
  else if((right == 1)&&(check1 =="open"))      //A1 button   DOOR open & finger up 
  {
    check1 = "close";
  }
  else if((right == 0)&&(check1 == "close"))   // DOOR close & finger down
  {
    pos--;
    check1 = "open";
  }
}

void playnum(int pos)
{
  if(pos == -1)
  {
    pos = 9;
  }
  else if(pos == 10)
  {
    pos = 0;
  }
  setLed(number[pos]);
}
