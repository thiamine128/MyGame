#pragma once

#include <glad/glad.h>

class FramebufferObject
{
public:
    FramebufferObject();
    ~FramebufferObject();

    void bind() const;
    void unbind() const;
    void setDrawBuffer(GLenum) const;
    void setReadBuffer(GLenum) const;
protected:
    GLuint id;
};