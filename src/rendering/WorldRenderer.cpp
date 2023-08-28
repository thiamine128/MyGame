#include "WorldRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Camera.h"
#include "Model.h"
#include "ModelManager.h"
#include "Game.h"
#include "Window.h"
#include "ShaderManager.h"
#include "TextureManager.h"

WorldRenderer::WorldRenderer()
{
    this->camera = new Camera();
    
    ShaderManager::load();
    
    this->projection = glm::mat4(1.0);
    this->lightProjection = glm::ortho(-24.0f, 24.0f, -24.0f, 24.0f, -24.0f, 32.0f);

    this->updateProjection();

    this->defaultShader = ShaderManager::getDefault();

    this->initShadowMap();
    this->initGBuffer();

    this->linesVbo = new VertexBufferObject();
    this->linesVao = new VertexArrayObject();
    this->linesEbo = new ElementBufferObject();
}

WorldRenderer::~WorldRenderer()
{
    
}

void WorldRenderer::setWorld(World* world)
{
    this->world = world;
}

World *WorldRenderer::getWorld() const
{
    return this->world;
}

void WorldRenderer::render()
{
    if (this->world != nullptr)
    {
        glEnable(GL_DEPTH_TEST);
        Player* player = this->world->getPlayer();

        this->camera->update(player);

        ShaderManager::setupUniforms(this);

        glViewport(0, 0, this->shadowWidth, this->shadowHeight);
        this->renderToDepthMap();
        
        glViewport(0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight());
        this->renderDefault();

        this->renderSelected();
    }  
}

Camera* WorldRenderer::getCamera() const
{
    return this->camera;
}

void WorldRenderer::renderToDepthMap()
{
    this->depthMapFramebuffer->bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    this->renderWorld(ShaderManager::getShadow(), true);
    this->depthMapFramebuffer->unbind();
}

void WorldRenderer::renderDefault()
{
    glClearColor(0.5f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE1);
    this->depthMap->bind();
    this->renderWorld(this->defaultShader, false);
}

void WorldRenderer::renderWorld(const Shader* shader, bool shadow)
{
    shader->use();
    this->world->getPlayer()->render(shader);
    this->world->getRoom()->render(shader);
}

void WorldRenderer::updateProjection()
{
    this->projection = glm::perspective(glm::radians(45.0f), (float) Window::getInstance()->getWidth() / (float) Window::getInstance()->getHeight(), 0.1f, 100.0f);

    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
}

glm::vec3 WorldRenderer::getWorldPos(glm::vec2 const& viewpos) const
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

void WorldRenderer::initShadowMap()
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

void WorldRenderer::initGBuffer()
{
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    glGenTextures(1, &gColor);
    glBindTexture(GL_TEXTURE_2D, gColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Window::getInstance()->getWidth(), Window::getInstance()->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gColor, 0);

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(3, attachments);
}

void WorldRenderer::renderAABB(AABB const& aabb) const
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

void WorldRenderer::renderSelected()
{
    glm::vec3 pos = this->getWorldPos(glm::vec2(Game::getInstance()->getController()->getMouseX(), Game::getInstance()->getController()->getMouseY()));
    pos.x = floor(pos.x);
    pos.z = floor(pos.z);
    AABB aabb = AABB(glm::vec3(pos.x, 0.001, pos.z), glm::ivec3(pos.x + 1, 1, pos.z + 1));
    this->renderAABB(aabb);
}

glm::vec3 WorldRenderer::getSunPosition() const
{
    return this->camera->getCenter() + glm::vec3(1.0, 6.0, -1.0);
}

glm::mat4 WorldRenderer::getView() const
{
    return this->camera->getView();
}

glm::mat4 WorldRenderer::getLightSpace() const
{
    return this->lightProjection * glm::lookAt(this->getSunPosition(), this->camera->getCenter(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 WorldRenderer::getProjection() const
{
    return this->projection;
}
