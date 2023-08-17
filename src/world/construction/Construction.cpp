#include "Construction.h"

Construction::Construction(glm::vec3 pos, ConstructionType type)
{
    this->pos = pos;
    this->type = type;
}

Construction::~Construction()
{

}

glm::vec3 Construction::getPos()
{
    return this->pos;
}

ConstructionType Construction::getType() const
{
    return this->type;
}
