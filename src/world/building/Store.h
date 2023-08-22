#pragma once

#include "rendering/Model.h"
#include "Building.h"

class Store : public Building
{
public:
    Store(glm::vec3);

    virtual void render(const Shader*);
protected:
    const Model* model;
};