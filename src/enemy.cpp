#include "enemy.hpp"
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