#pragma once

#include "rendering/Model.h"
#include "ConstructionRenderer.h"

class SingleModelConstructionRenderer : public ConstructionRenderer
{
public:
    SingleModelConstructionRenderer(const Model*);
    ~SingleModelConstructionRenderer();

    virtual void render(Construction*) const;
protected:
    const Model* model;
};