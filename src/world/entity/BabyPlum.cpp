#include "BabyPlum.h"

#include "ModelManager.h"
#include "world/World.h"
#include "EnemyBullet.h"
#include "SoundManager.h"

BabyPlum::BabyPlum(World* world, glm::vec3 const& pos) : Enemy(world, pos), actionUni(0, 2), bulletUni(-1.5, 1.5)
{
    this->aabb = {{0, 0, 0}, {3, 3, 3}};
    this->scale = glm::vec3(3.0);
    this->model = ModelManager::getModel("assets/models/babyplum.obj");
    this->action = 0;
    this->actionTick = 30;
    this->smooth = false;
    this->health = 180.0;
}

void BabyPlum::tick()
{
    Player* player = world->getPlayer();
    if (this->actionTick == 0)
    {
        this->action = actionUni(rng);
        switch (action)
        {
        case 0:
            this->actionTick = 20;
            break;
        case 1:
            this->velocity = glm::vec3(0.0, 2.0, 0.0);
            this->actionTick = 30;
            break;
        case 2:
            this->actionTick = 240;
            this->velocity = glm::normalize(player->getPos() - pos) * 7.0f;
            this->velocity.y = 0.0f;
            break;
        default:
            break;
        }
    } else {
        this->actionTick--;
    }
    if (this->action == 0)
    {
        this->velocity = glm::normalize(player->getPos() - pos);
    } else if (this->action == 1)
    {
        this->velocity.y -= 0.2;
        if (this->actionTick == 15)
        {
            const int num = 20;
            SoundManager::play("assets/sounds/shoot.wav");
            for (int i = 0; i < num; ++i)
            {
                double rad = 2.0 * glm::pi<double>() * i / num;
                auto eb = new EnemyBullet(world, this->pos + glm::vec3(0.0, 1.0, 0.0), 6.0f * glm::vec3(glm::sin(rad), 0.0, glm::cos(rad)), 0.6f, 5.0f, glm::vec4(1.0, 0.2, 0.2, 1.0));
                this->world->getRoom()->addEntity(eb);
            }
        }
    } else if (this->action == 2)
    {
        if (this->action % 5 == 0)
            SoundManager::play("assets/sounds/shoot.wav");
        auto eb = new EnemyBullet(world, this->pos + glm::vec3(bulletUni(rng), 1.5, bulletUni(rng)), -2.0f * velocity, 0.6f, 1.0f, glm::vec4(1.0, 0.2, 0.2, 1.0));
        this->world->getRoom()->addEntity(eb);
    }
    Entity::tick();

    if (this->getAABB().collideWith(player->getAABB()))
    {
        player->hurt(0.5f);
    }
    this->setRotation(glm::atan(this->velocity.x, this->velocity.z));
}

void BabyPlum::updateAi()
{
}

void BabyPlum::onDeath()
{
    this->world->getRoom()->spawnEntity(0, 0, 4, 4);
    this->world->getRoom()->spawnEntity(3, 0, 0, 0);
    this->world->addScore(1200);
}

void BabyPlum::onCollide(int side)
{
    if (this->action == 2)
    {
        if (side == 1)
        {
            velocity.x = -velocity.x;
        } else if (side == 2)
        {
            velocity.z = -velocity.z;
        } else if (side == 3)
        {
            velocity.x = -velocity.x;
            velocity.z = -velocity.z;
        }
    }
}

