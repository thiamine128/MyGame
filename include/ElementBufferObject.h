#pragma once

#include <glad/glad.h>

class ElementBufferObject
{
public:
    ElementBufferObject();
    ~ElementBufferObject();

    void bind() const;
    void unbind() const;
    void bufferDataStatic(GLsizeiptr, const void*) const;
protected:
    GLuint id;
};