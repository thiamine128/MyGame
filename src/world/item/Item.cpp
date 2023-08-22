#include "Item.h"

#include "world/World.h"

#include "ToolItem.h"
#include "SeedItem.h"
#include "ConstructionItem.h"

Item* Item::hoe = new ToolItem("Hoe", "assets/model/item/hoe.obj");
Item* Item::potato = new Item("Potato", "assets/model/item/potato.obj");
Item* Item::potatoSeeds = new SeedItem("Potato Seeds", "assets/model/item/potato_seeds.obj");
Item* Item::planks = new ConstructionItem("Planks", "assets/model/construction/planks.obj", ConstructionType::PLANKS);
Item* Item::fence = new ConstructionItem("Planks", "assets/model/construction/fence.obj", ConstructionType::FENCE);

Item::Item(std::string const& name, std::string const& modelPath) : name(name), modelPath(modelPath)
{
    this->guiTransform = glm::mat4(1.0);
}

std::string const &Item::getModelPath() const
{
    return this->modelPath;
}

glm::mat4 const &Item::getGuiTransform() const
{
    return this->guiTransform;
}

void Item::use(Player* player, glm::ivec2 const& pos)
{
    const Crop* crop = player->getWorld()->getCrop(pos.x, pos.y);
    World* world = player->getWorld();

    if (crop != nullptr && crop->getStage() == crop->getMaxStage())
    {
        world->harvest(pos.x, pos.y);
        player->gain({Item::potato, 1});
    }
}

std::string const &Item::getName() const
{
    return this->name;
}
