#include "Item.h"

Item* Item::hoe = new Item("Hoe", "assets/model/item/hoe.obj");
Item* Item::potato = new Item("Potato", "assets/model/item/potato.obj");


Item::Item(std::string const& name, std::string const& modelPath) : name(name), modelPath(modelPath)
{

}

std::string const &Item::getModelPath() const
{
    return this->modelPath;
}

std::string const &Item::getName() const
{
    return this->name;
}
