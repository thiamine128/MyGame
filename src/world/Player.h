#pragma once

class World;

#include "rendering/Model.h"
#include "item/Inventory.h"
#include "util/AABB.h"
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
    void gain(ItemStack const&);
    ItemStack const& getSlot(int) const;
    AABB getAABB() const;
    AABB getAABB(glm::vec3 const&) const;
protected:
    glm::vec3 pos;
    glm::vec3 prevPos;
    glm::vec3 velocity;
    Inventory inventory;
    World* world;
    const Model* model;
};