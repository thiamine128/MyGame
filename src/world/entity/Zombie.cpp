#include "Zombie.h"

#include "ModelManager.h"

Zombie::Zombie(World* world, glm::vec3 const& pos, int type) : Enemy(world, pos), type(type)
{
    switch(type)
    {
    case 2:
        this->model = ModelManager::getModel("assets/models/zombie2.obj");
        this->health = 7.0f;
        break;
    case 3:
        this->model = ModelManager::getModel("assets/models/zombie3.obj");
        this->health = 10.0f;
        break;
    default:
        this->model = ModelManager::getModel("assets/models/zombie.obj");
        this->health = 5.0f;
        break;
    }

    this->scale = glm::vec3(0.8);
}