#pragma once

#include "Entity.h"

class EnemyBullet : public Entity
{
public:
    EnemyBullet(World*, glm::vec3 const&, glm::vec3 const&, float, float, glm::vec4 const&);

    virtual void render(const Shader*) const;
    virtual void tick();
    virtual void onCollide(int);
    virtual void onRemove();

protected:
    glm::vec4 color;
    float size;
    glm::vec3 initialPos;
    float range;
    std::uniform_real_distribution<float> uni;
};