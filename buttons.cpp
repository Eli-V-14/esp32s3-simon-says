#include "config.h"
#include "buttons.h"

static bool lastState[NUM_COLORS + 1];
static unsigned long lastChange[NUM_COLORS + 1];
static bool pressedFlag[NUM_COLORS + 1];

void buttonsBegin() {
  for(int i = 0; i <= NUM_COLORS; i++) {
    pinMode(BTN_PINS[i], INPUT_PULLUP);
    lastState[i] = HIGH; // HIGH = not pressed
  }
}

void buttonsUpdate(bool ignoreLit) {
  for (int i = 0; i <= NUM_COLORS; i++) {
    if (ignoreLit && i < NUM_COLORS) continue;

    bool raw = digitalRead(BTN_PINS[i]);

    if(raw != lastState[i] && millis() - lastChange[i] > DEBOUNCE_MS) {
      lastChange[i] = millis();
      lastState[i] = raw;
      if (raw == LOW) pressedFlag[i] = true; // counts presses
    }
  }
}

bool buttonPressed(int i) {
  if (pressedFlag[i]) {
    pressedFlag[i] = false;
    return true;
  }
  return false;
}

void buttonsClear() {
  for (int i = 0; i <= NUM_COLORS; i++) pressedFlag[i] = false;
}