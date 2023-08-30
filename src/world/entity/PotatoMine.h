#pragma once

#include "Entity.h"

class PotatoMine : public Entity
{
public:
    PotatoMine(World*, glm::vec3 const&);

    virtual void tick();
protected:
    std::uniform_real_distribution<float> uni;
};