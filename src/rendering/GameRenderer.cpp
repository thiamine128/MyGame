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
#include "ChunkTessellator.h"

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

    ChunkTessellator::initConstructionModels();
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

    this->renderSelected();
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

glm::vec3 GameRenderer::getWorldPos(glm::vec2 const& viewpos) const
{
    float x = 2.0f * viewpos.x / Window::getInstance()->getWidth() - 1.0f;
    float y = 1.0f - 2.0f * viewpos.y / Window::getInstance()->getHeight();
    glm::vec4 rayclip = glm::vec4(x, y, -1.0f, 1.0f);
    glm::vec4 worldpos = glm::inverse(this->projection) * rayclip;
    worldpos.z = -1.0f, worldpos.w = 0.0f;
    worldpos = glm::inverse(this->getView()) * worldpos;
    glm::vec3 result = glm::vec3(worldpos.x, worldpos.y, worldpos.z);
    glm::vec3 cpos = this->camera->getPos();
    
    if (result.y != 0.0f)
        result /= result.y;
    result = cpos - cpos.y * result;
    return result;
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

void GameRenderer::renderSelected()
{
    glm::vec3 pos = this->getWorldPos(glm::vec2(Game::getInstance()->getController()->getMouseX(), Game::getInstance()->getController()->getMouseY()));
    pos.x = floor(pos.x);
    pos.z = floor(pos.z);
    AABB aabb = AABB(glm::vec3(pos.x, 0.001, pos.z), glm::ivec3(pos.x + 1, 1, pos.z + 1));
    this->renderAABB(aabb);
}

glm::vec3 GameRenderer::getSunPosition() const
{
    float t = (float) Game::getInstance()->getWorld()->getTime() / (float) Game::getInstance()->getWorld()->getTimePerDay() * 360.0f * 0.7f;

    return this->camera->getCenter() + glm::vec3(6.0 * glm::cos(glm::radians(t)), 6.0 * glm::sin(glm::radians(t)), -6.0);
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
