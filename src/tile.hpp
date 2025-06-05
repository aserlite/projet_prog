#pragma once

#include <string>
#include <vector>

enum class TileType {
    Empty,
    Solid,
    Object,
    Obstacle,
    Trap
};

class Tile {
public:
    Tile(TileType type, const std::string& spritePath);

    TileType getType() const;
    const std::string& getSpritePath() const;

private:
    TileType type;
    std::string spritePath;
};