#include "SlimeBoss.h"

#include "ModelManager.h"
#include "world/World.h"
#include "EnemyBullet.h"

SlimeBoss::SlimeBoss(World* world, glm::vec3 const& pos) : Enemy(world, pos), uni(0.0, 1.0)
{
    this->model = ModelManager::getModel("assets/models/slimeboss.obj");
    this->health = 70.0f;
    this->aabb = {{0, 0, 0}, {4, 4, 4}};
    this->scale = glm::vec3(6.0);
}

void SlimeBoss::tick()
{
    if (this->aiTick == 0)
    {
        this->aiTick = 10;
        this->updateAi();
    }
    this->aiTick--;

    if (pos.y > 0.0f)
    {
        this->velocity.y -= 0.05;
    }

    glm::vec3 ppos = this->world->getPlayer()->getPos();
    ppos -= pos;
    ppos = glm::normalize(ppos) * this->speed;
    if (glm::length(ppos) >= this->speed * 0.05f)
        this->velocity.x = ppos.x, this->velocity.z = ppos.z;
    else
    {
        this->velocity.x = 0.0, this->velocity.z = 0.0;
    }

    Player* player = this->world->getPlayer();
    if (this->getAABB().collideWith(player->getAABB()))
    {
        player->hurt(1.0f);
    }
    
    Entity::tick();
    this->setRotation(glm::atan(this->velocity.x, this->velocity.z));
}

void SlimeBoss::updateAi()
{
    
    if (this->pos.y <= 0.1f)
    {
        if (this->velocity.y < -1.0f)
        {
            for (int i = 0; i < 20; ++i)
            {
                auto enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(4 * (uni(rng) - 0.5), uni(rng) + 0.4, 4 * (uni(rng) - 0.5)), 0.5f, 0.0f, glm::vec4(0.2, 0.2, 0.8, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
            }
        }
        this->velocity.y = 1.4f;
    }
}

void SlimeBoss::onDeath()
{
    this->world->getRoom()->spawnEntity(0, 0, 4, 4);
    this->world->getRoom()->spawnEntity(3, 0, 0, 0);
    this->world->addScore(1200);
}