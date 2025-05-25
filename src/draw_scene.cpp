#include "draw_scene.hpp"
#include <iostream>
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "player.hpp" // Inclure la classe Player
#include "enemy.hpp"
#include <vector>

GLBI_Convex_2D_Shape carre;

TileMap *globalMap = nullptr;

extern Player player; // Déclarer le joueur comme global (ou passez-le en paramètre)
extern std::vector<Enemy> enemies;

void initScene()
{
    std::vector<float> carrePoints = {
        -1.0f , -1.0f, // Coin inférieur gauche
        1.0f , -1.0f ,  // Coin inférieur droit
        1.0f , 1.0f ,   // Coin supérieur droit
        -1.0f , 1.0f    // Coin supérieur gauche
    };

    carre.initShape(carrePoints);
    carre.changeNature(GL_TRIANGLE_FAN);
}

void drawSquare(float x, float y, float size, float r, float g, float b)
{
    // std::cout << "Drawing square at (" << x << ", " << y << ") with size " << size << std::endl;

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation({x, y, 0.0f});
    myEngine.mvMatrixStack.addHomothety({size, size, 1.0f});
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(r, g, b);
    carre.drawShape(); 
    myEngine.mvMatrixStack.popMatrix();
}

void drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fond noir
    glClear(GL_COLOR_BUFFER_BIT);
    myEngine.mvMatrixStack.loadIdentity();
    myEngine.updateMvMatrix();

    if (globalMap != nullptr) {
        int rows = globalMap->getHeight();
        int cols = globalMap->getWidth();

        // Ajustement de la taille des cellules pour que la carte tienne dans la fenêtre
        float cellW = 2.0f / cols; // Largeur d'une cellule (normalisée pour OpenGL)
        float cellH = 2.0f / rows; // Hauteur d'une cellule (normalisée pour OpenGL)

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                TileType type = globalMap->getTile(x, y).getType();

                // Calcul des coordonnées de la cellule
                float x1 = -1.0f + x * cellW; // Coordonnée X de la cellule
                float y1 = -1.0f + y * cellH; // Coordonnée Y de la cellule

                // Dessin de la cellule en fonction de son type
                if (type == TileType::Solid) {
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.5f, 0.3f, 0.1f); // Marron (mur)
                } else if (type == TileType::Empty) {
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.8f, 0.8f, 0.8f); // Gris clair (vide)
                } else if (type == TileType::Object) {
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.0f, 1.0f, 0.0f); // Vert (objet)
                } else if (type == TileType::Trap) {
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 1.0f, 0.0f, 0.0f); // Rouge (piège)
                } else {
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.2f, 0.2f, 0.2f); // Couleur par défaut
                }
            }
        }
    }

    // Dessiner le joueur
    float playerSize = 2.0f / globalMap->getWidth(); // Taille du joueur (identique à celle des cases)
    drawSquare(player.getX() * playerSize - 1.0f + playerSize / 2,
               player.getY() * playerSize - 1.0f + playerSize / 2,
               playerSize, 0.0f, 0.0f, 1.0f); // Bleu pour le joueur

    // Dessiner les ennemis
    float enemySize = 2.0f / globalMap->getWidth();
    for (const auto& enemy : enemies) {
        drawSquare(enemy.getX() * enemySize - 1.0f + enemySize / 2,
                   enemy.getY() * enemySize - 1.0f + enemySize / 2,
                   enemySize, 1.0f, 0.0f, 1.0f); // Magenta pour les ennemis
    }

    glFlush();
}