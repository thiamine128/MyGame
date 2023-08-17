#pragma once

#include "ConstructionType.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Construction
{
public:
    Construction(glm::vec3, ConstructionType);
    ~Construction();

    glm::vec3 getPos();
    ConstructionType getType() const;
protected:
    ConstructionType type;
    glm::vec3 pos;
};