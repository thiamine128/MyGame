#include "Construction.h"

Construction* Construction::planks = new Construction(ConstructionType::PLANKS, BuildType::FLOOR, AABB(glm::vec3(), glm::vec3()), false);
Construction* Construction::bed = new Construction(ConstructionType::BEDS, BuildType::BLOCK, AABB(glm::vec3(), glm::vec3()), false);

Construction::Construction(ConstructionType type, BuildType buildType, AABB aabb, bool collision) : type(type), buildType(buildType), aabb(aabb), collision(collision)
{
    
}

BuildType const& Construction::getBuildType() const
{
    return this->buildType;
}

AABB const& Construction::getAABB() const
{
    return this->aabb;
}

bool Construction::hasCollision() const
{
    return this->collision;
}

ConstructionType const &Construction::getType() const
{
    return this->type;
}
