#pragma once
#include "tile_map.hpp"
#include <string>

class Enemy {
public:
    Enemy(float x, float y, float speed, const std::string& spritePath);

    void update(float deltaTime, const TileMap& map, const std::vector<std::vector<std::pair<int, int>>>& flowField);
    float getX() const;
    float getY() const;
    const std::string& getSpritePath() const;

private:
    float x, y;
    float speed;
    std::string spritePath;
};