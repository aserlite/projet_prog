#pragma once

#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

extern GLBI_Engine myEngine;

void initWinScreen();
void drawWinScreen(int score, float timeSeconds);
bool isWinScreenActive();
void setWinScreenActive(bool active);
int handleWinScreenClick(float mouseX, float mouseY);