#pragma once

#include <glad/glad.h>

class Texture
{
public:
    Texture(const char*);
    ~Texture();

    void bind() const;
protected:
    int width, height, nrChannels;
    GLuint id;
};