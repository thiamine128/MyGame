#pragma once

#include "Enemy.h"

class ZombieShooter : public Enemy
{
public:
    ZombieShooter(World*, glm::vec3 const&, int);

    virtual void tick();
protected:
    int type;
    int shootTicks;
};
