#pragma once

#include "ConstructionType.h"

#include "util/AABB.h"

#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

class Construction
{
public:
    Construction(ConstructionType, BuildType, AABB, bool);

    BuildType const& getBuildType() const;
    AABB const& getAABB() const;
    bool hasCollision() const;
    ConstructionType const& getType() const;

    static Construction* planks;
    static Construction* bed;
    static Construction* fence;

    static std::unordered_map<ConstructionType, Construction*> constructions;
protected:
    ConstructionType type;
    BuildType buildType;
    AABB aabb;
    bool collision;
};