#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "tile_map.hpp"
#include "draw_scene.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "flow_field.hpp"
#include "game_loop.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "text.hpp"

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

// Déclaration des variables globales
Player player(0, 0, 0.1f);
std::vector<Enemy> enemies;
std::vector<std::vector<std::pair<int, int>>> flowField;
TileMap* globalMap = nullptr;

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwSetErrorCallback(onError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tile Map", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    myEngine.initGL();
    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    runGameLoop(window);

    glfwTerminate();
    return 0;
}


// TODO: 
// - afficher score
// - afficher le temps
// - ajouter un menu au debut 
// - ajouter un écran de fin