#include "Entity.h"

#include "Game.h"
#include "ModelManager.h"

#include <iostream>


Entity::Entity(World* world, glm::vec3 const& pos, AABB const& aabb) : world(world), pos(pos), aabb(aabb), rng(rd())
{
    this->toRemove = false;
    this->prevPos = pos;

    this->health = 3;
    this->rotation = 0.0f;
    this->prevRot = 0.0f;
    this->speed = 2.0f;
    this->freezingTick = 0;
    this->scale = glm::vec3(1.0);
    this->hurtTick = 0;
}


glm::vec3 Entity::getPosFrame() const
{
    return glm::mix(this->prevPos, this->pos, Game::getInstance()->getDeltaTime() / 0.05f);
}

glm::vec3 Entity::getPos() const
{
    return this->pos;
}

void Entity::setPos(glm::vec3 const& pos)
{
    this->prevPos = this->pos = pos;
}

glm::vec3 Entity::getVelocity() const
{
    return this->velocity;
}

void Entity::setVelocity(glm::vec3 const& velocity)
{
    this->velocity = velocity;
}

void Entity::remove()
{
    this->toRemove = true;
    this->onRemove();
}

bool Entity::shouldRemove() const
{
    return this->toRemove;
}

AABB Entity::getAABB() const
{
    return this->getAABB(this->pos);
}

AABB Entity::getAABB(glm::vec3 const& pos) const
{
    return AABB(pos - glm::vec3(aabb.getMaxX() / 2.0f, 0.0, aabb.getMaxZ() / 2.0f), pos + glm::vec3(aabb.getMaxX() / 2.0f, aabb.getMaxY(), aabb.getMaxZ() / 2.0f));
}

void Entity::render(const Shader* shader) const
{
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, this->getPosFrame());
    model = glm::rotate(model, this->rotation, glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, scale);

    shader->setMat4("model", model);

    if (this->hurtTick > 0)
    {
        shader->setVec4("color", glm::vec4(1.0, 0.5, 0.5, 1.0));
    } else if (this->freezingTick > 0)
    {
        shader->setVec4("color", glm::vec4(0.5, 0.5, 1.0, 1.0));
    }

    this->model->render(shader);

    if (this->hurtTick > 0 || this->freezingTick > 0)
    {
        shader->setVec4("color", glm::vec4(1.0));
    }
}

void Entity::tick()
{
    glm::vec3 nextPos;
    if (this->freezingTick > 0)
    {
        this->freezingTick--;
        nextPos = this->pos + this->velocity * 0.05f * 0.5f;
    } else {
        nextPos = this->pos + this->velocity * 0.05f;
    }
    bool collided = false;

    if (this->hurtTick > 0)
    {
        this->hurtTick--;
    }

    this->prevPos = this->pos;
    collided = this->world->getRoom()->checkCollision(this->getAABB(nextPos));
    if (!collided)
    {
        this->pos = nextPos;
    }
    else
    {
        this->onCollide();
    }

    if (this->health <= 0)
    {
        this->remove();
        this->onDeath();
    }
}

void Entity::onCollide()
{
}

bool Entity::isEnemy()
{
    return false;
}

void Entity::onDeath()
{
}

void Entity::onRemove()
{

}

void Entity::freeze(int ticks)
{
    this->freezingTick = ticks;
}

void Entity::hurt(double damage)
{
    this->health -= damage;
    this->hurtTick = 10;
}

void Entity::setRotation(float rotation)
{
    this->prevRot = this->rotation;
    this->rotation = rotation;
}

World *Entity::getWorld()
{
    return this->world;
}

ItemEntity::ItemEntity(World* world, glm::vec3 const& pos, int item) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}}), item(item)
{
    this->model = ModelManager::getModel(Item::m[item]->getModelPath());
}

void ItemEntity::tick()
{
    if (this->world->getPlayer()->getAABB().collideWith(this->getAABB()))
    {
        this->world->getPlayer()->gainItem(Item::m[item]);
        this->remove();
    }
}

bool ItemEntity::isEnemy()
{
    return false;
}

EntranceEntity::EntranceEntity(World* world, glm::vec3 const& pos) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}})
{
    this->model = ModelManager::getModel("assets/models/entrance.obj");
}

void EntranceEntity::tick()
{
    Entity::tick();
    if (this->world->getPlayer()->getAABB().collideWith(this->getAABB()))
    {
        this->world->prepareNextStage();
    }
}

bool EntranceEntity::isEnemy()
{
    return false;
}