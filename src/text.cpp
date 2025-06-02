#include <glad/glad.h>
#define GLT_IMPLEMENTATION
#include "gl_text.h"
#include <iostream>
#include "text.hpp"

static bool textInitialized = false;
static GLTtext *gltText = nullptr;

void initText()
{
    if (!textInitialized)
    {
        if (!gltInit())
        {
            std::cerr << "[glText] Erreur d'initialisation !" << std::endl;
            return;
        }
        gltText = gltCreateText();
        textInitialized = true;
    }
}

void quitText()
{
    if (textInitialized)
    {
        gltDeleteText(gltText);
        gltTerminate();
        textInitialized = false;
    }
}

void drawText(float x, float y, const char *text, float scale)
{
    if (!textInitialized)
        initText();

    gltSetText(gltText, text);

    // Sauvegarde l'état OpenGL
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

    GLint oldProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &oldProgram);
    GLint oldVAO = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &oldVAO);

    gltBeginDraw();
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);
    gltDrawText2D(gltText, x, y, scale);
    gltEndDraw();

    // Restaure l'état OpenGL
    glUseProgram(oldProgram);
    glBindVertexArray(oldVAO);
    glPopClientAttrib();
    glPopAttrib();

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "[DEBUG] OpenGL error after drawText: " << err << std::endl;
    }
}
