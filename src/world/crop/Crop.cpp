#include "Crop.h"

Crop::Crop(CropProperties* properties, glm::ivec2 pos) : properties(properties), pos(pos)
{
    this->day = 0;
}

void Crop::tick()
{
}

const Mesh *Crop::getMesh() const
{
    return this->properties->getMesh(this->day);
}

int Crop::getDay() const
{
    return this->day;
}

void Crop::setDay(int day)
{
    this->day = day;
}

int Crop::getMaxStage() const
{
    return this->properties->getMaxStage();
}

int Crop::getStage() const
{
    return this->properties->getStage(this->day);
}
