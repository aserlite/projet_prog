#include "tile_map.hpp"
#include <random>
#include <iostream>

Tile::Tile(TileType type) : type(type) {}

TileMap::TileMap(int width, int height)
    : width(width), height(height), map(height, std::vector<Tile>(width)) {}

    void TileMap::generateProceduralMap(float fillProbability, int iterations) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        // Étape 1 : Initialisation aléatoire de la carte avec un contour vide
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Si la case est sur le bord, elle est vide
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    map[y][x] = Tile(TileType::Empty); // Contour vide
                } else {
                    // Sinon, initialisation aléatoire
                    if (dis(gen) < fillProbability) {
                        map[y][x] = Tile(TileType::Solid); // Case pleine
                    } else {
                        map[y][x] = Tile(TileType::Empty); // Case vide
                    }
                }
            }
        }

        // Étape 2 : Application des règles de cellular automata
        for (int iter = 0; iter < iterations; ++iter) {
            std::vector<std::vector<Tile>> newMap = map;

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    // Les cases du contour restent vides
                    if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                        newMap[y][x] = Tile(TileType::Empty);
                        continue;
                    }

                    int filledNeighbors = countFilledNeighbors(x, y);

                    if (map[y][x].getType() == TileType::Solid) {
                        // Une case pleine reste pleine si elle a au moins 4 voisins pleins
                        if (filledNeighbors < 5) {
                            newMap[y][x] = Tile(TileType::Empty);
                        }
                    } else {
                        // Une case vide devient pleine si elle a plus de 4 voisins pleins
                        if (filledNeighbors > 4) {
                            newMap[y][x] = Tile(TileType::Solid);
                        }
                    }
                }
            }

            map = newMap; // Mise à jour de la carte
        }

        // Étape supplémentaire : Remplir les espaces vides enfermés
        fillEnclosedEmptySpaces();

        // Étape 3 : Ajout d'objets, pièges et ennemis
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Les cases du contour ne peuvent pas contenir d'objets ou de pièges
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                    continue;
                }

                if (map[y][x].getType() == TileType::Empty) {
                    if (dis(gen) < 0.03) {
                        map[y][x] = Tile(TileType::Object); // Ajouter un objet
                    } else if (dis(gen) < 0.02) {
                        map[y][x] = Tile(TileType::Trap); // Ajouter un piège
                    }
                }
            }
        }

        // Étape 4 : Affichage de la carte dans le terminal
        std::cout << "Generated Map:" << std::endl;
        for (int y = height - 1; y >= 0; --y) {
            for (int x = 0; x < width; ++x) {
                TileType type = map[y][x].getType();
                if (type == TileType::Solid) {
                    std::cout << "#"; // Case pleine
                } else if (type == TileType::Empty) {
                    std::cout << "."; // Case vide
                } else if (type == TileType::Object) {
                    std::cout << "O"; // Objet
                } else if (type == TileType::Trap) {
                    std::cout << "X"; // Piège
                }
            }
            std::cout << std::endl;
        }
    }

    int TileMap::countFilledNeighbors(int x, int y) const {
        int count = 0;
    
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = x + dx;
                int ny = y + dy;
    
                // Vérifie si le voisin est dans les limites de la carte
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    if (map[ny][nx].getType() == TileType::Solid) {
                        count++;
                    }
                }
            }
        }
    
        return count;
    }

    const Tile& TileMap::getTile(int x, int y) const {
        return map[y][x];
    }

    int TileMap::getWidth() const {
        return width;
    }

    int TileMap::getHeight() const {
        return height;
    }

    void TileMap::fillEnclosedEmptySpaces() {
        std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

        // Fonction récursive pour le flood fill
        auto floodFill = [&](int x, int y, auto&& floodFillRef) -> void {
            if (x < 0 || x >= width || y < 0 || y >= height) return; // Hors limites
            if (visited[y][x] || map[y][x].getType() != TileType::Empty) return; // Déjà visité ou non vide

            visited[y][x] = true;

            // Propagation dans les 4 directions
            floodFillRef(x + 1, y, floodFillRef);
            floodFillRef(x - 1, y, floodFillRef);
            floodFillRef(x, y + 1, floodFillRef);
            floodFillRef(x, y - 1, floodFillRef);
        };

        // Marquer toutes les cases vides connectées au bord
        for (int x = 0; x < width; ++x) {
            if (map[0][x].getType() == TileType::Empty && !visited[0][x]) {
                floodFill(x, 0, floodFill);
            }
            if (map[height - 1][x].getType() == TileType::Empty && !visited[height - 1][x]) {
                floodFill(x, height - 1, floodFill);
            }
        }
        for (int y = 0; y < height; ++y) {
            if (map[y][0].getType() == TileType::Empty && !visited[y][0]) {
                floodFill(0, y, floodFill);
            }
            if (map[y][width - 1].getType() == TileType::Empty && !visited[y][width - 1]) {
                floodFill(width - 1, y, floodFill);
            }
        }

        // Remplir les cases vides non connectées au bord
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (map[y][x].getType() == TileType::Empty && !visited[y][x]) {
                    map[y][x] = Tile(TileType::Solid); // Remplir les cases enfermées
                }
            }
        }
    }