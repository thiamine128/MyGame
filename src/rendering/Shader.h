#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char*, const char*);
    ~Shader();

    void use() const;
    void setInt(const char*, int) const;
    void setVec3(const char*, glm::vec3 const&) const;
    void setMat4(const char*, glm::mat4 const&) const;
    void setVec2(const char*, glm::vec2 const&) const;
protected:
    GLuint id;
};