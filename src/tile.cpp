#include "tile.hpp"

Tile::Tile(TileType type, const std::string& spritePath)
    : type(type), spritePath(spritePath) {}

TileType Tile::getType() const {
    return type;
}

const std::string& Tile::getSpritePath() const {
    return spritePath;
}