  #include<SPI.h>
  #define ss_pin1 10 //STCP storage register clock input
  #define ss_pin2 9
  #define data_pin 11 //DS serial data input
  #define clock_pin 13 // SHCP shift register clock input

  byte number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  int a=0;
  void Led1(uint8_t led1)
  {
    shiftOut(data_pin, clock_pin, MSBFIRST, led1);
    digitalWrite(ss_pin1, HIGH);
    digitalWrite(ss_pin1, LOW);
  }
  void Led2(uint8_t led2)
  {
    shiftOut(data_pin, clock_pin, MSBFIRST, led2);
    digitalWrite(ss_pin2, HIGH);
    digitalWrite(ss_pin2, LOW);
  }

  void setup() {
    pinMode(clock_pin,OUTPUT);
    pinMode(ss_pin1,OUTPUT);
    pinMode(ss_pin2,OUTPUT);
    pinMode(data_pin,OUTPUT);
    Led1(0x3F);
    Led2(0x3F);
  }

void show_num()
{
  int x1,x2;
  Led1(number[2]);
  Led2(number[1]);
}
  void loop() {

    show_num();

  }
