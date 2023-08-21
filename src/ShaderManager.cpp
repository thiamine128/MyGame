#include "ShaderManager.h"

#include "rendering/GameRenderer.h"
#include "rendering/Camera.h"
#include "GUI.h"

Shader* ShaderManager::defaultShader = nullptr;
Shader* ShaderManager::instanceDefaultShader = nullptr;
Shader* ShaderManager::shadowShader = nullptr;
Shader* ShaderManager::lineShader = nullptr;
Shader* ShaderManager::guiShader = nullptr;
Shader* ShaderManager::guiModelShader = nullptr;
Shader* ShaderManager::textShader = nullptr;

void ShaderManager::load()
{
    defaultShader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");
    instanceDefaultShader = new Shader("assets/shader/instance_default.vsh", "assets/shader/instance_default.fsh");
    shadowShader = new Shader("assets/shader/shadow.vsh", "assets/shader/shadow.fsh");
    lineShader = new Shader("assets/shader/line.vsh", "assets/shader/line.fsh");
    guiShader = new Shader("assets/shader/gui.vsh", "assets/shader/gui.fsh");
    guiModelShader = new Shader("assets/shader/gui_model.vsh", "assets/shader/gui_model.fsh");
    textShader = new Shader("assets/shader/text.vsh", "assets/shader/text.fsh");
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

const Shader *ShaderManager::getLine()
{
    return lineShader;
}

const Shader *ShaderManager::getGui()
{
    return guiShader;
}

const Shader *ShaderManager::getGuiModel()
{
    return guiModelShader;
}

const Shader * ShaderManager::getText()
{
    return textShader;
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
    lineShader->use();
    lineShader->setMat4("view", renderer->getView());
    shadowShader->use();
    shadowShader->setMat4("lightSpace", renderer->getLightSpace());
}

void ShaderManager::initUniforms(const GameRenderer* renderer, const GUI* gui)
{
    defaultShader->use();
    defaultShader->setInt("shadowMap", 1);
    defaultShader->setMat4("projection", renderer->getProjection());
    instanceDefaultShader->use();
    instanceDefaultShader->setInt("shadowMap", 1);
    instanceDefaultShader->setMat4("projection", renderer->getProjection());
    lineShader->use();
    lineShader->setMat4("projection", renderer->getProjection());
    guiShader->use();
    guiModelShader->setMat4("projection", gui->getProjection());
    guiModelShader->use();
    guiModelShader->setMat4("projection", gui->getProjection());
    textShader->use();
    textShader->setMat4("projection", gui->getProjection());
}
