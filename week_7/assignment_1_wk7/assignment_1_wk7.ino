#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define sw_L 6
#define sw_R 7
int switch1, switch2;
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void homer(void){
  display.clearDisplay();                 // you must clear display before draw everything on display. if not display still is keeping buffer previously
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,15);
  display.println("switch 1 -->");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,43);
  display.println("switch 2 -->");
  
  display.drawCircle(100, 46, 10, WHITE);
  display.drawCircle(100, 18, 10, WHITE);
}


void setup() {
  pinMode(sw_L, INPUT);
  pinMode(sw_R, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
     Serial.println("SSD1306 allocation failed");
     for(;;);
  }
  delay(1000);
  display.clearDisplay(); // clears the screen and buffer  
  display.display();    // method to display the text on screen
}

void loop(){
  circle();
}

void circle(void){
    switch1 = digitalRead(sw_L);
    switch2 = digitalRead(sw_R);
    Serial.print(switch1);
  
    if(switch1 == 0)
    {
      display.fillCircle(100, 18, 10, WHITE);  // drawCircle(position-x, position-y, radius, color)
      display.drawCircle(100, 46, 10, WHITE);
      if(switch1 == 0 && switch2 == 0)
      {
        display.fillCircle(100, 18, 10, WHITE);
        display.fillCircle(100, 46, 10, WHITE);
      }
    }
    else if(switch2 == 0)
    {
      display.fillCircle(100, 46, 10, WHITE);
      display.drawCircle(100, 18, 10, WHITE);
      if(switch1 == 0 && switch2 == 0)
      {
        display.fillCircle(100, 18, 10, WHITE);
        display.fillCircle(100, 46, 10, WHITE);
      }
    }
    else
    {
      homer();
    }
    display.display();
    
}
