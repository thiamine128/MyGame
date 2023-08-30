#pragma once

#include "Entity.h"

class StoneShooter : public Entity
{
public:
    StoneShooter(World*, glm::vec3 const&, int);

    virtual void tick();
    virtual bool isEnemy();

protected:
    int dir;
    int shootTick;
};