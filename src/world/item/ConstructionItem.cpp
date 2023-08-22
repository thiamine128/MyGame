#include "ConstructionItem.h"

#include "world/World.h"

ConstructionItem::ConstructionItem(std::string const& name, std::string const& modelPath, ConstructionType constructionType) : Item(name, modelPath), constructionType(constructionType)
{
    this->guiTransform = glm::translate(this->guiTransform, glm::vec3(0.0, -0.1, 0.0));
    this->guiTransform = glm::scale(this->guiTransform, glm::vec3(0.5));
    this->guiTransform = glm::rotate(this->guiTransform, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
    this->guiTransform = glm::rotate(this->guiTransform, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
}

void ConstructionItem::use(Player* player, glm::ivec2 const& pos)
{
    World* world = player->getWorld();

    if (world->canBuildAt(pos.x, pos.y, Construction::constructions[this->constructionType]))
    {
        player->decreaseItemCnt();
        world->buildConstruction(pos.x, pos.y, Construction::constructions[this->constructionType]);
    }
}
