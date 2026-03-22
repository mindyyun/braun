#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define TFT_CS  10
#define TFT_DC   9
#define TFT_RST  8

int button1 = 7; // happy
int button2 = 6; // sad
int button3 = 5; // bored

// 0 = menu, 1 = happy, 2 = sad, 3 = bored
int currentState = 0;
int lastState = -1; // track last state to avoid redrawing every frame

// Previous button readings for edge detection
int prevButton1 = HIGH;
int prevButton2 = HIGH;
int prevButton3 = HIGH;

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

void showMenu();
void showHappy();
void showSad();
void showBored();

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

  // Detect HIGH -> LOW transitions (button press edges)
  bool pressed1 = (b1 == LOW && prevButton1 == HIGH);
  bool pressed2 = (b2 == LOW && prevButton2 == HIGH);
  bool pressed3 = (b3 == LOW && prevButton3 == HIGH);

  // State transitions on press
  if (currentState == 0) {
    if      (pressed1) currentState = 1;
    else if (pressed2) currentState = 2;
    else if (pressed3) currentState = 3;
  } else {
    // Any button press from a response screen returns to menu
    if (pressed1 || pressed2 || pressed3) {
      currentState = 0;
    }
  }

  // Only redraw when state changes
  if (currentState != lastState) {
    switch (currentState) {
      case 0: showMenu();  break;
      case 1: showHappy(); break;
      case 2: showSad();   break;
      case 3: showBored(); break;
    }
    lastState = currentState;
  }

  // Save previous button states for edge detection next iteration
  prevButton1 = b1;
  prevButton2 = b2;
  prevButton3 = b3;

  delay(20); // small debounce delay
}

void showMenu() {
  tft.fillScreen(0x8db1);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("(^._.^)");       // ASCII-safe kaomoji
  tft.println("How are you");
  tft.println("  feeling?");
  tft.setCursor(90, 200);
  tft.println("happy");
  tft.setCursor(90, 285);
  tft.println("sad");
  tft.setCursor(90, 380);
  tft.println("bored");
}

void showHappy() {
  tft.fillScreen(0xe5dc);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("(^ v ^)");       // happy face
  tft.println("I'm happy");
  tft.println("you're happy!");
}

void showSad() {
  tft.fillScreen(0xbebd);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("(T_T)");         // sad face
  tft.println("Cheer up!");
}

void showBored() {
  tft.fillScreen(0xed3d);
  tft.setTextColor(0xf713);
  tft.setTextSize(4);
  tft.setCursor(25, 50);
  tft.println("-_-");           // bored face
  tft.println("Womp womp.");
  tft.println("Do something");
  tft.println("about it!");
}