#include "enemy.hpp"
#include <random>
#include <cmath>
#include <algorithm>
#include <iostream>

Enemy::Enemy(float x, float y, float speed, const std::string& spritePath)
    : x(x), y(y), speed(speed), spritePath(spritePath), stuckFrames(0) {}

float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }
const std::string& Enemy::getSpritePath() const { return spritePath; }

void Enemy::update(float deltaTime, const TileMap& map, const std::vector<std::vector<std::pair<int, int>>>& flowField) {
    float size = 1.9f;

    float centerX = x + size / 2.0f;
    float centerY = y + size / 2.0f;
    int tileX = static_cast<int>(centerX);
    int tileY = static_cast<int>(centerY);

    if (tileX < 0 || tileX >= map.getWidth() || tileY < 0 || tileY >= map.getHeight())
        return;

    auto dir = flowField[tileY][tileX];
    int nextX = dir.first;
    int nextY = dir.second;

    // Si déjà à destination ou pas de direction
    if (nextX == tileX && nextY == tileY) {
        stuckFrames++;
        return;
    }

    // Vérifie que la case cible est traversable
    TileType t = map.getTile(nextX, nextY).getType();
    if (t == TileType::Solid || t == TileType::Obstacle) {
        stuckFrames++;
        return;
    }

    // Calcul direction vers le centre de la prochaine case
    float targetX = nextX + 0.5f;
    float targetY = nextY + 0.5f;
    float dx = targetX - centerX;
    float dy = targetY - centerY;
    float len = std::sqrt(dx*dx + dy*dy);

    if (len > 0.01f) {
        float move = speed * deltaTime;
        if (move > len) move = len; // Ne pas dépasser la cible

        // Tentative de déplacement
        float newX = x + (dx / len) * move;
        float newY = y + (dy / len) * move;

        // Vérifie la collision pour tous les coins de l'ennemi
        bool collision = false;
        float corners[4][2] = {
            { newX, newY },
            { newX + size, newY },
            { newX, newY + size },
            { newX + size, newY + size }
        };
        for (int i = 0; i < 4; ++i) {
            int cx = static_cast<int>(corners[i][0]);
            int cy = static_cast<int>(corners[i][1]);
            if (cx < 0 || cx >= map.getWidth() || cy < 0 || cy >= map.getHeight()) {
                collision = true;
                break;
            }
            TileType ct = map.getTile(cx, cy).getType();
            if (ct == TileType::Solid || ct == TileType::Obstacle) {
                collision = true;
                break;
            }
        }
        if (!collision) {
            x = newX;
            y = newY;
            stuckFrames = 0;
        } else {
            stuckFrames++;
        }
    } else {
        // Snap sur la grille si très proche
        x = nextX - size / 2.0f + 0.5f;
        y = nextY - size / 2.0f + 0.5f;
        stuckFrames = 0;
    }

    // Déblocage aléatoire si bloqué trop longtemps
    if (stuckFrames > 60) {
        std::vector<std::pair<int, int>> directions = {
            {1,0}, {-1,0}, {0,1}, {0,-1}
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(directions.begin(), directions.end(), gen);
        for (auto [dx, dy] : directions) {
            int nx = tileX + dx;
            int ny = tileY + dy;
            if (nx >= 0 && nx < map.getWidth() && ny >= 0 && ny < map.getHeight()) {
                TileType t = map.getTile(nx, ny).getType();
                if (t == TileType::Empty) {
                    x = nx;
                    y = ny;
                    stuckFrames = 0;
                    break;
                }
            }
        }
    }
}

std::pair<float, float> getRandomFarPosition(const TileMap& map, float minDistance, float playerX, float playerY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int margin = 2; // pour éviter les bords
    std::uniform_int_distribution<> distX(margin, map.getWidth() - margin - 1);
    std::uniform_int_distribution<> distY(margin, map.getHeight() - margin - 1);

    for (int tries = 0; tries < 1000; ++tries) {
        int x = distX(gen);
        int y = distY(gen);
        float dx = x - playerX;
        float dy = y - playerY;
        float dist = std::sqrt(dx*dx + dy*dy);
        if (dist >= minDistance && map.getTile(x, y).getType() == TileType::Empty) {
            return {static_cast<float>(x), static_cast<float>(y)};
        }
    }
    // Si pas trouvé, retourne une position par défaut (pas sur le bord)
    return {static_cast<float>(margin), static_cast<float>(margin)};
}