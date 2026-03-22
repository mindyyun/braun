
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

// These are 'flexible' lines that can be changed
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8 // RST can be set to -1 if you tie it to Arduino's reset

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// SoftSPI - note that on some processors this might be *faster* than hardware SPI!
//Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

// Forward declarations
unsigned long testText();
// unsigned long testLines(uint16_t color);
// unsigned long testRects(uint16_t color);
// unsigned long testCircles(uint8_t radius, uint16_t color);
// unsigned long testTriangles();
// unsigned long testFilledTriangles();
// unsigned long testRoundRects();
// unsigned long testFilledRoundRects();

void setup() {
  Serial.begin(9600);
  Serial.println("HX8357D Test!"); 

  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  
  Serial.println(F("Benchmark                Time (microseconds)"));

  tft.setRotation(1);

  Serial.print(F("Text                     "));
  Serial.println( testText());
  delay(500);

//   Serial.print(F("Lines                    "));
//   Serial.println(testLines(HX8357_CYAN));
//   delay(500);

//   Serial.print(F("Rectangles (outline)     "));
//   Serial.println(testRects(HX8357_GREEN));
//   delay(500);

//   tft.fillScreen(HX8357_BLACK);
//   Serial.print(F("Circles (outline)        "));
//   Serial.println(testCircles(10, HX8357_RED));
//   delay(500);


//   Serial.print(F("Triangles (outline)      "));
//   Serial.println(testTriangles());
//   delay(500);

//   Serial.print(F("Triangles (filled)       "));
//   Serial.println(testFilledTriangles());
//   delay(500);


//   Serial.print(F("Rounded rects (outline)  "));
//   Serial.println(testRoundRects());
//   delay(500);

//   Serial.print(F("Rounded rects (filled)   "));
//   Serial.println(testFilledRoundRects());
//   delay(500);

  Serial.println(F("Done!"));
}


void loop(void) {
  for(uint8_t rotation=0; rotation<2; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(4000);
  }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(HX8357_RED);
  tft.fillScreen(HX8357_GREEN);
  tft.fillScreen(HX8357_BLUE);
  tft.fillScreen(HX8357_WHITE);
  return micros() - start;
}


unsigned long testText() {
  tft.fillScreen(HX8357_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(8);
  tft.println("Hello World!");
  tft.setTextColor(HX8357_YELLOW); tft.setTextSize(4);
  tft.println(1234.56);
  tft.setTextColor(HX8357_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(HX8357_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  return micros() - start;
}

// unsigned long testLines(uint16_t color) {
//   unsigned long start;
//   int           x1, y1, x2, y2,
//                 w = tft.width(),
//                 h = tft.height();

//   tft.fillScreen(HX8357_BLACK);

//   x1 = y1 = 0;
//   y2    = h - 1;
//   start = micros();
//   for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
//   x2    = w - 1;
//   for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

//   return micros() - start;
// }

// unsigned long testFastLines(uint16_t color1, uint16_t color2) {
//   unsigned long start;
//   int           x, y, w = tft.width(), h = tft.height();

//   tft.fillScreen(HX8357_BLACK);
//   start = micros();
//   for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
//   for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

//   return micros() - start;
// }

// unsigned long testRects(uint16_t color) {
//   unsigned long start;
//   int           n, i, i2,
//                 cx = tft.width()  / 2,
//                 cy = tft.height() / 2;

//   tft.fillScreen(HX8357_BLACK);
//   n     = min(tft.width(), tft.height());
//   start = micros();
//   for(i=2; i<n; i+=6) {
//     i2 = i / 2;
//     tft.drawRect(cx-i2, cy-i2, i, i, color);
//   }

//   return micros() - start;
// }

// unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
//   unsigned long start, t = 0;
//   int           n, i, i2,
//                 cx = tft.width()  / 2 - 1,
//                 cy = tft.height() / 2 - 1;

//   tft.fillScreen(HX8357_BLACK);
//   n = min(tft.width(), tft.height());
//   for(i=n; i>0; i-=6) {
//     i2    = i / 2;
//     start = micros();
//     tft.fillRect(cx-i2, cy-i2, i, i, color1);
//     t    += micros() - start;
//     // Outlines are not included in timing results
//     tft.drawRect(cx-i2, cy-i2, i, i, color2);
//   }

//   return t;
// }

// unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
//   unsigned long start;
//   int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

//   tft.fillScreen(HX8357_BLACK);
//   start = micros();
//   for(x=radius; x<w; x+=r2) {
//     for(y=radius; y<h; y+=r2) {
//       tft.fillCircle(x, y, radius, color);
//     }
//   }

//   return micros() - start;
// }

// unsigned long testCircles(uint8_t radius, uint16_t color) {
//   unsigned long start;
//   int           x, y, r2 = radius * 2,
//                 w = tft.width()  + radius,
//                 h = tft.height() + radius;

//   // Screen is not cleared for this one -- this is
//   // intentional and does not affect the reported time.
//   start = micros();
//   for(x=0; x<w; x+=r2) {
//     for(y=0; y<h; y+=r2) {
//       tft.drawCircle(x, y, radius, color);
//     }
//   }

//   return micros() - start;
// }

// unsigned long testTriangles() {
//   unsigned long start;
//   int           n, i, cx = tft.width()  / 2 - 1,
//                       cy = tft.height() / 2 - 1;

//   tft.fillScreen(HX8357_BLACK);
//   n     = min(cx, cy);
//   start = micros();
//   for(i=0; i<n; i+=5) {
//     tft.drawTriangle(
//       cx    , cy - i, // peak
//       cx - i, cy + i, // bottom left
//       cx + i, cy + i, // bottom right
//       tft.color565(200, 20, i));
//   }

//   return micros() - start;
// }

// unsigned long testFilledTriangles() {
//   unsigned long start, t = 0;
//   int           i, cx = tft.width()  / 2 - 1,
//                    cy = tft.height() / 2 - 1;

//   tft.fillScreen(HX8357_BLACK);
//   start = micros();
//   for(i=min(cx,cy); i>10; i-=5) {
//     start = micros();
//     tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//       tft.color565(0, i, i));
//     t += micros() - start;
//     tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
//       tft.color565(i, i, 0));
//   }

//   return t;
// }

// unsigned long testRoundRects() {
//   unsigned long start;
//   int           w, i, i2,
//                 cx = tft.width()  / 2 ,
//                 cy = tft.height() / 2 ;

//   tft.fillScreen(HX8357_BLACK);
//   w     = min(tft.width(), tft.height());
//   start = micros();
//   for(i=0; i<w; i+=8) {
//     i2 = i / 2 - 2;
//     tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 100, 100));
//   }

//   return micros() - start;
// }

// unsigned long testFilledRoundRects() {
//   unsigned long start;
//   int           i, i2,
//                 cx = tft.width()  / 2 + 10,
//                 cy = tft.height() / 2 + 10;

//   tft.fillScreen(HX8357_BLACK);
//   start = micros();
//   for(i=min(tft.width(), tft.height()) - 20; i>25; i-=6) {
//     i2 = i / 2;
//     tft.fillRoundRect(cx-i2, cy-i2, i-20, i-20, i/8, tft.color565(100, i/2, 100));
//   }

//   return micros() - start;
//  }
