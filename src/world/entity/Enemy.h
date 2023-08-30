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