#include "GameRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "ModelManager.h"
#include "Game.h"
#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderManager.h"


GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    this->camera = new Camera();

    ShaderManager::load();

    this->defaultShader = ShaderManager::getDefault();

    this->playerModel = ModelManager::getModel("assets/model/stickman.obj");
    this->groundModel = ModelManager::getModel("assets/model/ground.obj");

    this->projection = glm::mat4(1.0);
    this->updateProjectionMatrix();

    this->constructionRendererDispatcher = new ConstructionRendererDispatcher();
    this->constructionRendererDispatcher->init();
}

GameRenderer::~GameRenderer()
{
    
}

void GameRenderer::render() const
{
    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Player* player = Game::getInstance()->getWorld()->getPlayer();

    this->camera->update(player);

    this->renderGround();

    this->renderPlayer(player);

    this->renderWorld(Game::getInstance()->getWorld());
}

void GameRenderer::renderGround() const
{
    this->defaultShader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::scale(model, glm::vec3(256.0f, 1.0f, 256.0f));
    glm::mat4 view = this->camera->getView();

    
    this->defaultShader->setMat4("model", model);
    this->defaultShader->setMat4("view", view);
    this->defaultShader->setMat4("projection", this->projection);

    this->groundModel->render(this->defaultShader);
}

Camera *GameRenderer::getCamera() const
{
    return this->camera;
}

void GameRenderer::renderPlayer(Player* player) const
{
    this->defaultShader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, player->getPosFrame());
    glm::mat4 view = this->camera->getView();

    
    this->defaultShader->setMat4("model", model);
    this->defaultShader->setMat4("view", view);
    this->defaultShader->setMat4("projection", this->projection);

    this->playerModel->render(this->defaultShader);
}

void GameRenderer::renderWorld(World* world) const
{
    auto constructions = world->getConstructions();
    for (Construction* construction : constructions) {
        this->constructionRendererDispatcher->render(construction);
    }
}

void GameRenderer::updateProjectionMatrix()
{
    this->projection = glm::perspective(glm::radians(45.0f), (float) Window::getInstance()->getWidth() / (float) Window::getInstance()->getHeight(), 0.1f, 100.0f);
}

void GameRenderer::setupViewProjection(const Shader* shader) const
{
    shader->setMat4("view", this->camera->getView());
    shader->setMat4("projection", this->projection);
}
