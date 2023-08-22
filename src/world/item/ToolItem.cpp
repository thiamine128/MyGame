#include "ToolItem.h"

#include "world/World.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ToolItem::ToolItem(std::string const& name, std::string const& modelPath) : Item(name, modelPath)
{
    this->guiTransform = glm::rotate(this->guiTransform, glm::radians(45.0f), glm::vec3(0.0, 0.0, -1.0));
    this->guiTransform = glm::scale(this->guiTransform, glm::vec3(0.9f));
}

void ToolItem::use(Player* player, glm::ivec2 const& pos)
{
    Item::use(player, pos);
    World* world = player->getWorld();

    if (this == Item::hoe)
    {
        world->setTile(pos.x, pos.y, TileType::Plowland);
    }
}
