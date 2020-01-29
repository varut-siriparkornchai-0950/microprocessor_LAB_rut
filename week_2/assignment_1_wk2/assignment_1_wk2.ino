int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
int led, leftP=4, rightP=5, LP, RP;

void updateDATA(uint16_t updata);

void setup() {
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
 pinMode(leftP,INPUT);
 pinMode(rightP,INPUT);
 Serial.begin(9600);
}

void loop() {
  
  LP = digitalRead(leftP);
  RP = digitalRead(rightP);
  Serial.println(LP);
  
  for(int i=0;i<=15;i++)
  {
    led = 0x1 << i;
    updateDATA(led);
    delay(200);
  }
  
}      //  end void loop()

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
