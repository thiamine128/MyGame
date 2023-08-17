#pragma once

#include "world/construction/Construction.h"
#include "rendering/Model.h"

class ConstructionRenderer
{
public:
    ConstructionRenderer();
    ~ConstructionRenderer();

    virtual void render(Construction*) const;
};

