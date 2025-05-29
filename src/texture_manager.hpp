#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& path, bool flip = true);
    void attachTexture() const;
    void detachTexture() const;
    GLuint getID() const { return texID; }

private:
    GLuint texID = 0;
};