#pragma once

#include "enemy.hpp"
#include "tile_map.hpp"
#include <string>

enum class Direction { Up, Down, Left, Right };

class Player
{
public:
    Player(float x, float y, float speed);

    // Méthodes pour gérer le joueur
    void move(float dx, float dy, TileMap &map); // Déplacement du joueur
    void mine(TileMap &map);                     // Miner un bloc
    void collect(TileMap &map);                  // Collecter un objet
    void checkTrap(TileMap& map);
    void checkEnemyCollision(const std::vector<Enemy>& enemies);

    // Accesseurs
    float getX() const;
    float getY() const;
    const std::string &getSpritePath() const;
    int getScore() const; // Récupérer le score

    bool allObjectsCollected(TileMap& map) const;
    bool isInTrap(TileMap& map) const;
    bool isInEnemy(const std::vector<Enemy>& enemies) const;

    void setDirection(Direction dir) { direction = dir; }
    Direction getDirection() const { return direction; }
    const std::string& getCurrentSprite() const;

private:
    float x;                // Position X du joueur
    float y;                // Position Y du joueur
    float speed;            // Vitesse de déplacement
    float size = 1.9f;      // Taille du joueur
    std::string spritePath; // Chemin vers le sprite du joueur
    int score = 0;          // Compteur de points
    Direction direction = Direction::Down;
    std::string spriteUp, spriteDown, spriteLeft, spriteRight;
};

std::pair<float, float> findSafeSpawn(TileMap& map, int radius = 2);
