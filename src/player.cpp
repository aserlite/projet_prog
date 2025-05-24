#include "player.hpp"
#include <iostream>

Player::Player(float x, float y, float speed, const std::string& spritePath)
    : x(x), y(y), speed(speed), spritePath(spritePath) {}

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

const std::string& Player::getSpritePath() const {
    return spritePath;
}

void Player::move(float dx, float dy, TileMap& map) {
    float newX = x + dx * speed;
    float newY = y + dy * speed;

    // Coins du carré du joueur
    float corners[4][2] = {
        { newX, newY }, // bas-gauche
        { newX + size, newY }, // bas-droit
        { newX, newY + size }, // haut-gauche
        { newX + size, newY + size } // haut-droit
    };

    // Vérifie que tous les coins sont sur des cases traversables
    for (int i = 0; i < 4; ++i) {
        int tileX = static_cast<int>(corners[i][0]);
        int tileY = static_cast<int>(corners[i][1]);

        if (tileX < 0 || tileX >= map.getWidth() || tileY < 0 || tileY >= map.getHeight()) {
            return; // Sortie de la carte : pas de mouvement
        }

        TileType tileType = map.getTile(tileX, tileY).getType();
        if (tileType == TileType::Solid) {
            return; // Collision détectée : pas de mouvement
        }
    }

    // Si aucun coin ne bloque, déplacement autorisé
    x = newX;
    y = newY;
}


void Player::mine(TileMap& map) {
    int tileX = static_cast<int>(x);
    int tileY = static_cast<int>(y);

    TileType tileType = map.getTile(tileX, tileY).getType();

    if (tileType == TileType::Solid) {
        // Transformer le bloc plein en bloc vide
        map.getTile(tileX, tileY) = Tile(TileType::Empty);
        std::cout << "Bloc miné à (" << tileX << ", " << tileY << ")" << std::endl;
    }
}

void Player::collect(TileMap& map) {
    int tileX = static_cast<int>(x);
    int tileY = static_cast<int>(y);

    TileType tileType = map.getTile(tileX, tileY).getType();

    if (tileType == TileType::Object) {
        // Collecter l'objet
        map.getTile(tileX, tileY) = Tile(TileType::Empty);
        std::cout << "Objet collecté à (" << tileX << ", " << tileY << ")" << std::endl;
    }
}