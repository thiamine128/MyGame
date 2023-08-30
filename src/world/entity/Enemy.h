#pragma once

#include "Entity.h"
#include "rendering/Model.h"

#include <vector>
#include <random>


class Enemy : public Entity
{
public:
    Enemy(World*, glm::vec3 const&);
    virtual bool isEnemy();
    virtual void tick();
    virtual void updateAi();
    virtual void onDeath();
protected:
    int aiTick, step;
    bool canSeePlayer;
    std::vector<glm::ivec2> path;
};

class Zombie : public Enemy
{
public:
    Zombie(World*, glm::vec3 const&, int);
protected:
    int type;
};

class ZombieShooter : public Enemy
{
public:
    ZombieShooter(World*, glm::vec3 const&, int);

    virtual void tick();
protected:
    int type;
    int shootTicks;
};

class SlimeBoss : public Enemy
{
public:
    SlimeBoss(World*, glm::vec3 const&);

    virtual void tick();
    virtual void updateAi();
    virtual void onDeath();
protected:
    std::uniform_real_distribution<float> uni;
};

class BabyPlum : public Enemy
{
public:
    BabyPlum(World*, glm::vec3 const&);

    virtual void tick();
    virtual void updateAi();
    virtual void onDeath();
    virtual void onCollide(int);
protected:
    int action, actionTick;
    std::uniform_int_distribution<int> actionUni;
    std::uniform_real_distribution<float> bulletUni;
};

class Dragon : public Enemy
{
public:
    Dragon(World*, glm::vec3 const&);

    virtual void tick();
    virtual void updateAi();
    virtual void onDeath();
    virtual void onCollide(int);
protected:
    int action, actionTick;
    std::uniform_int_distribution<int> actionUni;
    std::uniform_real_distribution<float> bulletUni;
};