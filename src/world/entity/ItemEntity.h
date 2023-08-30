#pragma once

#include "Entity.h"

class ItemEntity : public Entity
{
public:
    ItemEntity(World*, glm::vec3 const&, int);

    virtual void tick();
    virtual bool isItem() const;
    virtual void render(const Shader*) const;
    Item* getItem() const;
protected:
    int item;
    int animateTick;
};