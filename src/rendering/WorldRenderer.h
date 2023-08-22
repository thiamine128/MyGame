#pragma once

class Camera;
class Model;
class World;
class FramebufferObject;

#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "world/World.h"
#include "world/crop/Crop.h"
#include "InstancedRenderer.h"
#include "util/AABB.h"
#include "world/construction/ConstructionType.h"

#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

class WorldRenderer
{
public:
    WorldRenderer();
    ~WorldRenderer();

    void setWorld(World*);
    World* getWorld() const;
    void render();
    Camera* getCamera() const;
    void updateProjection();
    glm::vec3 getWorldPos(glm::vec2 const&) const;
    glm::vec3 getSunPosition() const;
    glm::mat4 getView() const;
    glm::mat4 getLightSpace() const;
    glm::mat4 getProjection() const;
protected:
    World* world;
    Camera* camera;
    const Model* groundModel;
    const Shader* defaultShader;
    glm::mat4 projection;
    glm::mat4 lightProjection;
    FramebufferObject* depthMapFramebuffer;
    Texture* depthMap;
    int shadowWidth, shadowHeight;
    VertexArrayObject* linesVao;
    VertexBufferObject* linesVbo;
    ElementBufferObject* linesEbo;
    
    void renderToDepthMap();
    void renderDefault();
    void renderWorld(const Shader*, bool);
    void renderChunks(const Shader*, bool);
    void initShadowMap();
    void renderAABB(AABB const&) const;
    void renderSelected();
};