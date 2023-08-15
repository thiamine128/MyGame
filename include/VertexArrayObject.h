#pragma once

#include <glad/glad.h>

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind() const;
    void unbind() const;
protected:
    GLuint id;
};