#pragma once

#include "rendering/Model.h"
#include "Building.h"

class House : public Building
{
public:
    House(glm::vec3);

    virtual void render(const Shader*);
protected:
    const Model* model;
};