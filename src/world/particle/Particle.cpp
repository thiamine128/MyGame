#include "Particle.h"

#include "Game.h"

Particle::Particle(glm::vec3 const& pos, glm::vec3 const& velocity, glm::vec3 const& color, int life) : pos(pos), velocity(velocity)
{
    this->life = this->maxLife = life;
    this->prevPos = pos;
    this->scale = this->prevScale = 1.0f;
    this->color = glm::vec4(color, 1.0);
}

void Particle::tick()
{
    this->life--;
    this->prevScale = this->scale;
    this->scale = (float) (this->life) / this->maxLife;
    this->prevPos = this->pos;
    this->pos += this->velocity * 0.05f;
}

bool Particle::alive()
{
    return life > 0;
}

glm::vec3 Particle::getPos()
{
    return glm::mix(this->prevPos, this->pos, Game::getInstance()->getDeltaTime() / 0.05f);
}

float Particle::getScale()
{
    return glm::mix(this->prevScale, this->scale, Game::getInstance()->getDeltaTime() / 0.05f);
}

glm::vec4 const &Particle::getColor() const
{
    return color;
}
