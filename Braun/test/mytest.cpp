#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

// These are 'flexible' lines that can be changed
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8 // RST can be set to -1 if you tie it to Arduino's reset

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);



// Forward declarations
unsigned long testText();

void setup() {
  Serial.begin(9600);
  Serial.println("HX8357D Test!"); 

  tft.begin();

}


void loop(void) {
  
  testText();
  delay(400000);

}


unsigned long testText() {
  tft.fillScreen(0xe61b);
  //unsigned long start = micros();
  tft.setCursor(25, 50);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(4);
  tft.println("How are you \n   feeling?");

  tft.setCursor(90, 200);
  tft.setTextColor(HX8357_RED); tft.setTextSize(4);
  tft.println("happy");

  tft.println();
  tft.setCursor(90, 285);
  tft.setTextColor(HX8357_GREEN);    tft.setTextSize(4);
  tft.println("sad");
  tft.println();
  tft.setCursor(90, 380);
  tft.setTextColor(HX8357_BLUE);
  tft.setTextSize(4);
  tft.println("bored");
  //return micros() - start;
}