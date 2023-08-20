#pragma once

#include "ConstructionType.h"

#include <glm/gtc/type_ptr.hpp>

class Construction
{
public:
    Construction(ConstructionType, glm::vec3);
protected:
    ConstructionType type;
    glm::vec3 pos;
};