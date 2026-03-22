#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#define TFT_CS  10
#define TFT_DC   9
#define TFT_RST  8
int button1 = 7; // happy / yes "not bored"
int button2 = 6; // sad
int button3 = 5; // bored / keep clicking
// 0 = menu, 1 = happy, 2 = sad, 3 = bored, 4 = bored counter, 5 = still bored check, 6 = yay
int currentState = 0;
int lastState = -1;
int boredCount = 0;
int boredRound = 0; // tracks how many rounds of 10 they've done
int lastBoredCount = -1; // to avoid redrawing counter every frame

int prevButton1 = HIGH;
int prevButton2 = HIGH;
int prevButton3 = HIGH;

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

void showMenu();
void showHappy();
void showSad();
void showBored();
void showBoredCounter();
void showStillBored();
void showYay();

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(0);
}

void loop() {
  int b1 = digitalRead(button1);
  int b2 = digitalRead(button2);
  int b3 = digitalRead(button3);

  bool pressed1 = (b1 == LOW && prevButton1 == HIGH);
  bool pressed2 = (b2 == LOW && prevButton2 == HIGH);
  bool pressed3 = (b3 == LOW && prevButton3 == HIGH);

  switch (currentState) {
    case 0: // Menu
      if      (pressed1) { currentState = 1; }
      else if (pressed2) { currentState = 2; }
      else if (pressed3) {
        boredCount = 0;
        boredRound = 0;
        lastBoredCount = -1;
        currentState = 3;
      }
      break;

    case 1: // Happy
    case 2: // Sad
      if (pressed1 || pressed2 || pressed3) currentState = 0;
      break;

    case 3: // Bored landing screen
      if (pressed3) {
        boredCount = 0;
        lastBoredCount = -1;
        currentState = 4;
      } else if (pressed1 || pressed2) {
        currentState = 0;
      }
      break;

    case 4: // Bored counter (clicking up to 10)
      if (pressed3) {
        boredCount++;
        lastBoredCount = -1; // force redraw of counter
        if (boredCount >= 10) {
          boredRound++;
          currentState = 5; // ask if still bored
        }
      }
      break;

    case 5: // Still bored check
      if (pressed3) {
        // Yes, still bored — do another 10
        boredCount = 0;
        lastBoredCount = -1;
        currentState = 4;
      } else if (pressed1) {
        // No, not bored anymore!
        currentState = 6;
      }
      break;

    case 6: // Yay!
      if (pressed1 || pressed2 || pressed3) currentState = 0;
      break;
  }

  // Redraw full screen only on state change
  if (currentState != lastState) {
    switch (currentState) {
      case 0: showMenu();        break;
      case 1: showHappy();       break;
      case 2: showSad();         break;
      case 3: showBored();       break;
      case 4: showBoredCounter(); break;
      case 5: showStillBored();  break;
      case 6: showYay();         break;
    }
    lastState = currentState;
  }

  // In counter state, redraw only the count number when it changes
  if (currentState == 4 && boredCount != lastBoredCount) {
    // Erase old number area and redraw count
    tft.fillRect(0, 220, 320, 80, 0x8db1);
    tft.setTextColor(0xf713);
    tft.setTextSize(6);
    // Center the number
    int digitWidth = (boredCount >= 10) ? 2 : 1;
    int xPos = (320 - digitWidth * 36) / 2;
    tft.setCursor(xPos, 230);
    tft.println(boredCount);
    lastBoredCount = boredCount;
  }

  prevButton1 = b1;
  prevButton2 = b2;
  prevButton3 = b3;
  delay(20);
}

void showMenu() {
  tft.fillScreen(0x7bec);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(50, 50);
  tft.println("(^._.^)");
  tft.setCursor(25, 80);
  tft.println("How are you");
  tft.println("  feeling?");

  uint16_t pinkFill   = 0xFBB6;
  uint16_t pinkBorder = 0xF8B2;

  tft.fillRoundRect(25, 195, 200, 50, 8, 0xa632);
  tft.drawRoundRect(25, 195, 200, 50, 8, pinkBorder);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(60, 205);
  tft.println("happy");

  tft.fillRoundRect(25, 280, 200, 50, 8, 0xa632);
  tft.drawRoundRect(25, 280, 200, 50, 8, pinkBorder);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(60, 290);
  tft.println("sad");

  tft.fillRoundRect(25, 375, 200, 50, 8, 0xa632);
  tft.drawRoundRect(25, 375, 200, 50, 8, pinkBorder);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(60, 385);
  tft.println("bored");
}

void showHappy() {
  tft.fillScreen(0xcd71);
  tft.setTextColor(0xf77c);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("(^ v ^)");
  tft.println("I'm happy");
  tft.println("you're happy!");
}

void showSad() {
  tft.fillScreen(0x95fd);
  tft.setTextColor(0xf77c);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("(T_T)");
  tft.println("Cheer up!");
}

void showBored() {
  tft.fillScreen(0x731d);
  tft.setTextColor(0xf77c);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("-_-");
  tft.println("Womp womp.");
  tft.println("Do something");
  tft.println("about it!");
  tft.setTextSize(2);
  tft.setCursor(25, 280);
  tft.println("(press 3 to try)");
}

void showBoredCounter() {
  tft.fillScreen(0x731d);
  tft.setTextColor(0xf77c);
  tft.setTextSize(3);
  tft.setCursor(10, 50);
  tft.println("Keep clicking!");
  tft.setTextSize(2);
  tft.setCursor(10, 110);
  tft.println("Get to 10...");
  if (boredRound > 0) {
    tft.setCursor(10, 140);
    tft.print("Round ");
    tft.println(boredRound + 1);
  }
  // Count display area is drawn in loop() to update smoothly
}

void showStillBored() {
  tft.fillScreen(0x731d);
  tft.setTextColor(0xf77c);
  tft.setTextSize(3);
  tft.setCursor(20, 60);
  tft.println("Still bored?");
  tft.setTextSize(2);
  tft.setCursor(20, 150);
  tft.println("Press 3: yes :(");
  tft.setCursor(20, 180);
  tft.println("Press 1: no! :)");
}

void showYay() {
  tft.fillScreen(0xd63c);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(40, 80);
  tft.println("(^ v ^)");
  tft.setCursor(40, 160);
  tft.println("YAY!");
  tft.setTextSize(3);
  tft.setCursor(20, 230);
  tft.println("Not bored");
  tft.println("anymore!");
  tft.setTextSize(2);
  tft.setCursor(20, 330);
  tft.println("press any button");
}