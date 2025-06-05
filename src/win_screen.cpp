#include "win_screen.hpp"
#include <iostream>
#include "texture_manager.hpp"
#include "draw_scene.hpp"

static bool winScreenActive = false;
static Texture winScreenTexture;

void initWinScreen() {
    winScreenActive = false;
    winScreenTexture.loadFromFile("assets/images/winScreen.jpg");
}

void drawWinScreen(int score, float timeSeconds) {
    winScreenTexture.attachTexture();
    drawSquare(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f);
    winScreenTexture.detachTexture();
}

bool isWinScreenActive() {
    return winScreenActive;
}

void setWinScreenActive(bool active) {
    winScreenActive = active;
}