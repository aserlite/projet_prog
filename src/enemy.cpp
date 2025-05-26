#include "enemy.hpp"
#include <random>
#include <cmath>

Enemy::Enemy(float x, float y, float speed, const std::string& spritePath)
    : x(x), y(y), speed(speed), spritePath(spritePath) {}

float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }
const std::string& Enemy::getSpritePath() const { return spritePath; }

void Enemy::update(float deltaTime, const TileMap& map, const std::vector<std::vector<std::pair<int, int>>>& flowField) {
    int tileX = static_cast<int>(x);
    int tileY = static_cast<int>(y);

    if (tileX < 0 || tileX >= map.getWidth() || tileY < 0 || tileY >= map.getHeight())
        return;

    auto dir = flowField[tileY][tileX];
    int nextX = dir.first;
    int nextY = dir.second;

    if (nextX == tileX && nextY == tileY) return; // Déjà à destination ou pas de direction

    float dx = nextX - x;
    float dy = nextY - y;
    float len = std::sqrt(dx*dx + dy*dy);
    if (len > 0.01f) {
        x += (dx / len) * speed * deltaTime;
        y += (dy / len) * speed * deltaTime;
    }
}

std::pair<float, float> getRandomFarPosition(const TileMap& map, float minDistance, float playerX, float playerY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, map.getWidth() - 1);
    std::uniform_int_distribution<> distY(0, map.getHeight() - 1);

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
    // Si pas trouvé, retourne une position par défaut
    return {1.0f, 1.0f};
}