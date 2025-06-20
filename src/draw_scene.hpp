#pragma once

#include "tile_map.hpp"
#include "glbasimac/glbi_engine.hpp"

using namespace glbasimac;

extern GLBI_Engine myEngine;

extern TileMap* globalMap;

void drawScene();
void drawSquare(float x, float y, float size, float r, float g, float b);

void initScene();