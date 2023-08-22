#pragma once

#include "rendering/glhelper.h"
#include "util/AABB.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Building
{
public:
    Building(glm::vec3 pos, AABB aabb);

    virtual void render(const Shader*);

    glm::vec3 const& getPos() const;
    AABB const& getAABB() const;
    std::vector<AABB> const& getCollisions() const;
protected:
    glm::vec3 pos;
    AABB aabb;
    std::vector<AABB> collisions;
};