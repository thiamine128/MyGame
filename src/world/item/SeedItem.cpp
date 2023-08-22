#include "SeedItem.h"

#include "world/World.h"
#include "world/crop/Crop.h"

SeedItem::SeedItem(std::string const& name, std::string const& modelPath) : Item(name, modelPath)
{
    this->guiTransform = glm::rotate(this->guiTransform, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
}

void SeedItem::use(Player* player, glm::ivec2 const& pos)
{
    const Crop* crop = player->getWorld()->getCrop(pos.x, pos.y);
    World* world = player->getWorld();
    if (crop == nullptr && world->getTile(pos.x, pos.y) == TileType::Plowland)
    {
        world->sow(pos.x, pos.y, CropProperties::potato);
        player->decreaseItemCnt();
    }
}
