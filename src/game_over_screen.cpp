#include "game_over_screen.hpp"
#include <iostream>
#include "texture_manager.hpp"
#include "draw_scene.hpp"

static bool gameOverScreenActive = false;
static Texture gameOverScreenTexture;
static Texture quitbuttonTexture;
static Texture restartbuttonTexture;

struct ButtonZone {
    float x, y, w, h;
};

static const ButtonZone quitBtnZone = {0.9f, 0.9f, 0.15f, 0.25f};
static const ButtonZone restartBtnZone = {0.0f, -0.6f, 0.4f, 1.0f};

void initGameOverScreen() {
    gameOverScreenActive = true;
    gameOverScreenTexture.loadFromFile("assets/images/gameOverScreen.jpg");
    quitbuttonTexture.loadFromFile("assets/images/quit.jpg");
    restartbuttonTexture.loadFromFile("assets/images/restart.jpg");
}

void drawGameOverScreen(int score, float timeSeconds) {
    gameOverScreenTexture.attachTexture();
    drawSquare(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f);
    gameOverScreenTexture.detachTexture();
    quitbuttonTexture.attachTexture();
    drawSquare(0.9f, 0.9f, 0.15f, 0.25f, 0.25f, 0.5f);
    quitbuttonTexture.detachTexture();
    restartbuttonTexture.attachTexture();
    drawSquare(0.0f, -0.6f, 0.4f, 1.0f, 1.0f, 1.0f);
    restartbuttonTexture.detachTexture();
}

bool isGameOverScreenActive() {
    return gameOverScreenActive;
}

void setGameOverScreenActive(bool active) {
    gameOverScreenActive = active;
}

static bool isInsideButton(float mx, float my, const ButtonZone& btn) {
    return mx >= btn.x && mx <= btn.x + btn.w && my >= btn.y && my <= btn.y + btn.h;
}

int handleGameOverScreenClick(float mouseX, float mouseY) {
    if (isInsideButton(mouseX, mouseY, restartBtnZone)) {
        return 1;
    }
    if (isInsideButton(mouseX, mouseY, quitBtnZone)) {
        return 2;
    }
    return 0;
}