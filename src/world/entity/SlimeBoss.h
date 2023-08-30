#pragma once

#include "Enemy.h"

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