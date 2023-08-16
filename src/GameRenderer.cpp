#include "rendering/GameRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Window.h"
#include "rendering/Shader.h"
#include "rendering/Model.h"
#include "rendering/Texture.h"

Shader* shader;
Model* mmodel;

GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    this->camera = new Camera();

    shader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");

    mmodel = new Model("assets/model/stickman.obj");
}

GameRenderer::~GameRenderer()
{
    
}

void GameRenderer::render() const
{
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();
    

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = camera->getView();
    projection = glm::perspective(glm::radians(45.0f), (float) Window::getInstance()->getWidth() / (float) Window::getInstance()->getHeight(), 0.1f, 100.0f);

    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    mmodel->render(shader);
}

Camera *GameRenderer::getCamera() const
{
    return this->camera;
}
