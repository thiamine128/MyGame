#include "VertexBufferObject.h"

#include <glad/glad.h>

VertexBufferObject::VertexBufferObject()
{
    glGenBuffers(1, &(this->id));
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &(this->id));
}

void VertexBufferObject::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBufferObject::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::bufferDataStatic(GLsizeiptr size, const void* data) const
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
