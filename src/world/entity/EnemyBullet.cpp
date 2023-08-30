#include "EnemyBullet.h"

#include "world/World.h"
#include "ModelManager.h"

EnemyBullet::EnemyBullet(World* world, glm::vec3 const& pos, glm::vec3 const& velocity, float size, float range, glm::vec4 const& color) : Entity(world, pos, {{0, 0, 0}, {size, size, size}}), size(size), color(color), uni(-1.0, 1.0), range(range)
{
    this->velocity = velocity;
    this->model = ModelManager::getModel("assets/models/enemybullet.obj");
    this->initialPos = pos;
}

void EnemyBullet::render(const Shader *shader) const
{
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, this->getPosFrame());
    model = glm::scale(model, glm::vec3(size));
    model = glm::rotate(model, this->rotation, glm::vec3(0.0, 1.0, 0.0));
    
    shader->setMat4("model", model);
    shader->setVec4("color", color);

    this->model->render(shader);
    shader->setVec4("color", glm::vec4(1.0f));
}

void EnemyBullet::tick()
{
    if (glm::length(initialPos - pos) >= range)
        this->velocity.y -= 0.15;
    Entity::tick();

    if (this->world->getPlayer()->getAABB().collideWith(this->getAABB()))
    {
        this->world->getPlayer()->hurt(0.5f);
        this->onCollide(0);
    }
    
    this->setRotation(glm::atan(this->velocity.x, this->velocity.z));
}

void EnemyBullet::onCollide(int)
{
    this->remove();
}

void EnemyBullet::onRemove()
{
    for (int i = 0; i < 6; ++i)
    {
        this->world->getRoom()->addParticle(this->pos, glm::vec3(uni(rng), uni(rng), uni(rng)), color);
    }
}
