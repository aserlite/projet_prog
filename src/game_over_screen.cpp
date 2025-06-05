#include "game_over_screen.hpp"
#include <iostream>
#include "texture_manager.hpp"
#include "draw_scene.hpp"

static bool gameOverScreenActive = false;
static Texture gameOverScreenTexture;

void initGameOverScreen() {
    gameOverScreenActive = true;
    gameOverScreenTexture.loadFromFile("assets/images/gameOverScreen.jpg");
}

void drawGameOverScreen(int score, float timeSeconds) {
    gameOverScreenTexture.attachTexture();
    drawSquare(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f);
    gameOverScreenTexture.detachTexture();
}

bool isGameOverScreenActive() {
    return gameOverScreenActive;
}

void setGameOverScreenActive(bool active) {
    gameOverScreenActive = active;
}