#include "PotatoMine.h"

#include "ModelManager.h"
#include "world/World.h"

PotatoMine::PotatoMine(World* world, glm::vec3 const& pos) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}}), uni(-1, 1)
{
    this->model = ModelManager::getModel("assets/models/potatomine.obj");
}

void PotatoMine::tick()
{
    Entity::tick();

    std::vector<Entity*> ent;
    world->getRoom()->getEnemiesWithin(ent, this->getAABB().inflate({2, 2, 2}));
    bool explode = false;
    for (auto e : ent)
    {
        if (e->getAABB().collideWith(this->getAABB()))
        {
            explode = true;
            break;
        }
    }

    if (explode)
    {
        for (auto e : ent)
        {
            e->hurt(30.0f);
        }
        this->remove();
        for (int i = 0; i < 16; ++i)
        {
            world->getRoom()->addParticle(pos, glm::vec3(uni(rng), 1 + uni(rng), uni(rng)), glm::vec3(0.8, 0.6, 0.28), 40);
        }
    }
}