#pragma once

class Model;

#include <unordered_map>
#include <string>

class ModelManager
{
public:
    static const Model* getModel(std::string const&);
    static void terminate();
protected:
    static std::unordered_map<std::string, Model*> entries;
};