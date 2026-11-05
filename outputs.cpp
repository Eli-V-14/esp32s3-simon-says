#include "config.h"
#include "outputs.h"

static unsigned long offAt = 0;
static bool busy = false;

static void allOff() {
  for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], LOW);
  noTone(BUZZER_PIN);
}

void outputsBegin() {
  for (int i = 0; i < NUM_COLORS; i++) pinMode(LED_PINS[i], OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  allOff();
}

void playStep(int i, unsigned long ms) {
  allOff();
  digitalWrite(LED_PINS[i], HIGH);
  tone(BUZZER_PIN, TONES[i]);
  offAt = millis() + ms;
  busy = true;
}

void playAll(unsigned long ms) {
  allOff();
  for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], HIGH);
  tone(BUZZER_PIN, 120);
  offAt = millis() + ms;
  busy = true;
}

void outputsUpdate() {
  if (busy && (long)(millis() - offAt) >= 0) {
    allOff();
    busy = false;
  }
}

bool outputsBusy() {
  return busy;
}