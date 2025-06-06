#include "game_loop.hpp"
#include "draw_scene.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "flow_field.hpp"
#include "start_screen.hpp"
#include "game_over_screen.hpp"
#include "win_screen.hpp"
#include <chrono>
#include <iostream>

extern Player player;
extern std::vector<Enemy> enemies;
extern std::vector<std::vector<std::pair<int, int>>> flowField;
extern TileMap *globalMap;
static bool pauseActive = false;

float gElapsedTime = 0.0f;

void runGameLoop(GLFWwindow *window)
{
    initScene();
    initStartScreen();
    initGameOverScreen();
    initWinScreen();

    auto startTime = std::chrono::high_resolution_clock::now();
    float elapsedTime = 0.0f;
    static int lastPlayerX = -1, lastPlayerY = -1;
    static auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- Start Screen ---
        if (isStartScreenActive())
        {
            drawStartScreen();
            glfwSwapBuffers(window);
            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                setStartScreenActive(false);
                TileMap *newMap = new TileMap(35, 35);
                newMap->generateProceduralMap(0.475f, 4);
                delete globalMap;
                globalMap = newMap;
                auto [spawnX, spawnY] = findSafeSpawn(*globalMap, 2);
                player = Player(spawnX, spawnY, 0.1f);
                enemies.clear();
                float minDistance = 15.0f;
                for (int i = 0; i < 3; ++i)
                {
                    auto [ex, ey] = getRandomFarPosition(*globalMap, minDistance, player.getX(), player.getY());
                    enemies.emplace_back(ex, ey, 1.5f + 0.5f * i, "police_front.png");
                }
                setGameOverScreenActive(false);
                startTime = std::chrono::high_resolution_clock::now();
            }
            continue;
        }

        // --- Game Over Screen ---
        if (isGameOverScreenActive())
        {
            drawGameOverScreen(player.getScore(), elapsedTime);
            glfwSwapBuffers(window);
            glfwPollEvents();

            // Gestion du clic souris sur les boutons
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);

                // Conversion des coordonnées écran vers NDC [-1,1] puis vers repère boutons
                int width, height;
                glfwGetWindowSize(window, &width, &height);
                float mx = (float)xpos / width * 2.0f - 1.0f;
                float my = 1.0f - (float)ypos / height * 2.0f; // Y inversé

                int action = handleGameOverScreenClick(mx, my);
                if (action == 1) // Restart
                {
                    TileMap *newMap = new TileMap(35, 35);
                    newMap->generateProceduralMap(0.475f, 4);
                    delete globalMap;
                    globalMap = newMap;
                    auto [spawnX, spawnY] = findSafeSpawn(*globalMap, 2);
                    player = Player(spawnX, spawnY, 0.1f);
                    enemies.clear();
                    float minDistance = 15.0f;
                    for (int i = 0; i < 3; ++i)
                    {
                        auto [ex, ey] = getRandomFarPosition(*globalMap, minDistance, player.getX(), player.getY());
                        enemies.emplace_back(ex, ey, 1.5f + 0.5f * i, "police_front.png");
                    }
                    setGameOverScreenActive(false);
                    startTime = std::chrono::high_resolution_clock::now();
                }
                if (action == 2) // Quit
                {
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                }
            }

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                TileMap *newMap = new TileMap(35, 35);
                newMap->generateProceduralMap(0.475f, 4);
                delete globalMap;
                globalMap = newMap;
                auto [spawnX, spawnY] = findSafeSpawn(*globalMap, 2);
                player = Player(spawnX, spawnY, 0.1f);
                enemies.clear();
                float minDistance = 15.0f;
                for (int i = 0; i < 3; ++i)
                {
                    auto [ex, ey] = getRandomFarPosition(*globalMap, minDistance, player.getX(), player.getY());
                    enemies.emplace_back(ex, ey, 1.5f + 0.5f * i, "police_front.png");
                }
                setGameOverScreenActive(false);
                startTime = std::chrono::high_resolution_clock::now();
            }
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }
            continue;
        }

        // --- Win Screen ---
        if (isWinScreenActive())
        {
            drawWinScreen(player.getScore(), elapsedTime);
            glfwSwapBuffers(window);
            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                TileMap *newMap = new TileMap(35, 35);
                newMap->generateProceduralMap(0.475f, 4);
                delete globalMap;
                globalMap = newMap;
                auto [spawnX, spawnY] = findSafeSpawn(*globalMap, 2);
                player = Player(spawnX, spawnY, 0.1f);
                enemies.clear();
                float minDistance = 15.0f;
                for (int i = 0; i < 3; ++i)
                {
                    auto [ex, ey] = getRandomFarPosition(*globalMap, minDistance, player.getX(), player.getY());
                    enemies.emplace_back(ex, ey, 1.5f + 0.5f * i, "police_front.png");
                }
                setWinScreenActive(false);
                startTime = std::chrono::high_resolution_clock::now();
            }
            if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }
            continue;
        }

        // Gestion des entrées clavier
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            player.setDirection(Direction::Up);
            player.move(0.0f, 1.0f, *globalMap);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            player.setDirection(Direction::Down);
            player.move(0.0f, -1.0f, *globalMap);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            player.setDirection(Direction::Left);
            player.move(-1.0f, 0.0f, *globalMap);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            player.setDirection(Direction::Right);
            player.move(1.0f, 0.0f, *globalMap);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            player.mine(*globalMap);
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        int playerX = static_cast<int>(player.getX());
        int playerY = static_cast<int>(player.getY());
        if (playerX != lastPlayerX || playerY != lastPlayerY || flowField.empty())
        {
            flowField = computeFlowField(*globalMap, playerX, playerY);
            lastPlayerX = playerX;
            lastPlayerY = playerY;
        }

        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;

        for (auto &enemy : enemies)
        {
            enemy.update(deltaTime, *globalMap, flowField);
        }

        player.checkEnemyCollision(enemies);

        if (player.isInEnemy(enemies))
        {
            std::cout << " ============== GAME OVER ==============" << std::endl;
            std::cout << "Joueur attrapé par un ennemi !" << std::endl;
            std::cout << "Score final : " << player.getScore() << std::endl;
            std::cout << "Temps écoulé : " << elapsedTime << " secondes" << std::endl;
            setGameOverScreenActive(true);
        }

        if (player.isInTrap(*globalMap))
        {
            std::cout << " ============== GAME OVER ==============" << std::endl;
            std::cout << "Joueur tombé dans un piège !" << std::endl;
            std::cout << "Score final : " << player.getScore() << std::endl;
            std::cout << "Temps écoulé : " << elapsedTime << " secondes" << std::endl;
            setGameOverScreenActive(true);
        }

        if (player.allObjectsCollected(*globalMap))
        {
            std::cout << "Tous les objets sont collectés !" << std::endl;
            std::cout << "Score final : " << player.getScore() << std::endl;
            std::cout << "Temps écoulé : " << elapsedTime << " secondes" << std::endl;
            setWinScreenActive(true);
        }

        elapsedTime = std::chrono::duration<float>(now - startTime).count();
        gElapsedTime = elapsedTime;

        drawScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}