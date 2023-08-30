#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
    Zombie(World*, glm::vec3 const&, int);
protected:
    int type;
};