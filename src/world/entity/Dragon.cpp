#include "Dragon.h"

#include "ModelManager.h"
#include "world/World.h"
#include "EnemyBullet.h"

Dragon::Dragon(World* world, glm::vec3 const& pos) : Enemy(world, pos), actionUni(0, 2), bulletUni(-1.5, 1.5)
{
    this->aabb = {{0, 0, 0}, {3, 3, 3}};
    this->scale = glm::vec3(3.0);
    this->model = ModelManager::getModel("assets/models/dragon.obj");
    this->action = 0;
    this->actionTick = 30;
    this->smooth = false;
    this->health = 240.0;
}

void Dragon::tick()
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
            this->actionTick = 20;
            break;
        case 2:
            
            break;
        default:
            break;
        }
    } else {
        this->actionTick--;
    }

    glm::vec3 faceDir = glm::normalize(player->getPos() - pos);
    if (this->action == 0)
    {
        this->velocity = faceDir * 2.5f;
    } else if (this->action == 1)
    {
        this->velocity = faceDir * 0.1f;
        auto eb = new EnemyBullet(world, this->pos + glm::vec3(bulletUni(rng), 1.5, bulletUni(rng)), faceDir * 4.0f + glm::vec3(bulletUni(rng), bulletUni(rng), bulletUni(rng)) * 0.2f, 0.6f, 4.0f, glm::vec4(1.0, 0.5, 0.0, 1.0));
        this->world->getRoom()->addEntity(eb);
    }
    
    Entity::tick();

    if (this->getAABB().collideWith(player->getAABB()))
    {
        player->hurt(0.5f);
    }
    this->setRotation(glm::atan(this->velocity.x, this->velocity.z));
}

void Dragon::updateAi()
{
}

void Dragon::onDeath()
{
    this->world->addScore(1200);
    world->finish();
}

void Dragon::onCollide(int side)
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