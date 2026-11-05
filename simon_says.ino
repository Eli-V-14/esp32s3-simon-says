#include <Preferences.h>
#include "config.h"
#include "buttons.h"
#include "outputs.h"
#include "screen.h"
#include "game.h"

enum State { IDLE, SHOWING, WAITING, GAME_OVER };
State state = IDLE;

unsigned long nextAt = 0;  // when the next timed action is due
int showIdx = 0;           // which step of the sequence is being shown
int inputPos = 0;          // which step the player is on
int highScore = 0;
Preferences prefs;         // flash storage, survives power loss

bool due() {
  return (long)(millis() - nextAt) >= 0;
}

void enterIdle() {
  state = IDLE;
  buttonsClear();
  screenIdle(highScore);
}

void enterShowing() {
  state = SHOWING;
  showIdx = 0;
  nextAt = millis() + 600;
  screenLevel(gameLevel(), "Watch...");
}

void enterWaiting() {
  state = WAITING;
  inputPos = 0;
  buttonsClear();  // drop any presses made while the sequence was playing
  screenLevel(gameLevel(), "Your turn");
}

void enterGameOver(bool won) {
  state = GAME_OVER;
  int score = won ? gameLevel() : gameLevel() - 1;  // rounds completed
  if (score > highScore) {
    highScore = score;
    prefs.putInt("best", highScore);
  }
  screenGameOver(won ? "YOU WIN!" : "GAME OVER", score, highScore);
  playAll(800);
  nextAt = millis() + 3000;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("1: start");
  outputsBegin();
  Serial.println("2: outputs ok");
  buttonsBegin();
  Serial.println("3: buttons ok");
  screenBegin();
  Serial.println("4: screen ok");
  prefs.begin("simon", false);
  highScore = prefs.getInt("best", 0);
  Serial.println("5: prefs ok");
  enterIdle();
  Serial.println("6: idle drawn");
}

void loop() {
  outputsUpdate();
  buttonsUpdate(outputsBusy());

  switch (state) {
    case IDLE:
      if (buttonPressed(START_BTN)) {
        gameStart();
        gameAddStep();
        enterShowing();
      }
      break;

    case SHOWING:
      if (due()) {
        if (showIdx < gameLevel()) {
          playStep(gameStepAt(showIdx), 400);
          showIdx++;
          nextAt = millis() + 600;  // 400 on + 200 gap
        } else {
          enterWaiting();
        }
      }
      break;

    case WAITING:
      for (int i = 0; i < NUM_COLORS; i++) {
        if (!buttonPressed(i)) continue;
        playStep(i, 250);
        if (!gameCheck(inputPos, i)) {
          enterGameOver(false);
          break;
        }
        inputPos++;
        if (inputPos == gameLevel()) {  // finished this round
          if (gameLevel() >= MAX_LEVEL) {
            enterGameOver(true);
          } else {
            gameAddStep();
            enterShowing();
          }
        }
        break;
      }
      break;

    case GAME_OVER:
      if (due()) enterIdle();
      break;
  }
}