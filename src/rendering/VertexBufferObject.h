#pragma once

#include <glad/glad.h>

class VertexBufferObject
{
public:
    VertexBufferObject();
    ~VertexBufferObject();

    void bind() const;
    void unbind() const;
    void bufferDataStatic(GLsizeiptr, const void*) const;
    void bufferDataDynamic(GLsizeiptr, const void*) const;
protected:
    GLuint id;
};