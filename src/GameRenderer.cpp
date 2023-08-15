#include "GameRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Texture.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

Shader* shader;
VertexBufferObject* vbo;
VertexArrayObject* vao;
ElementBufferObject* ebo;
Texture* texture;

float vertices[] =
{
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] =
{
    0, 1, 3,
    1, 2, 3
};
GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }

    shader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");
    vbo = new VertexBufferObject();
    ebo = new ElementBufferObject();
    vao = new VertexArrayObject();
    vao->bind();

    vbo->bind();
    vbo->bufferDataStatic(sizeof(vertices), vertices);

    ebo->bind();
    ebo->bufferDataStatic(sizeof(indices), indices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vbo->unbind();
    vao->unbind();

    texture = new Texture("assets/test.png");
}

GameRenderer::~GameRenderer()
{
    delete vbo;
    delete ebo;
    delete vao;
    delete texture;
}

void GameRenderer::render() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    vao->bind();
    texture->bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}