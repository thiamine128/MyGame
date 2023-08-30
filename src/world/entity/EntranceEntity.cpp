#include "EntranceEntity.h"

#include "ModelManager.h"
#include "world/World.h"

EntranceEntity::EntranceEntity(World* world, glm::vec3 const& pos) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}})
{
    this->model = ModelManager::getModel("assets/models/entrance.obj");
}

void EntranceEntity::tick()
{
    Entity::tick();
    if (this->world->getPlayer()->getAABB().collideWith(this->getAABB()))
    {
        this->world->prepareNextStage();
    }
}

bool EntranceEntity::isEnemy()
{
    return false;
}