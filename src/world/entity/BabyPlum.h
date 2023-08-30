#pragma once

#include "Enemy.h"

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