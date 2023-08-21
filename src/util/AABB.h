#pragma once

#include <glm/gtc/type_ptr.hpp>

class AABB
{
public:
    AABB(glm::vec3, glm::vec3);

    bool collideWith(AABB const&) const;
    float getMinX() const;
    float getMinY() const;
    float getMinZ() const;
    float getMaxX() const;
    float getMaxY() const;
    float getMaxZ() const;
    bool insideXZ(glm::vec3 const&) const;
    AABB offset(glm::vec3 const&) const;
protected:
    glm::vec3 min, max;
};