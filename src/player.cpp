#include "player.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include "texture_manager.hpp"

Player::Player(float x, float y, float speed)
    : x(x), y(y), speed(speed) {}

float Player::getX() const
{
    return x;
}

float Player::getY() const
{
    return y;
}

const std::string &Player::getSpritePath() const
{
    return spritePath;
}

void Player::move(float dx, float dy, TileMap &map)
{
    float newX = x + dx * speed;
    float newY = y + dy * speed;

    int startX = static_cast<int>(newX);
    int endX = static_cast<int>(newX + size);
    int startY = static_cast<int>(newY);
    int endY = static_cast<int>(newY + size);

    for (int tileX = startX; tileX <= endX; ++tileX)
    {
        for (int tileY = startY; tileY <= endY; ++tileY)
        {
            if (tileX < 0 || tileX >= map.getWidth() || tileY < 0 || tileY >= map.getHeight())
            {
                return; // Sortie de la carte
            }

            TileType tileType = map.getTile(tileX, tileY).getType();
            if (tileType == TileType::Solid || tileType == TileType::Obstacle)
            {
                return; // Collision détectée
            }
        }
    }

    // Si pas de collision, mise à jour de la position
    x = newX;
    y = newY;

    // Vérification de collecte
    collect(map);
    checkTrap(map);
}

void Player::mine(TileMap &map)
{
    int startX, endX, startY, endY;

    switch (direction)
    {
    case Direction::Up:
        startX = static_cast<int>(x + .5f);
        endX = static_cast<int>(x + size + .5f);
        startY = static_cast<int>(y + size + .5f);
        endY = startY + .5f;
        break;

    case Direction::Down:
        startX = static_cast<int>(x);
        endX = static_cast<int>(x + size);
        endY = static_cast<int>(y) - 1;
        startY = endY;
        break;

    case Direction::Left:
        startY = static_cast<int>(y);
        endY = static_cast<int>(y + size);
        endX = static_cast<int>(x) - 1;
        startX = endX;
        break;

    case Direction::Right:
        startY = static_cast<int>(y);
        endY = static_cast<int>(y + size);
        startX = static_cast<int>(x + size + .5f);
        endX = startX + .5f;
        break;
    }

    // Boucle sur la ligne/colonne de contact
    for (int tileX = startX; tileX <= endX; ++tileX)
    {
        for (int tileY = startY; tileY <= endY; ++tileY)
        {
            if (tileX >= 0 && tileX < map.getWidth() && tileY >= 0 && tileY < map.getHeight())
            {
                TileType tileType = map.getTile(tileX, tileY).getType();
                if (tileType == TileType::Solid)
                {
                    map.getTile(tileX, tileY) = Tile(TileType::Empty);
                }
            }
        }
    }
}

void Player::collect(TileMap &map)
{
    int startX = static_cast<int>(x);
    int endX = static_cast<int>(x + size);
    int startY = static_cast<int>(y);
    int endY = static_cast<int>(y + size);

    for (int tileX = startX; tileX <= endX; ++tileX)
    {
        for (int tileY = startY; tileY <= endY; ++tileY)
        {
            if (tileX >= 0 && tileX < map.getWidth() && tileY >= 0 && tileY < map.getHeight())
            {
                TileType tileType = map.getTile(tileX, tileY).getType();
                if (tileType == TileType::Object)
                {
                    map.getTile(tileX, tileY) = Tile(TileType::Empty);
                    score++;
                    std::cout << "Objet collecté à (" << tileX << ", " << tileY << "). Score : " << score << std::endl;
                }
            }
        }
    }
}

void Player::checkTrap(TileMap& map)
{
    int startX = static_cast<int>(x);
    int endX = static_cast<int>(x + size);
    int startY = static_cast<int>(y);
    int endY = static_cast<int>(y + size);

    for (int tileX = startX; tileX <= endX; ++tileX)
    {
        for (int tileY = startY; tileY <= endY; ++tileY)
        {
            if (tileX >= 0 && tileX < map.getWidth() && tileY >= 0 && tileY < map.getHeight())
            {
                TileType tileType = map.getTile(tileX, tileY).getType();
            }
        }
    }
}

