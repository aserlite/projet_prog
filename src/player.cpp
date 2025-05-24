#include "player.hpp"
#include <iostream>

Player::Player(float x, float y, float speed, const std::string &spritePath)
    : x(x), y(y), speed(speed), spritePath(spritePath) {}

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
                std::cout << "Bloc en contact à (" << tileX << ", " << tileY << ") : " << static_cast<int>(tileType) << std::endl;

                if (tileType == TileType::Solid)
                {
                    map.getTile(tileX, tileY) = Tile(TileType::Empty);
                    std::cout << "Bloc miné à (" << tileX << ", " << tileY << ")" << std::endl;
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

int Player::getScore() const
{
    return score;
}