#pragma once

#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

extern GLBI_Engine myEngine;

void initStartScreen();
void drawStartScreen();
bool isStartScreenActive();
void setStartScreenActive(bool active);