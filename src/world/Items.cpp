#include "Items.h"

#include "Player.h"

Item* Item::m[128];
Item* Item::torchwood = nullptr;
Item* Item::ice = nullptr;
Item* Item::arrow = nullptr;
Item* Item::milk = nullptr;
Item* Item::glass = nullptr;

Item::Item(std::string const& name, std::string const& modelPath) : name(name), modelPath(modelPath)
{

}

std::string const &Item::getModelPath() const
{
    return this->modelPath;
}

void Item::onPickup(Item* item, Player* player)
{
    if (item == torchwood)
    {
        player->addAtk(0.5);
    } else if (item == ice)
    {
        player->addAtk(0.5);
    } else if (item == milk)
    {
        player->addShootSpeed(4);
    } else if (item == glass)
    {
        player->addRange(2.0f);
    }
}

void Item::init()
{
    m[1] = torchwood = new Item("Torchwood", "assets/models/torchwood.obj");
    m[2] = ice = new Item("Ice", "assets/models/ice.obj");
    m[3] = arrow = new Item("Arrow", "assets/models/peaarrow.obj");
    m[4] = milk = new Item("Milk", "assets/models/milk.obj");
    m[5] = glass = new Item("Glass", "assets/models/glass.obj");
}