void Player::checkEnemyCollision(const std::vector<Enemy>& enemies)
{
    // Rectangle du joueur
    float playerLeft   = x;
    float playerRight  = x + size;
    float playerTop    = y + size;
    float playerBottom = y;

    for (const auto& enemy : enemies) {
        float enemySize = size; // ou adapte si les ennemis sont plus petits
        float ex = enemy.getX();
        float ey = enemy.getY();

        float enemyLeft   = ex;
        float enemyRight  = ex + enemySize;
        float enemyTop    = ey + enemySize;
        float enemyBottom = ey;

        // Collision AABB
        bool collision = playerLeft < enemyRight && playerRight > enemyLeft &&
                         playerBottom < enemyTop && playerTop > enemyBottom;
    }
}

int Player::getScore() const
{
    return score;
}

bool Player::allObjectsCollected(TileMap& map) const {
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (map.getTile(x, y).getType() == TileType::Object) {
                return false;
            }
        }
    }
    return true;
}

bool Player::isInTrap(TileMap& map) const {
    int startX = static_cast<int>(x);
    int endX = static_cast<int>(x + size);
    int startY = static_cast<int>(y);
    int endY = static_cast<int>(y + size);

    for (int tileX = startX; tileX <= endX; ++tileX) {
        for (int tileY = startY; tileY <= endY; ++tileY) {
            if (tileX >= 0 && tileX < map.getWidth() && tileY >= 0 && tileY < map.getHeight()) {
                TileType tileType = map.getTile(tileX, tileY).getType();
                if (tileType == TileType::Trap) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Player::isInEnemy(const std::vector<Enemy>& enemies) const {
    float playerLeft   = x;
    float playerRight  = x + size;
    float playerTop    = y + size;
    float playerBottom = y;

    for (const auto& enemy : enemies) {
        float enemySize = 1.9f; // Taille de l'ennemi
        float ex = enemy.getX();
        float ey = enemy.getY();

        float enemyLeft   = ex;
        float enemyRight  = ex + enemySize;
        float enemyTop    = ey + enemySize;
        float enemyBottom = ey;

        // Collision AABB
        if (playerLeft < enemyRight && playerRight > enemyLeft &&
            playerBottom < enemyTop && playerTop > enemyBottom) {
            return true; // Collision avec un ennemi
        }
    }
    return false; // Pas de collision avec un ennemi
}

std::pair<float, float> findSafeSpawn(TileMap& map, int radius) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(radius, map.getWidth() - radius - 1);
    std::uniform_int_distribution<> distY(radius, map.getHeight() - radius - 1);

    for (int tries = 0; tries < 1000; ++tries) {
        int x = distX(gen);
        int y = distY(gen);

        // Vérifie que la zone autour est "safe"
        bool safe = true;
        for (int dx = -radius; dx <= radius && safe; ++dx) {
            for (int dy = -radius; dy <= radius && safe; ++dy) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= map.getWidth() || ny < 0 || ny >= map.getHeight())
                    continue;
                TileType t = map.getTile(nx, ny).getType();
                if (t == TileType::Trap || t == TileType::Object || t == TileType::Solid || t == TileType::Obstacle)
                    safe = false;
            }
        }
        if (safe) {
            // Nettoie la zone autour (transforme tout en Empty)
            for (int dx = -radius; dx <= radius; ++dx) {
                for (int dy = -radius; dy <= radius; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= map.getWidth() || ny < 0 || ny >= map.getHeight())
                        continue;
                    map.getTile(nx, ny) = Tile(TileType::Empty);
                }
            }
            return {static_cast<float>(x), static_cast<float>(y)};
        }
    }

    return {static_cast<float>(radius), static_cast<float>(radius)};
}