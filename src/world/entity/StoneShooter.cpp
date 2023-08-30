#include "StoneShooter.h"

#include "ModelManager.h"
#include "EnemyBullet.h"
#include "world/World.h"

StoneShooter::StoneShooter(World* world, glm::vec3 const& pos, int dir) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}})
{
    this->model = ModelManager::getModel("assets/models/stoneshooter.obj");
    this->setRotation(glm::radians(dir / 4.0 * 360.0 + 180.0));
    this->shootTick = 40;
    this->dir = dir;
}

void StoneShooter::tick()
{
    if (this->shootTick)
    {
        this->shootTick--;
    } else
    {
        this->shootTick = 40;
        glm::vec3 v[] =
        {
            {0, 0, 1},
            {1, 0, 0},
            {0, 0, -1},
            {-1, 0, 0}
        };
        auto eb = new EnemyBullet(world, pos + v[dir] * 0.6f + glm::vec3(0.0, 0.2, 0.0), v[dir] * 2.0f, 0.3f, 4.0f, glm::vec4(0.5, 0.5, 0.5, 1.0));
        world->getRoom()->addEntity(eb);
    }
}

bool StoneShooter::isEnemy()
{
    return false;
}
