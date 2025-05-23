#include "tile_map.hpp"
#include <random>
#include <iostream>

Tile::Tile(TileType type) : type(type) {}

TileMap::TileMap(int width, int height)
    : width(width), height(height), map(height, std::vector<Tile>(width)) {}

    void TileMap::generateProceduralMap(float fillProbability, int iterations) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
    
        // Génération de la carte
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (dis(gen) < fillProbability) {
                    map[y][x] = Tile(TileType::Solid);
                } else {
                    map[y][x] = Tile(TileType::Empty);
                }
            }
        }
    
        // Règles de voisinage
        for (int iter = 0; iter < iterations; ++iter) {
            std::vector<std::vector<Tile>> newMap = map;
    
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int filledNeighbors = countFilledNeighbors(x, y);
                    if (map[y][x].getType() == TileType::Solid) {
                        if (filledNeighbors < 5) {
                            newMap[y][x] = Tile(TileType::Empty);
                        }
                    } else {
                        if (filledNeighbors > 4) {
                            newMap[y][x] = Tile(TileType::Solid);
                        }
                    }
                }
            }
    
            map = newMap;
        }
    
        std::cout << "Map visualization:" << std::endl;
        for (int y = height - 1; y >= 0; --y) {
            for (int x = 0; x < width; ++x) {
                TileType type = map[y][x].getType();
                if (type == TileType::Empty) {
                    std::cout << "."; // Case vide
                } else if (type == TileType::Solid) {
                    std::cout << "#"; // Obstacle destructible
                } else if (type == TileType::Object) {
                    std::cout << "O"; // Objet à collecter
                } else if (type == TileType::Trap) {
                    std::cout << "X"; // Piège
                } else {
                    std::cout << "?"; // Type inconnu
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

int TileMap::countFilledNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (map[ny][nx].getType() == TileType::Solid) {
                    ++count;
                }
            }
        }
    }
    return count;
}

const Tile& TileMap::getTile(int x, int y) const {
    return map[y][x];
}

int TileMap::getWidth() const {
    return width;
}

int TileMap::getHeight() const {
    return height;
}