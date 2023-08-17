#pragma once

#include "rendering/Model.h"

#include <unordered_map>

class ModelManager
{
public:
    static Model const* getModel(std::string const&);
    static void terminate();
protected:
    static std::unordered_map<std::string, Model*> entries;
};