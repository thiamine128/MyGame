#include "glhelper.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <stb_image.h>

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

void ElementBufferObject::bufferDataDynamic(GLsizeiptr size, const void* data) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}


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


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexSrc, fragmentSrc;
    std::ifstream vertexFile, fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vertexStream, fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexSrc = vertexStream.str();
        fragmentSrc = fragmentStream.str();    
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Cannot read shader file." << std::endl;
    }

    GLuint vertexId, fragmentId;
    GLint success;
    char log[512];

    const char* vertexCode = vertexSrc.c_str();
    
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexCode, NULL);
    glCompileShader(vertexId);
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexId, sizeof(log), NULL, log);
        std::cout << "Failed to compile vertex shader." << std::endl;
        std::cout << log << std::endl;
    }

    const char* fragmentCode = fragmentSrc.c_str();
    
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentCode, NULL);
    glCompileShader(fragmentId);
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentId, sizeof(log), NULL, log);
        std::cout << "Failed to compile fragment shader." << std::endl;
        std::cout << log << std::endl;
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertexId);
    glAttachShader(this->id, fragmentId);
    glLinkProgram(id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->id, sizeof(log), NULL, log);
        std::cout << "Failed to link program." << std::endl;
        std::cout << log << std::endl;
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void Shader::use() const
{
    glUseProgram(this->id);
}

void Shader::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setMat4(const char* name, glm::mat4 const& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec2(const char* name, glm::vec2 const& value) const
{
    glUniform2fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setVec3(const char* name, glm::vec3 const& value) const
{
    glUniform3fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}

void Shader::setVec4(const char* name, glm::vec4 const& value) const
{
    glUniform4fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}

Texture::Texture()
{
    glGenTextures(1, &(this->id));
}

Texture::Texture(const char *path)
{
    glGenTextures(1, &(this->id));
    this->loadImage(path);
}

Texture::~Texture()
{
    glDeleteTextures(1, &(this->id));
}

void Texture::loadImage(const char* path)
{
    unsigned char* data = stbi_load(path, &(this->width), &(this->height), &(this->nrChannels), STBI_rgb_alpha);

    if (data) {
        
        this->bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load image : " << path << "." << std::endl;
    }

    stbi_image_free(data);
}

void Texture::glyph(int w, int h, void* data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

int Texture::getWidth() const
{
    return this->width;
}

int Texture::getHeight() const
{
    return this->height;
}

void Texture::attachToFramebuffer(GLenum attachment) const
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
}

void Texture::setupDepthMap(int width, int height) const
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

GLuint Texture::getId() const
{
    return this->id;
}


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

void VertexBufferObject::bufferDataDynamic(GLsizeiptr size, const void* data) const
{
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}