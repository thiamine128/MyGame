#pragma once

#include "Entity.h"

class EntranceEntity : public Entity
{
public:
    EntranceEntity(World*, glm::vec3 const&);

    virtual void tick();
    virtual bool isEnemy();
};