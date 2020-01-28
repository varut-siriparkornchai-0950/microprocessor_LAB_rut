int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
bool toggle=0;
byte led;

void updateDATA(uint8_t updata);

void setup() {
 pinMode(clk_pin,OUTPUT);
 pinMode(latch_pin,OUTPUT);
 pinMode(data_pin,OUTPUT);
}
void loop() {
  led = 0b00000001;
  delay(500);
  for(int i=0;i<=7;++i)
  {
    updateDATA(led);
    led = led << 1 ;
    delay(500);
  }
}

void updateDATA(uint8_t updata){
 digitalWrite(latch_pin,LOW);
 for(int i = 0 ; i < 8 ; i++){
  digitalWrite(data_pin,(updata>>(7-i)) & 0x01);      // & 0x01 for checking last bit, is that True?
  digitalWrite(clk_pin,HIGH);
  digitalWrite(clk_pin,LOW);
 }
 digitalWrite(latch_pin,HIGH);
 delay(100);
}
