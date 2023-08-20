#include "FramebufferObject.h"

FramebufferObject::FramebufferObject()
{
    glGenFramebuffers(1, &(this->id));
}

FramebufferObject::~FramebufferObject()
{
    glDeleteFramebuffers(1, &(this->id));
}

void FramebufferObject::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
}

void FramebufferObject::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FramebufferObject::setDrawBuffer(GLenum buffer) const
{
    glDrawBuffer(buffer);
}

void FramebufferObject::setReadBuffer(GLenum buffer) const
{
    glReadBuffer(buffer);
}
