#define GLFW_INCLUDE_NONE
#include "tile_map.hpp"
#include "draw_scene.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "flow_field.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <chrono>

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
static const float GL_VIEW_SIZE = 2.0f;
static float aspectRatio = 1.0f;

using namespace glbasimac; 
GLBI_Engine myEngine;

void onError(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow* /*window*/, int width, int height) {
    aspectRatio = width / (float)height;
    glViewport(0, 0, width, height);

    if (aspectRatio > 1.0) {
        myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio / 2.0,
                                 GL_VIEW_SIZE * aspectRatio / 2.0,
                                 -GL_VIEW_SIZE / 2.0, GL_VIEW_SIZE / 2.0);
    } else {
        myEngine.set2DProjection(-GL_VIEW_SIZE / 2.0, GL_VIEW_SIZE / 2.0,
                                 -GL_VIEW_SIZE / (2.0 * aspectRatio),
                                 GL_VIEW_SIZE / (2.0 * aspectRatio));
    }
}
Player player(0, 0, 0.1f, "player_sprite.png"); // valeurs temporaires, écrasées juste après

std::vector<Enemy> enemies;
std::vector<std::vector<std::pair<int, int>>> flowField;

int main() {
    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwSetErrorCallback(onError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Création de la fenêtre
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tile Map", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialisation de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialisation OpenGL
    myEngine.initGL();

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialisation de la carte
    TileMap* map = new TileMap(50, 50);
    map->generateProceduralMap(0.475f, 4);
    globalMap = map; 

    auto [spawnX, spawnY] = findSafeSpawn(*map, 2); // rayon 2 cases autour du joueur
    player = Player(spawnX, spawnY, 0.1f, "player_sprite.png");

    float minDistance = 15.0f;
    for (int i = 0; i < 3; ++i) {
        auto [ex, ey] = getRandomFarPosition(*map, minDistance, player.getX(), player.getY());
        enemies.emplace_back(ex, ey, 1.5f + 0.5f * i, "enemy_sprite.png");
    }


    initScene();
    // Boucle principale
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Gestion des entrées clavier
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            player.setDirection(Direction::Up);
            player.move(0.0f, 1.0f, *globalMap); // Haut
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            player.setDirection(Direction::Down);
            player.move(0.0f, -1.0f, *globalMap); // Bas
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            player.setDirection(Direction::Left);
            player.move(-1.0f, 0.0f, *globalMap); // Gauche
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            player.setDirection(Direction::Right);
            player.move(1.0f, 0.0f, *globalMap); // Droite
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            player.mine(*globalMap);
        }

        static int lastPlayerX = -1, lastPlayerY = -1;
        static auto lastTime = std::chrono::high_resolution_clock::now();

        int playerX = static_cast<int>(player.getX());
        int playerY = static_cast<int>(player.getY());
        if (playerX != lastPlayerX || playerY != lastPlayerY || flowField.empty()) {
            flowField = computeFlowField(*globalMap, playerX, playerY);
            lastPlayerX = playerX;
            lastPlayerY = playerY;
        }

        // Calcul du deltaTime pour les ennemis
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        // Mise à jour des ennemis
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, *globalMap, flowField);
        }

        player.checkEnemyCollision(enemies);

        // Dessiner la scène
        drawScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    delete map;

    glfwTerminate();
    return 0;
}


// TODO: 
// - ajouter algo de pathfinding
// - afficher score
// - afficher le temps
// - ajouter un menu au debut 
// - ajouter un écran de fin
// - ajouter les textures
