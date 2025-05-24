#define GLFW_INCLUDE_NONE
#include "tile_map.hpp"
#include "draw_scene.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

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

int main() {
    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwSetErrorCallback(onError);

    // Création de la fenêtre
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tile Map", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialisation de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialisation OpenGL
    myEngine.initGL();

    onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialisation de la carte
    TileMap* map = new TileMap(50, 50);
    map->generateProceduralMap(0.475f, 4);
    globalMap = map; 

    initScene();
    // Boucle principale
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete map;

    glfwTerminate();
    return 0;
}