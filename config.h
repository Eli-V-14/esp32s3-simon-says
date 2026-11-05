#pragma once
#include <Arduino.h>

const int NUM_COLORS = 4;

// Outputs: each drives one lit button's LED anode
const int LED_PINS[NUM_COLORS] = {40, 41, 38, 37}; // green, red, yellow, blue

// Inputs: each lit button's switch (same color order as LED_PINS), the START last
const int BTN_PINS[NUM_COLORS + 1] = {15, 16, 17, 18, 0};
const int START_BTN = 4; // index of the START button

const int BUZZER_PIN = 45;
const int SDA_PIN = 13;
const int SCL_PIN = 12;

const int TONES[NUM_COLORS] = {262, 330, 392, 494};

const unsigned long DEBOUNCE_MS = 20;
const int MAX_LEVEL = 32;