#pragma once
#include "tile_map.hpp"
#include <vector>
#include <utility>

std::vector<std::vector<std::pair<int, int>>> computeFlowField(const TileMap& map, int destX, int destY);