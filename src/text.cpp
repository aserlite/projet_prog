#define GLT_IMPLEMENTATION
#include "stb_easy_font.h"
#include <iostream>
#include "text.hpp"
#include <GL/gl.h> 


void drawText(float x, float y, const char *text, float scale)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

    char buffer[99999];
    int quads = stb_easy_font_print(x, y, (char *)text, nullptr, buffer, sizeof(buffer));
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopClientAttrib();
    glPopAttrib();

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "[DEBUG] OpenGL error after drawText: " << err << std::endl;
    }
}