#pragma once

#include <string>

class Item
{
public:
    Item(std::string const&, std::string const&);

    std::string const& getName() const;
    std::string const& getModelPath() const;

    static Item* hoe;
    static Item* potato;
protected:
    std::string name;
    std::string modelPath;
};