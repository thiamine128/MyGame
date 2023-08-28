#pragma once

class World;
#include "util/AABB.h"
#include "rendering/glhelper.h"
#include "Items.h"
#include "rendering/Model.h"

#include <random>

class Entity
{
public:
    Entity(World*, glm::vec3 const&, AABB const&);

    glm::vec3 getPosFrame() const;
    glm::vec3 getPos() const;
    void setPos(glm::vec3 const&);
    glm::vec3 getVelocity() const;
    AABB getAABB() const;
    AABB getAABB(glm::vec3 const&) const;
    void setVelocity(glm::vec3 const&);
    void remove();
    bool shouldRemove() const;
    virtual void render(const Shader*) const;
    virtual void tick();
    virtual void onCollide();
    virtual bool isEnemy();
    virtual void onDeath();
    virtual void onRemove();
    void freeze(int);
    void hurt(double);
    void setRotation(float);
    World* getWorld();
protected:
    glm::vec3 pos;
    glm::vec3 prevPos;
    glm::vec3 velocity;
    glm::vec3 scale;
    World* world;
    Model const* model;
    AABB aabb;
    bool toRemove;
    double health;
    float rotation;
    float prevRot;
    float speed;
    int freezingTick;
    std::random_device rd;
    std::mt19937 rng;
    int hurtTick;
};

class ItemEntity : public Entity
{
public:
    ItemEntity(World*, glm::vec3 const&, int);

    virtual void tick();
    virtual bool isEnemy();
protected:
    int item;
};

class EntranceEntity : public Entity
{
public:
    EntranceEntity(World*, glm::vec3 const&);

    virtual void tick();
    virtual bool isEnemy();
};