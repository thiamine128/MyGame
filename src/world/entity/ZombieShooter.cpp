#include "ZombieShooter.h"

#include "world/World.h"
#include "SoundManager.h"
#include "ModelManager.h"
#include "EnemyBullet.h"

ZombieShooter::ZombieShooter(World* world, glm::vec3 const& pos, int type) : Enemy(world, pos), type(type)
{
    switch (type)
    {
    case 2:
        this->health = 10.0f;
        this->model = ModelManager::getModel("assets/models/zombieshooter2.obj");
        break;
    
    default:
        this->health = 5.0f;
        this->model = ModelManager::getModel("assets/models/zombieshooter.obj");
        break;
    }

    this->scale = glm::vec3(0.8);
    this->speed = 0.9f;
    this->shootTicks = 20;
}

void ZombieShooter::tick()
{
    Enemy::tick();
    if (this->shootTicks)
    {
        this->shootTicks--;
    } else
    {
        this->shootTicks = 20;
        if (this->canSeePlayer)
        {
            glm::vec3 ppos = world->getPlayer()->getPos();
            SoundManager::play("assets/sounds/shoot.wav");
            if (this->type == 2)
            {
                float shotSpeed = 0.75;
                auto enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), shotSpeed * glm::vec3(3.0f, 0.0, 0.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), shotSpeed * glm::vec3(-3.0f, 0.0, 0.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), shotSpeed * glm::vec3(0.0f, 0.0, 3.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), shotSpeed * glm::vec3(0.0f, 0.0, -3.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
            } else
            {
                auto enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::normalize(ppos - pos) * 2.0f, 0.4f, 4.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
            }
        }
    }
}