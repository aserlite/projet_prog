#pragma once

#include <vector>
#include <string>

enum class TileType {
    Empty,
    Solid,
    Object,
    Trap
};

class Tile {
public:
    Tile(TileType type = TileType::Empty);
    TileType getType() const;

private:
    TileType type;
};

class TileMap {
public:
    TileMap(int width, int height);
    void generateProceduralMap(float fillProbability, int iterations);
    const Tile& getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
    std::vector<std::vector<Tile>> map;
    void fillEnclosedEmptySpaces();
    int countFilledNeighbors(int x, int y) const;
};