#pragma once

#include "CropProperties.h"

#include <glm/gtc/type_ptr.hpp>

class Crop
{
public:
    Crop(CropProperties*, glm::ivec2);
    
    virtual void tick();
    const Mesh* getMesh() const;
    int getDay() const;
    void setDay(int);
    int getMaxStage() const;
    int getStage() const;
protected:
    glm::ivec2 pos;
    CropProperties* properties;
    int day;
};