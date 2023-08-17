#pragma once

#include "rendering/Shader.h"

class ShaderManager
{
public:
    static void load();
    static void terminate();

    static const Shader* getDefault();
protected:
    static Shader* defaultShader;
};