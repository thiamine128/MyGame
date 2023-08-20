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
    this->prevPos = this->pos;
    this->pos += this->velocity * 0.05f;
}

void Player::plow()
{
    if (this->world->getTile(this->pos.x, this->pos.z) == TileType::Plowland)
    {
        const Crop* crop = this->world->getCrop(this->pos.x, this->pos.z);
        if (crop != nullptr && crop->getStage() == crop->getMaxStage())
        {
            this->world->harvest(this->pos.x, this->pos.z);
        } else
        {
            this->world->sow(this->pos.x, this->pos.z, CropProperties::potato);
        }
    }
    else
        this->world->setTile(this->pos.x, this->pos.z, TileType::Plowland);
}
