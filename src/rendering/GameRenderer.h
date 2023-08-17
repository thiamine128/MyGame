#pragma once

#include "Camera.h"
#include "Model.h"
#include "world/World.h"
#include "rendering/construction/ConstructionRendererDispatcher.h"

class GameRenderer
{
public:
    GameRenderer();
    ~GameRenderer();

    void render() const;
    void renderGround() const;
    Camera* getCamera() const;
    void renderPlayer(Player*) const;
    void renderWorld(World*) const;
    void updateProjectionMatrix();
    void setupViewProjection(const Shader*) const;
protected:
    Camera* camera;
    const Model* groundModel;
    const Model* playerModel;
    const Shader* defaultShader;
    ConstructionRendererDispatcher* constructionRendererDispatcher;
    glm::mat4 projection;
};