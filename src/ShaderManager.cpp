#include "ShaderManager.h"

Shader* ShaderManager::defaultShader = nullptr;

void ShaderManager::load()
{
    defaultShader = new Shader("assets/shader/default.vsh", "assets/shader/default.fsh");
}

void ShaderManager::terminate()
{
    delete defaultShader;
}

const Shader* ShaderManager::getDefault()
{
    return defaultShader;
}
