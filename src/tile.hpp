#pragma once

#include <string>
#include <vector>

enum class TileType {
    Empty,      // Bloc vide
    Solid,      // Bloc plein destructible
    Object,     // Objet à collecter
    Obstacle,   // Obstacle indestructible
    Trap        // Piège
};

class Tile {
public:
    Tile(TileType type, const std::string& spritePath);

    TileType getType() const;
    const std::string& getSpritePath() const;

private:
    TileType type;
    std::string spritePath; // Chemin vers le sprite
};