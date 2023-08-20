#pragma once

class Shader;
class GameRenderer;

class ShaderManager
{
public:
    static void load();
    static void terminate();

    static const Shader* getDefault();
    static const Shader* getInstanceDefault();
    static const Shader* getShadow();
    static void setupUniforms(const GameRenderer*);
    static void initUniforms(const GameRenderer*);
protected:
    static Shader* defaultShader;
    static Shader* instanceDefaultShader;
    static Shader* shadowShader;
};