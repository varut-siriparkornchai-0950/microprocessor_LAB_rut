#include <ThreeWire.h>
#include <RtcDS1302.h>
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
int seecon,second,timer;
int printDateTime(const RtcDateTime& dt){
// Serial.print(dt.Year(), DEC);
// Serial.print('/');
// Serial.print(dt.Month(), DEC);
// Serial.print('/');
// Serial.print(dt.Day(), DEC);
// Serial.print(' ');
 Serial.print(dt.Hour(), DEC);
 Serial.print(':');
 Serial.print(dt.Minute(), DEC);
 Serial.print(':');
 Serial.print(dt.Second(), DEC);
 Serial.println();
// Serial.print("Total Seconds since 1/1/2000 : ");
// Serial.print(dt.TotalSeconds());
// Serial.println();
while(dt.Minute()>=1)
{
  Serial.println("STOP");
}
 dt.Second();
 return  dt.Second();
}

void setup(){
 Serial.begin(57600);
 Rtc.Begin();
 RtcDateTime setting_time(2020,2,2,0,0,0);
 // year, month, dayOfMonth, hour, minute, second
 printDateTime(setting_time);
 Serial.print("START !!!!!!!!!!");
 //Try to comment This line
 Rtc.SetDateTime(setting_time);
 //reset timer to "setting_time"
 pinMode(7,OUTPUT);
}

void loop() {
 
  digitalWrite(7,HIGH);   
  delay(1000);
  timer++; 
  Serial.println(timer);
  digitalWrite(7,LOW);
  delay(1000);
  timer++; 
  Serial.println(timer);
  if(timer >= 120)
  {
    Serial.println("STOP !!!!!");
  }
}



// result = 2.00.06 mins
