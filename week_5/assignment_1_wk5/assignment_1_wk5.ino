  #include<SPI.h>
  #define ss_pin 10 //STCP storage register clock input
  #define data_pin 11 //DS serial data input
  #define clock_pin 13 // SHCP shift register clock input

  byte number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  int a=0,pos = 0, leftp = 7, rightp = 6, left, right;
  String check0 = "open", check1 = "open"; 

  void setLed(uint8_t led)
  {
    shiftOut(data_pin, clock_pin, MSBFIRST, led);
    digitalWrite(ss_pin, HIGH);
    digitalWrite(ss_pin, LOW);
  }

  void setup() {
    pinMode(clock_pin,OUTPUT);
    pinMode(ss_pin,OUTPUT);
    pinMode(data_pin,OUTPUT);
    setLed(0x3F);
  }

  void loop() {

    if(a==10)
    {
      a=0;
    }
    setLed(number[a]);
    delay(500);
    a++;
  }
