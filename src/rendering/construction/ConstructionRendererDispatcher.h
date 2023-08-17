#pragma once

#include "world/construction/ConstructionType.h"
#include "world/construction/Construction.h"
#include "ConstructionRenderer.h"
#include <unordered_map>

class ConstructionRendererDispatcher
{
public:
    void init();

    void render(Construction*);
protected:
    std::unordered_map<ConstructionType, ConstructionRenderer*> entries;
};