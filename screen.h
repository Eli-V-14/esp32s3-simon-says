#pragma once

void screenBegin();
void screenIdle(int best);
void screenLevel(int level, const char* msg);
void screenGameOver(const char* title, int score, int best);