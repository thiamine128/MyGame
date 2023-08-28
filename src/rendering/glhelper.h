#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class ElementBufferObject
{
public:
    ElementBufferObject();
    ~ElementBufferObject();

    void bind() const;
    void unbind() const;
    void bufferDataStatic(GLsizeiptr, const void*) const;
    void bufferDataDynamic(GLsizeiptr, const void*) const;
protected:
    GLuint id;
};

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

class Shader
{
public:
    Shader(const char*, const char*);
    ~Shader();

    void use() const;
    void setInt(const char*, int) const;
    void setVec3(const char*, glm::vec3 const&) const;
    void setVec4(const char*, glm::vec4 const&) const;
    void setMat4(const char*, glm::mat4 const&) const;
    void setVec2(const char*, glm::vec2 const&) const;
    void setFloat(const char*, float) const;
protected:
    GLuint id;
};

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