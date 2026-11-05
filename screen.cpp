#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "screen.h"

static Adafruit_SSD1306 display(128, 64, &Wire, -1);

void screenBegin() {
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found - check SDA/SCL wiring");
  }
  display.setTextColor(SSD1306_WHITE);
}

void screenIdle(int best) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("SIMON SAYS");
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Press START");
  display.setCursor(0, 48);
  display.print("Best: ");
  display.print(best);
  display.display();
}

void screenLevel(int level, const char* msg) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Level");
  display.setTextSize(1);
  display.setCursor(0, 14);
  display.print(level);
  display.setCursor(0, 54);
  display.print(msg);
  display.display();
}

void screenGameOver(const char* title, int score, int best) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(title);
  display.setTextSize(1);
  display.setCursor(0, 28);
  display.print("Score: ");
  display.print(score);
  display.setCursor(0, 42);
  display.print("Best: ");
  display.print(best);
  display.display();
}