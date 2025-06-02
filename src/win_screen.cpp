#include "win_screen.hpp"
#include <iostream>
#include <glad/glad.h>
#include "text.hpp"

static bool WinScreenActive = false;

void initWinScreen() {
    WinScreenActive = true;
}

void drawWinScreen(int score, float timeSeconds) {
    glClearColor(0.05f, 0.25f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    myEngine.mvMatrixStack.loadIdentity();
    myEngine.updateMvMatrix();

    // drawText(200, 350, "GAME OVER", 2.0f); 
}

bool isWinScreenActive() {
    return WinScreenActive;
}

void setWinScreenActive(bool active) {
    WinScreenActive = active;
}