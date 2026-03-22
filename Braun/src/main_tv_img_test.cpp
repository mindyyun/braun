#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>   // swap for Adafruit_ILI9488.h if needed
#include <avr/pgmspace.h>
#include "main_tv.h"         // your generated header

#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

#define IMG_WIDTH  80
#define IMG_HEIGHT 60

void drawImageFromFlash(int16_t x, int16_t y) {
  tft.startWrite();
  tft.setAddrWindow(x, y, IMG_WIDTH, IMG_HEIGHT);

  for (uint32_t i = 0; i < (uint32_t)IMG_WIDTH * IMG_HEIGHT; i++) {
    uint16_t color = pgm_read_word(&image[i]);
    tft.pushColor(color);
  }

  tft.endWrite();
}

void setup() {
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(HX8357_BLACK);

  drawImageFromFlash(0, 0);
}

void loop() {
  // nothing needed
}