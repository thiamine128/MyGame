#include "Items.h"

#include "World.h"
#include "Player.h"

Item* Item::m[128];
int Item::itemNum = 11;
Item* Item::torchwood = nullptr;
Item* Item::ice = nullptr;
Item* Item::arrow = nullptr;
Item* Item::milk = nullptr;
Item* Item::glass = nullptr;
Item* Item::magician = nullptr;
Item* Item::branch = nullptr;
Item* Item::shoes = nullptr;
Item* Item::kettle = nullptr;
Item* Item::fertilizer = nullptr;
Item* Item::laserbean = nullptr;

Item::Item(std::string const& name, std::string const& modelPath, std::vector<std::string> const& description) : name(name), modelPath(modelPath), description(description)
{

}

std::string const &Item::getModelPath() const
{
    return this->modelPath;
}

std::vector<std::string> const& Item::getDescription() const
{
    return this->description;
}

std::string const &Item::getName() const
{
    return this->name;
}

//拾取道具
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
    } else if (item == branch)
    {
        player->setTripleShot();
    } else if (item == shoes)
    {
        player->addSpeed(1.0f);
    } else if (item == kettle)
    {
        player->addHeart(4);
    } else if (item == fertilizer)
    {
        player->addAtk(1);
    } else if (item == laserbean)
    {
        player->addShootSpeed(128);
    }

    player->getWorld()->addScore(1000);
}

//初始化道具
void Item::init()
{
    m[1] = torchwood = new Item("Torchwood", "assets/models/torchwood.obj", {"Explosive pea", "Damage up"});
    m[2] = ice = new Item("Ice", "assets/models/ice.obj", {"Freezing pea", "Damage up"});
    m[3] = arrow = new Item("Arrow", "assets/models/peaarrow.obj", {"Piercing pea"});
    m[4] = milk = new Item("Milk", "assets/models/milk.obj", {"Shoot speed up"});
    m[5] = glass = new Item("Glass", "assets/models/glass.obj", {"Range up"});
    m[6] = magician = new Item("Magician", "assets/models/magician.obj", {"Tracking shot"});
    m[7] = branch = new Item("Branch", "assets/models/branch.obj", {"Triple shot"});
    m[8] = shoes = new Item("Shoes", "assets/models/shoes.obj", {"Speed up"});
    m[9] = kettle = new Item("Kettle", "assets/models/kettle.obj", {"Health up"});
    m[10] = fertilizer = new Item("Fertilizer", "assets/models/fertilizer.obj", {"Pea size up", "Damage up"});
    m[11] = laserbean = new Item("Laser Bean", "assets/models/laserbean.obj", {"Laser pea"});
}
