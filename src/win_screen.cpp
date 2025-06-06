#include "win_screen.hpp"
#include <iostream>
#include "texture_manager.hpp"
#include "draw_scene.hpp"

static bool winScreenActive = false;
static Texture winScreenTexture;
static Texture quitbuttonTexture;
static Texture restartbuttonTexture;

struct ButtonZone {
    float x, y, w, h;
};

static const ButtonZone quitBtnZone = {0.9f, 0.9f, 0.15f, 0.25f};
static const ButtonZone restartBtnZone = {0.0f, -0.6f, 0.4f, 1.0f};

void initWinScreen() {
    winScreenActive = false;
    winScreenTexture.loadFromFile("assets/images/winScreen.jpg");
    quitbuttonTexture.loadFromFile("assets/images/quit.jpg");
    restartbuttonTexture.loadFromFile("assets/images/restart.jpg");
}

void drawWinScreen(int score, float timeSeconds) {
    winScreenTexture.attachTexture();
    drawSquare(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f);
    winScreenTexture.detachTexture();
    quitbuttonTexture.attachTexture();
    drawSquare(0.9f, 0.9f, 0.15f, 0.25f, 0.25f, 0.5f);
    quitbuttonTexture.detachTexture();
    restartbuttonTexture.attachTexture();
    drawSquare(0.0f, -0.6f, 0.4f, 1.0f, 1.0f, 1.0f);
    restartbuttonTexture.detachTexture();
}

bool isWinScreenActive() {
    return winScreenActive;
}

void setWinScreenActive(bool active) {
    winScreenActive = active;
}

static bool isInsideButton(float mx, float my, const ButtonZone& btn) {
    return mx >= btn.x && mx <= btn.x + btn.w && my >= btn.y && my <= btn.y + btn.h;
}

int handleWinScreenClick(float mouseX, float mouseY) {
    if (isInsideButton(mouseX, mouseY, restartBtnZone)) {
        return 1;
    }
    if (isInsideButton(mouseX, mouseY, quitBtnZone)) {
        return 2;
    }
    return 0;
}