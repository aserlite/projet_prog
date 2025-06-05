#include <glad/glad.h>
#include "start_screen.hpp"
#include <iostream>
#include "texture_manager.hpp"
#include "draw_scene.hpp"

static bool startScreenActive = true;
static Texture startScreenTexture;

void initStartScreen() {
    startScreenActive = true;
    startScreenTexture.loadFromFile("assets/images/startScreen.jpg");
}

void drawStartScreen() {
    startScreenTexture.attachTexture();
    drawSquare(0.0f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f);
    startScreenTexture.detachTexture();
}

bool isStartScreenActive() {
    return startScreenActive;
}

void setStartScreenActive(bool active) {
    startScreenActive = active;
}