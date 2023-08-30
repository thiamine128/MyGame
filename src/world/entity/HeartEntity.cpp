#include "HeartEntity.h"

#include "ModelManager.h"
#include "world/World.h"

HeartEntity::HeartEntity(World* world, glm::vec3 const& pos) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}})
{
    this->model = ModelManager::getModel("assets/models/heart.obj");
}

void HeartEntity::tick()
{
    Entity::tick();
    Player* player = world->getPlayer();
    if (player->getAABB().collideWith(this->getAABB()))
    {
        if (player->getHealth() < player->getHearts())
        {
            this->remove();
            player->heal();
        }
    }
}