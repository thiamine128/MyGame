#include "ShaderManager.h"

#include "rendering/GameRenderer.h"
#include "rendering/Camera.h"

Shader* ShaderManager::defaultShader = nullptr;
Shader* ShaderManager::instanceDefaultShader = nullptr;
Shader* ShaderManager::shadowShader = nullptr;

void ShaderManager::load()
{
    defaultShader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");
    instanceDefaultShader = new Shader("assets/shader/instance_default.vsh", "assets/shader/instance_default.fsh");
    shadowShader = new Shader("assets/shader/shadow.vsh", "assets/shader/shadow.fsh");
}

void ShaderManager::terminate()
{
    delete defaultShader;
}

const Shader* ShaderManager::getDefault()
{
    return defaultShader;
}

const Shader *ShaderManager::getInstanceDefault()
{
    return instanceDefaultShader;
}

const Shader *ShaderManager::getShadow()
{
    return shadowShader;
}

void ShaderManager::setupUniforms(const GameRenderer* renderer)
{
    defaultShader->use();
    defaultShader->setMat4("view", renderer->getView());
    defaultShader->setMat4("lightSpace", renderer->getLightSpace());
    defaultShader->setVec3("lightPos", renderer->getSunPosition());
    instanceDefaultShader->use();
    instanceDefaultShader->setMat4("view", renderer->getView());
    instanceDefaultShader->setMat4("lightSpace", renderer->getLightSpace());
    instanceDefaultShader->setVec3("lightPos", renderer->getSunPosition());
    shadowShader->use();
    shadowShader->setMat4("lightSpace", renderer->getLightSpace());
}

void ShaderManager::initUniforms(const GameRenderer* renderer)
{
    defaultShader->use();
    defaultShader->setInt("shadowMap", 1);
    defaultShader->setMat4("projection", renderer->getProjection());
    instanceDefaultShader->use();
    instanceDefaultShader->setInt("shadowMap", 1);
    instanceDefaultShader->setMat4("projection", renderer->getProjection());
}
