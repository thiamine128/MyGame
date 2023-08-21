#pragma once

class Shader;
class GameRenderer;
class GUI;

class ShaderManager
{
public:
    static void load();
    static void terminate();

    static const Shader* getDefault();
    static const Shader* getInstanceDefault();
    static const Shader* getShadow();
    static const Shader* getLine();
    static const Shader* getGui();
    static const Shader* getGuiModel();
    static void setupUniforms(const GameRenderer*);
    static void initUniforms(const GameRenderer*, const GUI*);
protected:
    static Shader* defaultShader;
    static Shader* instanceDefaultShader;
    static Shader* shadowShader;
    static Shader* lineShader;
    static Shader* guiShader;
    static Shader* guiModelShader;
};