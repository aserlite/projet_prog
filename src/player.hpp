#pragma once

#include "enemy.hpp"
#include "tile_map.hpp"
#include <string>

enum class Direction { Up, Down, Left, Right };

class Player
{
public:
    Player(float x, float y, float speed);

    void move(float dx, float dy, TileMap &map);
    void mine(TileMap &map);
    void collect(TileMap &map);
    void checkTrap(TileMap& map);
    void checkEnemyCollision(const std::vector<Enemy>& enemies);

    float getX() const;
    float getY() const;
    const std::string &getSpritePath() const;
    int getScore() const; 

    bool allObjectsCollected(TileMap& map) const;
    bool isInTrap(TileMap& map) const;
    bool isInEnemy(const std::vector<Enemy>& enemies) const;

    void setDirection(Direction dir) { direction = dir; }
    Direction getDirection() const { return direction; }
    const std::string& getCurrentSprite() const;

private:
    float x;
    float y;
    float speed;
    float size = 1.9f;
    std::string spritePath;
    int score = 0;
    Direction direction = Direction::Down;
    std::string spriteUp, spriteDown, spriteLeft, spriteRight;
};

std::pair<float, float> findSafeSpawn(TileMap& map, int radius = 2);
