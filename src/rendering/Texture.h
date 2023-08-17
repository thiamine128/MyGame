#pragma once

#include <glad/glad.h>

class Texture
{
public:
    Texture();
    Texture(char const*);
    ~Texture();

    void loadImage(const char*);
    void bind() const;
    int getWidth() const;
protected:
    int width, height, nrChannels;
    GLuint id;
};