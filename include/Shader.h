#pragma once

#include <glad/glad.h>

class Shader
{
public:
    Shader(const char*, const char*);
    ~Shader();

    void use() const;
    void setInt(const char*, int) const;
protected:
    GLuint id;
};