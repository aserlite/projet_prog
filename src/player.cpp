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
    // Calculer la nouvelle position
    float newX = x + dx * speed;
    float newY = y + dy * speed;

    // Vérifier les limites de la carte
    int tileX = static_cast<int>(newX);
    int tileY = static_cast<int>(newY);

    if (tileX >= 0 && tileX < map.getWidth() && tileY >= 0 && tileY < map.getHeight()) {
        TileType tileType = map.getTile(tileX, tileY).getType();

        // Le joueur peut se déplacer sur une case vide ou un objet
        if (tileType == TileType::Empty || tileType == TileType::Object) {
            x = newX;
            y = newY;
        } else if (tileType == TileType::Solid) {
            // Si le joueur essaie de marcher sur un bloc plein, il peut miner
            mine(map);
        }
    }
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