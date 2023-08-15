#include "Shader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

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
