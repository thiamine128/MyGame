#pragma once

class World;

#include "rendering/Model.h"
#include <glm/gtc/type_ptr.hpp>

class Player
{
public:
    Player(World*);
    ~Player();

    glm::vec3 getPosFrame() const;
    glm::vec3 getPos() const;
    glm::vec3 getVelocity() const;
    void setVelocity(glm::vec3 const&);
    void render(Shader const*) const;
    void tick();
    void plow();
protected:
    glm::vec3 pos;
    glm::vec3 prevPos;
    glm::vec3 velocity;
    World* world;
    const Model* model;
};