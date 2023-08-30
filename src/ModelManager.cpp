#include "ModelManager.h"

#include "rendering/Model.h"

std::unordered_map<std::string, Model*> ModelManager::entries;

//模型数据获取（如果没有加载过从文件中加载，否则返回已经加载好的模型）
Model const *ModelManager::getModel(std::string const& path)
{
    if (entries.count(path) == 0)
    {
        entries[path] = new Model(path.c_str());
    }
    return entries[path];
}

//销毁占用的内存
void ModelManager::terminate()
{
    for (auto e : entries) {
        delete e.second;
    }
}