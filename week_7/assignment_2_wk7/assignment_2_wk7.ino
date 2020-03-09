#include <ThreeWire.h>
#include <RtcDS1302.h>
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int tellingTime(const RtcDateTime& dt){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,15);
  display.println("year: "+String(dt.Year()));
  display.setCursor(10,23);
  display.println("month: "+String(dt.Month()));
  display.setCursor(10,31);
  display.println("day: "+String(dt.Day()));
  display.setCursor(10,39);
  display.println("hour: "+String(dt.Hour()));
  display.setCursor(10,47);
  display.println("minute: "+String(dt.Minute()));
  display.setCursor(10,55);
  display.println("second: "+String(dt.Second()));
  display.display();
}

void setup() {

 Rtc.Begin();
 RtcDateTime(__DATE__, __TIME__);
  
 display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
     Serial.println("SSD1306 allocation failed");
     for(;;);
  }
  delay(1000);
  display.clearDisplay(); // clears the screen and buffer  
  display.display();    // method to display the text on screen
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); // read datetime
  tellingTime(now);
}
