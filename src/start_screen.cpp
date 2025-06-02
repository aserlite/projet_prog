#include "start_screen.hpp"
#include <iostream>
#include "text.hpp"
#include <glad/glad.h>

static bool startScreenActive = true;

void initStartScreen() {
    startScreenActive = true;
}

void drawStartScreen() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    myEngine.mvMatrixStack.loadIdentity();
    myEngine.updateMvMatrix();

    // drawText(200, 350, "WELCOME TO THE GAME", 2.0f);
    // drawText(200, 300, "Press SPACE to start", 1.0f);
    // drawText(200, 250, "Press ESC to quit", 1.0f);
    // drawText(200, 200, "Use zqsd to move and e to mine", 1.0f); 
}

bool isStartScreenActive() {
    return startScreenActive;
}

void setStartScreenActive(bool active) {
    startScreenActive = active;
}