#include "ItemEntity.h"

#include "ModelManager.h"
#include "world/World.h"


ItemEntity::ItemEntity(World* world, glm::vec3 const& pos, int item) : Entity(world, pos, {{0, 0, 0}, {1, 1, 1}}), item(item)
{
    this->model = ModelManager::getModel(Item::m[item]->getModelPath());
    this->animateTick = 0;
}

void ItemEntity::tick()
{
    this->animateTick++;
    this->prevPos = this->pos;
    this->pos.y = 0.2f + glm::sin(this->animateTick * 0.2) * 0.05;
    if (this->world->getPlayer()->getAABB().collideWith(this->getAABB()))
    {
        this->world->getPlayer()->gainItem(Item::m[item]);
        this->remove();
    }
}

bool ItemEntity::isItem() const
{
    return true;
}

void ItemEntity::render(const Shader* shader) const
{
    Entity::render(shader);

    glm::mat4 model = glm::mat4(1.0f);
    auto cur = this->getPosFrame();
    model = glm::translate(model, glm::vec3(cur.x, 0.0, cur.z));
    shader->setMat4("model", model);

    ModelManager::getModel("assets/models/itembase.obj")->render(shader);
}

Item* ItemEntity::getItem() const
{
    return Item::m[item];
}