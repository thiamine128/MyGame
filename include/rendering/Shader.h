#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char*, const char*);
    ~Shader();

    void use() const;
    void setInt(const char*, int) const;
    void setMat4(const char*, glm::mat4&) const;
protected:
    GLuint id;
};