#include "game_over_screen.hpp"
#include <iostream>
#include <glad/glad.h>
#include "text.hpp"

static bool gameOverScreenActive = false;

void initGameOverScreen() {
    gameOverScreenActive = true;
}

void drawGameOverScreen(int score, float timeSeconds) {
    glClearColor(0.15f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    myEngine.mvMatrixStack.loadIdentity();
    myEngine.updateMvMatrix();

    // drawText(200, 350, "GAME OVER", 2.0f); 
    

}

bool isGameOverScreenActive() {
    return gameOverScreenActive;
}

void setGameOverScreenActive(bool active) {
    gameOverScreenActive = active;
}