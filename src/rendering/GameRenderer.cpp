#include "GameRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Camera.h"
#include "Model.h"
#include "world/World.h"
#include "FramebufferObject.h"
#include "ModelManager.h"
#include "Game.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "ShaderManager.h"
#include "TextureManager.h"


GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    this->camera = new Camera();
    
    ShaderManager::load();
    
    this->projection = glm::mat4(1.0);
    this->lightProjection = glm::ortho(-12.0f, 12.0f, -12.0f, 12.0f, -12.0f, 20.0f);

    this->updateProjection();

    this->defaultShader = ShaderManager::getDefault();

    this->groundModel = ModelManager::getModel("assets/model/ground.obj");

    this->initShadowMap();

    TextureManager::initAtlas();
}

GameRenderer::~GameRenderer()
{
    
}

void GameRenderer::render()
{
    Player* player = Game::getInstance()->getWorld()->getPlayer();

    this->camera->update(player);

    ShaderManager::setupUniforms(this);

    glViewport(0, 0, this->shadowWidth, this->shadowHeight);
    this->renderToDepthMap();
    
    glViewport(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight());
    this->renderDefault();
}

Camera* GameRenderer::getCamera() const
{
    return this->camera;
}

void GameRenderer::renderToDepthMap()
{
    this->depthMapFramebuffer->bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    this->renderWorld(Game::getInstance()->getWorld(), ShaderManager::getShadow());
    this->depthMapFramebuffer->unbind();
}

void GameRenderer::renderDefault()
{
    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1);
    this->depthMap->bind();
    this->renderWorld(Game::getInstance()->getWorld(), this->defaultShader);
}

void GameRenderer::renderWorld(World* world, const Shader* shader) const
{
    Game::getInstance()->getWorld()->getPlayer()->render(shader);

    auto constructions = world->getConstructions();
    for (Construction* construction : constructions) {
        
    }

    this->renderChunks(world, shader);
}

void GameRenderer::renderChunks(World* world, const Shader* shader) const
{
    TextureManager::tiles->getTexture()->bind();
    shader->use();
    shader->setInt("texture0", 0);
    
    glm::vec3 origin = this->camera->getCenter();
    glm::ivec2 p = world->getChunkPos(origin.x, origin.z);
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (world->hasChunk(p.x + i, p.y + j)) {
                glm::mat4 model = glm::mat4(1.0);
                model = glm::translate(model, glm::vec3((p.x + i) * 16.0, 0.0, (p.y + j) * 16.0));
                shader->setMat4("model", model);
                Chunk& chunk = world->getChunk(p.x + i, p.y + j);
                chunk.getMesh()->render();
            }
        }
    }

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (world->hasChunk(p.x + i, p.y + j)) {
                glm::mat4 model = glm::mat4(1.0);
                model = glm::translate(model, glm::vec3((p.x + i) * 16.0, 0.0, (p.y + j) * 16.0));
                shader->setMat4("model", model);
                Chunk& chunk = world->getChunk(p.x + i, p.y + j);
                for (int x = 0; x < 16; ++x)
                {
                    for (int y = 0; y < 16; ++y)
                    {
                        if (chunk.getCrop(x, y) != nullptr)
                        {
                            glm::mat4 model = glm::mat4(1.0);
                            model = glm::translate(model, glm::vec3((p.x + i) * 16.0 + x + 0.5, 0.0, (p.y + j) * 16.0 + y + 0.5));
                            shader->setMat4("model", model);
                            chunk.getCrop(x, y)->getMesh()->render(shader);
                        }
                    }
                }
            }
        }
    }
}

void GameRenderer::updateProjection()
{
    this->projection = glm::perspective(glm::radians(45.0f), (float) Window::getInstance()->getWidth() / (float) Window::getInstance()->getHeight(), 0.1f, 100.0f);
    
    ShaderManager::initUniforms(this);
}

void GameRenderer::initShadowMap()
{
    this->shadowWidth = this->shadowHeight = 1024;
    this->depthMapFramebuffer = new FramebufferObject();
    this->depthMap = new Texture();
    this->depthMap->bind();
    this->depthMap->setupDepthMap(this->shadowWidth, this->shadowHeight);
    this->depthMapFramebuffer->bind();
    this->depthMap->attachToFramebuffer(GL_DEPTH_ATTACHMENT);
    this->depthMapFramebuffer->setDrawBuffer(GL_NONE);
    this->depthMapFramebuffer->setReadBuffer(GL_NONE);
    this->depthMapFramebuffer->unbind();
}

glm::vec3 GameRenderer::getSunPosition() const
{
    return this->camera->getCenter() + glm::vec3(-2.0, 2.0, -2.0);
}

glm::mat4 GameRenderer::getView() const
{
    return this->camera->getView();
}

glm::mat4 GameRenderer::getLightSpace() const
{
    return this->lightProjection * glm::lookAt(this->getSunPosition(), this->camera->getCenter(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 GameRenderer::getProjection() const
{
    return this->projection;
}
