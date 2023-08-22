#pragma once

class Shader;
class WorldRenderer;
class GuiRenderer;

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
    static const Shader* getText();
    static void setupUniforms(const WorldRenderer*);
    static void initUniforms(const WorldRenderer*, const GuiRenderer*);
protected:
    static Shader* defaultShader;
    static Shader* instanceDefaultShader;
    static Shader* shadowShader;
    static Shader* lineShader;
    static Shader* guiShader;
    static Shader* guiModelShader;
    static Shader* textShader;
};