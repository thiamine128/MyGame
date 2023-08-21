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
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

GameRenderer::GameRenderer()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    this->camera = new Camera();
    
    ShaderManager::load();
    
    this->projection = glm::mat4(1.0);
    this->lightProjection = glm::ortho(-24.0f, 24.0f, -24.0f, 24.0f, -24.0f, 32.0f);

    this->updateProjection();

    this->defaultShader = ShaderManager::getDefault();

    this->groundModel = ModelManager::getModel("assets/model/ground.obj");

    this->initShadowMap();

    TextureManager::initAtlas();

    this->linesVbo = new VertexBufferObject();
    this->linesVao = new VertexArrayObject();
    this->linesEbo = new ElementBufferObject();

    this->blockModels[ConstructionType::BEDS] = ModelManager::getModel("assets/model/construction/bed.obj");
}

GameRenderer::~GameRenderer()
{
    
}

void GameRenderer::render()
{
    glEnable(GL_CULL_FACE);
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
    this->renderWorld(Game::getInstance()->getWorld(), ShaderManager::getShadow(), true);
    this->depthMapFramebuffer->unbind();
}

void GameRenderer::renderDefault()
{
    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1);
    this->depthMap->bind();
    this->renderWorld(Game::getInstance()->getWorld(), this->defaultShader, false);
}

void GameRenderer::renderWorld(World* world, const Shader* shader, bool shadow)
{
    Game::getInstance()->getWorld()->getPlayer()->render(shader);

    this->renderChunks(world, shader, shadow);
}

void GameRenderer::renderChunks(World* world, const Shader* shader, bool shadow)
{
    TextureManager::tiles->getTexture()->bind();
    shader->use();
    shader->setInt("texture0", 0);
    
    glm::vec3 origin = this->camera->getCenter();
    std::vector<Chunk*> chunks;
    world->getNearbyChunks(glm::vec2(origin.x, origin.z), chunks);
    for (auto chunk : chunks)
    {
        glm::ivec2 p = chunk->getChunkPos();
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(p.x * 16.0, 0.0, p.y * 16.0));
        shader->setMat4("model", model);
        chunk->getMesh()->render();
    }

    for (auto chunk : chunks)
    {
        for (int x = 0; x < 16; ++x)
        {
            for (int y = 0; y < 16; ++y)
            {
                glm::ivec2 p = chunk->getChunkPos();
                if (chunk->getCrop(x, y) != nullptr)
                {
                    glm::mat4 model = glm::mat4(1.0);
                    model = glm::translate(model, glm::vec3(p.x * 16.0 + x + 0.5, 0.0, p.y * 16.0 + y + 0.5));
                    shader->setMat4("model", model);
                    chunk->getCrop(x, y)->getMesh()->render(shader);
                }

                for (int k = 0; k < 2; ++k)
                {
                    Construction* construction = chunk->getConstruction(x, y, k);
                    if (construction != nullptr && construction->getBuildType() != BuildType::FLOOR)
                    {
                        glm::mat4 model = glm::mat4(1.0);
                        model = glm::translate(model, glm::vec3(p.x * 16.0 + x + 0.5, 0.0, p.y * 16.0 + y + 0.5));
                        shader->setMat4("model", model);
                        this->blockModels[construction->getType()]->render(shader);
                    }
                }
            }
        }
        auto buildings = chunk->getBuildings();
        for (auto building : buildings) {
            if (!shadow && building->getAABB().insideXZ(this->camera->getCenter()))
                continue;
            building->render(shader);
        }
    }
}

void GameRenderer::updateProjection()
{
    this->projection = glm::perspective(glm::radians(45.0f), (float) Window::getInstance()->getWidth() / (float) Window::getInstance()->getHeight(), 0.1f, 100.0f);
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


void GameRenderer::renderAABB(AABB const& aabb) const
{
    this->linesVbo->bind();
    glm::vec3 vert[8] =
    {
        {aabb.getMinX(), aabb.getMinY(), aabb.getMinZ()},
        {aabb.getMaxX(), aabb.getMinY(), aabb.getMinZ()},
        {aabb.getMaxX(), aabb.getMaxY(), aabb.getMinZ()},
        {aabb.getMinX(), aabb.getMaxY(), aabb.getMinZ()},
        {aabb.getMinX(), aabb.getMinY(), aabb.getMaxZ()},
        {aabb.getMaxX(), aabb.getMinY(), aabb.getMaxZ()},
        {aabb.getMaxX(), aabb.getMaxY(), aabb.getMaxZ()},
        {aabb.getMinX(), aabb.getMaxY(), aabb.getMaxZ()},
    };
    unsigned int indices[24] =
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };
    this->linesVao->bind();
    this->linesVbo->bind();
    this->linesVbo->bufferDataDynamic(sizeof(vert), vert);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    this->linesEbo->bind();
    this->linesEbo->bufferDataDynamic(sizeof(indices), indices);
    glEnableVertexAttribArray(0);
    ShaderManager::getLine()->use();
    glLineWidth(2.0f);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
}

glm::vec3 GameRenderer::getSunPosition() const
{
    return this->camera->getCenter() + glm::vec3(-6.0, 6.0, -6.0);
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
