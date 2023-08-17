#include "Player.h"

#include "Game.h"

#include <iostream>

Player::Player()
{
    this->pos = glm::vec3(0.0);
    this->velocity = glm::vec3(0.0);
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

void Player::tick()
{
    this->velocity = Game::getInstance()->getController()->getVelocity();
    this->prevPos = this->pos;
    this->pos += this->velocity * 0.05f;
}
