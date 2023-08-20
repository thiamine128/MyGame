#pragma once

class Camera;
class Model;
class World;
class FramebufferObject;

#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "world/Player.h"
#include "world/crop/Crop.h"
#include "InstancedRenderer.h"

#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

class GameRenderer
{
public:
    GameRenderer();
    ~GameRenderer();

    void render();
    Camera* getCamera() const;
    void renderToDepthMap();
    void renderDefault();
    void renderWorld(World*, const Shader*) const;
    void renderChunks(World*, const Shader*) const;
    void updateProjection();
    void initShadowMap();
    glm::vec3 getSunPosition() const;

    glm::mat4 getView() const;
    glm::mat4 getLightSpace() const;
    glm::mat4 getProjection() const;
protected:
    Camera* camera;
    const Model* groundModel;
    const Shader* defaultShader;
    glm::mat4 projection;
    glm::mat4 lightProjection;
    FramebufferObject* depthMapFramebuffer;
    Texture* depthMap;
    int shadowWidth, shadowHeight;
};