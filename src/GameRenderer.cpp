#include "GameRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::render() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}