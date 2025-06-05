#include "draw_scene.hpp"
#include <iostream>
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <vector>
#include "texture_manager.hpp"

StandardMesh carre;

extern TileMap* globalMap;

extern Player player;
extern std::vector<Enemy> enemies;

Texture playerTexture;
Texture enemyTexture;
Texture wallTexture;
Texture obstacleTexture;
Texture objectTexture;
Texture trapTexture;
Texture floorTexture;


void initScene()
{
    static float positions[] = {
        -0.5f, -0.5f, // Bas gauche
        0.5f, -0.5f,  // Bas droit
        0.5f, 0.5f,   // Haut droit
        -0.5f, 0.5f}; // Haut gauche

    static float uvs[] = {
        0.0f, 0.0f,  // Bas gauche
        1.0f, 0.0f,  // Bas droit
        1.0f, 1.0f,  // Haut droit
        0.0f, 1.0f}; // Haut gauche

    carre = StandardMesh(4, GL_TRIANGLE_FAN);
    carre.setNbElt(4);
    carre.addOneBuffer(0, 2, positions, "position", true);
    carre.addOneBuffer(2, 2, uvs, "uvs", true);
    carre.createVAO();

    myEngine.activateTexturing(true);

    enemyTexture.loadFromFile("assets/textures/police_front.png");
    wallTexture.loadFromFile("assets/textures/bush.png");
    obstacleTexture.loadFromFile("assets/textures/mur.png");
    objectTexture.loadFromFile("assets/textures/weed.png");
    trapTexture.loadFromFile("assets/textures/pompe.png");
    floorTexture.loadFromFile("assets/textures/sol.png");
}

void drawSquare(float x, float y, float size, float r, float g, float b)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation({x, y, 0.0f});
    myEngine.mvMatrixStack.addHomothety({size, size, 1.0f});
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(r, g, b);
    carre.draw();
    myEngine.mvMatrixStack.popMatrix();
}

void drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fond noir
    glClear(GL_COLOR_BUFFER_BIT);
    myEngine.mvMatrixStack.loadIdentity();
    myEngine.updateMvMatrix();

    if (globalMap != nullptr)
    {
        int rows = globalMap->getHeight();
        int cols = globalMap->getWidth();

        // Ajustement de la taille des cellules pour que la carte tienne dans la fenêtre
        float cellW = 2.0f / cols;
        float cellH = 2.0f / rows;

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                TileType type = globalMap->getTile(x, y).getType();

                // Calcul des coordonnées de la cellule
                float x1 = -1.0f + x * cellW; // X 
                float y1 = -1.0f + y * cellH; // Y

                // Dessin de la cellule
                if (type == TileType::Solid)
                {
                    wallTexture.attachTexture();
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.5f, 0.3f, 0.1f); // Marron (mur)
                    wallTexture.detachTexture();
                }
                else if (type == TileType::Empty)
                {
                    floorTexture.attachTexture();
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.8f, 0.8f, 0.8f); // Gris clair (vide)
                    floorTexture.detachTexture();
                }
                else if (type == TileType::Object)
                {
                    objectTexture.attachTexture();
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.0f, 1.0f, 0.0f); // Vert (objet)
                    objectTexture.detachTexture();
                }
                else if (type == TileType::Trap)
                {
                    trapTexture.attachTexture();
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 1.0f, 0.0f, 0.0f); // Rouge (piège)
                    trapTexture.detachTexture();
                }
                else
                {
                    obstacleTexture.attachTexture();
                    drawSquare(x1 + cellW / 2, y1 + cellH / 2, cellW, 0.2f, 0.2f, 0.2f); // Couleur par défaut
                    obstacleTexture.detachTexture();
                }
            }
        }
    }

    // Dessiner le joueur
    playerTexture.loadFromFile(player.getCurrentSprite());
    playerTexture.attachTexture();    float playerSize = 2.0f / globalMap->getWidth() * 2.0f; // Taille = 2 cases
    float playerCellSize = 2.0f / globalMap->getWidth();
    drawSquare(
        player.getX() * playerCellSize - 1.0f + playerCellSize,
        player.getY() * playerCellSize - 1.0f + playerCellSize,
        playerSize, 0.0f, 0.0f, 1.0f
    );
    playerTexture.detachTexture();

    // Dessiner les ennemis
    float enemySize = 2.0f / globalMap->getWidth() * 2.0f; // Taille = 2 cases
    float enemyCellSize = 2.0f / globalMap->getWidth();
    for (const auto &enemy : enemies)
    {
        enemyTexture.attachTexture();
        drawSquare(
            enemy.getX() * enemyCellSize - 1.0f + enemyCellSize,
            enemy.getY() * enemyCellSize - 1.0f + enemyCellSize,
            enemySize, 1.0f, 0.0f, 1.0f
        );
        enemyTexture.detachTexture();
    }
    glFlush();
}