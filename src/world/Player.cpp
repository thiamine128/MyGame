#include "Player.h"

#include "Game.h"

#include <iostream>


#include "ModelManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Player::Player(World* world)
{
    this->pos = glm::vec3(0.0);
    this->velocity = glm::vec3(0.0);
    this->world = world;

    this->model = ModelManager::getModel("assets/model/stickman.obj");

    this->gain({Item::hoe, 1});
}

Player::~Player()
{
}

glm::vec3 Player::getPosFrame() const
{
    return glm::mix(this->prevPos, this->pos, Game::getInstance()->getDeltaTime() / 0.05f);
}

glm::vec3 Player::getPos() const
{
    return this->pos;
}

glm::vec3 Player::getVelocity() const
{
    return this->velocity;
}

void Player::setVelocity(glm::vec3 const& velocity)
{
    this->velocity = velocity;
}

void Player::render(Shader const* shader) const
{
    shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, this->getPosFrame());

    glm::vec3 t = this->getPosFrame();
    
    shader->setMat4("model", model);

    this->model->render(shader);
}

void Player::tick()
{
    this->velocity = Game::getInstance()->getController()->getVelocity();
    glm::vec3 nextPos = this->pos + this->velocity * 0.05f;
    std::vector<Chunk*> chunks;
    this->world->getNearbyChunks(glm::vec2(this->pos.x, this->pos.z), chunks);
    bool collided = false;
    for (auto chunk : chunks)
    {
        if (chunk->collide(this->getAABB(nextPos)))
        {
            collided = true;
            break;
        }
    }

    this->prevPos = this->pos;
    if (!collided)
    {
        this->pos = nextPos;
    }
}

void Player::plow()
{
    if (this->world->getTile(this->pos.x, this->pos.z) == TileType::Plowland)
    {
        const Crop* crop = this->world->getCrop(this->pos.x, this->pos.z);
        if (crop != nullptr && crop->getStage() == crop->getMaxStage())
        {
            this->world->harvest(this->pos.x, this->pos.z);
            this->gain({Item::potato, 1});
        } else
        {
            this->world->sow(this->pos.x, this->pos.z, CropProperties::potato);
        }
    }
    else
        this->world->setTile(this->pos.x, this->pos.z, TileType::Plowland);
}

void Player::gain(ItemStack const& itemStack)
{
    this->inventory.gain(itemStack);
}

ItemStack const &Player::getSlot(int i) const
{
    return this->inventory.getSlot(i);
}

AABB Player::getAABB() const
{
    return this->getAABB(this->pos);
}

AABB Player::getAABB(glm::vec3 const& pos) const
{
    return AABB(pos - glm::vec3(0.5, 0.0, 0.5), pos + glm::vec3(0.5, 2.0, 0.5));
}
