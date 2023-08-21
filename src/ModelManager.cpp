#include "ModelManager.h"

#include "rendering/Model.h"

std::unordered_map<std::string, Model*> ModelManager::entries;

Model const *ModelManager::getModel(std::string const& path)
{
    if (entries.count(path) == 0)
    {
        entries[path] = new Model(path.c_str());
    }
    return entries[path];
}

void ModelManager::terminate()
{
    for (auto e : entries) {
        delete e.second;
    }
}