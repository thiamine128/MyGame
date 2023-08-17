#include "ElementBufferObject.h"

#include <glad/glad.h>

ElementBufferObject::ElementBufferObject()
{
    glGenBuffers(1, &(this->id));
}

ElementBufferObject::~ElementBufferObject()
{
    glDeleteBuffers(1, &(this->id));
}

void ElementBufferObject::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void ElementBufferObject::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::bufferDataStatic(GLsizeiptr size, const void* data) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
