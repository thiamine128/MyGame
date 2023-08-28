#include "Enemy.h"

#include "ModelManager.h"
#include "util/Pathfinder.h"
#include "World.h"
#include "Bullet.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Enemy::Enemy(World* world, glm::vec3 const& pos) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}})
{
    this->aiTick = 10;
    this->step = 0;
    this->canSeePlayer = false;

    this->speed = 1.5f;
}

bool Enemy::isEnemy()
{
    return true;
}

void Enemy::tick()
{
    if (this->aiTick == 0)
    {
        this->aiTick = 10;
        this->updateAi();
    }
    this->aiTick--;
    glm::vec3 ppos = this->world->getPlayer()->getPos();
    ppos -= pos;
    if (glm::length(ppos) >= this->speed * 0.05f && this->canSeePlayer)
        this->setVelocity(glm::normalize(ppos) * this->speed);
    else
    {
        this->setVelocity(glm::vec3(0));
    }

    Player* player = this->world->getPlayer();
    if (this->getAABB().collideWith(player->getAABB()))
    {
        player->hurt(0.5f);
    }
    Entity::tick();
    this->setRotation(glm::atan(this->velocity.x, this->velocity.z));
}

void Enemy::updateAi()
{
    glm::vec3 ppos = this->world->getPlayer()->getPos();
    this->canSeePlayer = Pathfinder::findPath(this->world->getRoom(), {floor(pos.x), floor(pos.z)}, {floor(ppos.x), floor(ppos.z)}, this->path);
    this->step = 0;
}

Zombie::Zombie(World* world, glm::vec3 const& pos, int type) : Enemy(world, pos), type(type)
{
    switch(type)
    {
    case 2:
        this->model = ModelManager::getModel("assets/models/zombie2.obj");
        this->health = 10.0f;
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

SlimeBoss::SlimeBoss(World* world, glm::vec3 const& pos) : Enemy(world, pos), uni(0.0, 1.0)
{
    this->model = ModelManager::getModel("assets/models/slimeboss.obj");
    this->health = 40.0f;
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
    this->world->getRoom()->spawnEntity(3, 0, 0, 0);
}

ZombieShooter::ZombieShooter(World* world, glm::vec3 const& pos, int type) : Enemy(world, pos), type(type)
{
    switch (type)
    {
    case 2:
        this->health = 20.0f;
        this->model = ModelManager::getModel("assets/models/zombieshooter2.obj");
        break;
    
    default:
        this->health = 10.0f;
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
            if (this->type == 2)
            {
                auto enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(3.0f, 0.0, 0.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(-3.0f, 0.0, 0.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0f, 0.0, 3.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
                enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0f, 0.0, -3.0f), 0.4f, 3.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
            } else
            {
                auto enemyBullet = new EnemyBullet(this->world, this->pos + glm::vec3(0.0, 1.0, 0.0), glm::normalize(ppos - pos) * 4.0f, 0.4f, 4.0f, glm::vec4(1.0, 0.8, 0.0, 1.0));
                this->world->getRoom()->addEntity(enemyBullet);
            }
        }
    }
}
