#include "rendering/VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &(this->id));
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &(this->id));
}

void VertexArrayObject::bind() const
{
    glBindVertexArray(this->id);
}

void VertexArrayObject::unbind() const
{
    glBindVertexArray(0);
}
