#include "Enemy.h"

#include "ModelManager.h"
#include "util/Pathfinder.h"
#include "SoundManager.h"
#include "world/World.h"
#include "Bullet.h"
#include "Game.h"
#include "EnemyBullet.h"

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

void Enemy::onDeath()
{
    world->addScore(100);
}