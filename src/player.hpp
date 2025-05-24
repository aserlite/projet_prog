#pragma once

#include "tile_map.hpp"
#include <string>

enum class Direction { Up, Down, Left, Right };

class Player
{
public:
    Player(float x, float y, float speed, const std::string &spritePath);

    // Méthodes pour gérer le joueur
    void move(float dx, float dy, TileMap &map); // Déplacement du joueur
    void mine(TileMap &map);                     // Miner un bloc
    void collect(TileMap &map);                  // Collecter un objet

    // Accesseurs
    float getX() const;
    float getY() const;
    const std::string &getSpritePath() const;
    int getScore() const; // Récupérer le score

    void setDirection(Direction dir) { direction = dir; }
    Direction getDirection() const { return direction; }

private:
    float x;                // Position X du joueur (en coordonnées flottantes)
    float y;                // Position Y du joueur (en coordonnées flottantes)
    float speed;            // Vitesse de déplacement
    float size = 1.9f;      // Taille du joueur (carré de 10x10 pixels)
    std::string spritePath; // Chemin vers le sprite du joueur
    int score = 0;          // Compteur de points
    Direction direction = Direction::Down;
};