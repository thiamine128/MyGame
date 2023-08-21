#pragma once

#include <glad/glad.h>

class Texture
{
public:
    Texture();
    Texture(char const*);
    ~Texture();

    void loadImage(const char*);
    void glyph(int, int, void*);
    void bind() const;
    int getWidth() const;
    int getHeight() const;
    void attachToFramebuffer(GLenum) const;
    void setupDepthMap(int, int) const;
    GLuint getId() const;
protected:
    
    int width, height, nrChannels;
    GLuint id;
};