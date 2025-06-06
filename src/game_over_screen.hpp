#pragma once

#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

extern GLBI_Engine myEngine;

void initGameOverScreen();
void drawGameOverScreen(int score, float timeSeconds);
bool isGameOverScreenActive();
void setGameOverScreenActive(bool active);
int handleGameOverScreenClick(float mouseX, float mouseY);