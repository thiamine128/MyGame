#include "ShaderManager.h"

#include "Game.h"
#include "rendering/WorldRenderer.h"
#include "rendering/Camera.h"
#include "rendering/GuiRenderer.h"
#include "Window.h"

Shader* ShaderManager::defaultShader = nullptr;
Shader* ShaderManager::instanceDefaultShader = nullptr;
Shader* ShaderManager::shadowShader = nullptr;
Shader* ShaderManager::lineShader = nullptr;
Shader* ShaderManager::guiShader = nullptr;
Shader* ShaderManager::guiModelShader = nullptr;
Shader* ShaderManager::textShader = nullptr;
Shader* ShaderManager::rectShader = nullptr;
Shader* ShaderManager::postShader = nullptr;

//加载着色器
void ShaderManager::load()
{
    defaultShader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");
    instanceDefaultShader = new Shader("assets/shader/instance_default.vsh", "assets/shader/instance_default.fsh");
    shadowShader = new Shader("assets/shader/shadow.vsh", "assets/shader/shadow.fsh");
    lineShader = new Shader("assets/shader/line.vsh", "assets/shader/line.fsh");
    guiShader = new Shader("assets/shader/gui.vsh", "assets/shader/gui.fsh");
    guiModelShader = new Shader("assets/shader/gui_model.vsh", "assets/shader/gui_model.fsh");
    textShader = new Shader("assets/shader/text.vsh", "assets/shader/text.fsh");
    rectShader = new Shader("assets/shader/rect.vsh", "assets/shader/rect.fsh");
    postShader = new Shader("assets/shader/post.vsh", "assets/shader/post.fsh");
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

const Shader *ShaderManager::getRect()
{
    return rectShader;
}

const Shader *ShaderManager::getPost()
{
    return postShader;
}

//更新着色器的uniform变量（频繁修改）
void ShaderManager::setupUniforms(const WorldRenderer* renderer)
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
//更新着色器的uniform变量（不常修改）
void ShaderManager::initUniforms(const WorldRenderer* renderer, const GuiRenderer* gui)
{
    defaultShader->use();
    defaultShader->setInt("shadowMap", 1);
    defaultShader->setMat4("projection", renderer->getProjection());
    defaultShader->setVec4("color", glm::vec4(1.0));
    instanceDefaultShader->use();
    instanceDefaultShader->setInt("shadowMap", 1);
    instanceDefaultShader->setMat4("projection", renderer->getProjection());
    lineShader->use();
    lineShader->setMat4("projection", renderer->getProjection());
    guiShader->use();
    guiShader->setMat4("projection", gui->getProjection());
    guiModelShader->use();
    guiModelShader->setMat4("projection", gui->getProjection());
    textShader->use();
    textShader->setMat4("projection", gui->getProjection());
    textShader->setVec4("color", glm::vec4(1.0));
    rectShader->use();
    rectShader->setMat4("projection", gui->getProjection());
    postShader->use();
    postShader->setInt("gNormal", 0);
    postShader->setInt("gColor", 1);
    postShader->setMat4("projection", gui->getProjection());
    postShader->setInt("screenWidth", Window::getInstance()->getWidth());
    postShader->setInt("screenHeight", Window::getInstance()->getHeight());
}