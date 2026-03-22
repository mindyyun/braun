#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>   // driver for Adafruit 3.5" TFT
#include "tv_bw.h"

// Pin definitions for Uno (hardware SPI)
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// Image dimensions — must match what you exported
#define IMG_W  100
#define IMG_H   80

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(HX8357_BLACK);

  // drawBitmap(x, y, bitmap_ptr, w, h, fg_color, bg_color)
  // fg = WHITE pixels in your bitmap, bg = BLACK pixels
  // x and y are where to start the display, is at 0, 0 rn
  tft.drawBitmap(0, 0, tv_bw, 320, 282, 0xFFFF, 0x0000);  // foreground=WHITE, background=BLACK
}

void loop() {
  // nothing — image is static
}