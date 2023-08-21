#include "Building.h"

Building::Building(glm::vec3 pos, AABB aabb) : pos(pos), aabb(aabb)
{
}

void Building::render(const Shader *)
{
}

glm::vec3 const& Building::getPos() const
{
    return this->pos;
}

AABB const& Building::getAABB() const
{
    return this->aabb;
}

std::vector<AABB> const &Building::getCollisions() const
{
    return this->collisions;
}
