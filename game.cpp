#include "config.h"
#include "game.h"

static int sequence[MAX_LEVEL];
static int level = 0;

void gameStart() {
  level = 0;
}

void gameAddStep() {
  if (level < MAX_LEVEL) {
    sequence[level] = random(NUM_COLORS);
    level++;
  }
}

int gameLevel() {
  return level;
}

int gameStepAt(int i) {
  return sequence[i];
}

bool gameCheck(int pos, int button) {
  return sequence[pos] == button;
}