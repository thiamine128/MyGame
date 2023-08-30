#include "Player.h"

#include "Game.h"
#include "ModelManager.h"
#include "entity/Bullet.h"
#include "SoundManager.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
Player::Player(World* world) : Entity(world, glm::vec3(0.0), AABB({0, 0, 0}, {0.8, 2, 0.8}))
{

    this->model = ModelManager::getModel("assets/models/peashooter.obj");

    this->shootSpeed = 10;
    this->shotCooldown = 0;
    this->health = 3.0f;
    this->hearts = 6;
    this->speed = 3.0f;
    this->immuneTicks = 0;
    this->atk = 1.0;
    this->range = 1.0f;
    this->tripleShot = false;
}

Player::~Player()
{
}

void Player::shoot(int dir)
{
    glm::vec3 v0[] = 
    {
        {0.0, 0.0, -1.0},
        {-1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0}
    };
    if (this->shotCooldown <= 0)
    {
        if (this->tripleShot)
        {
            for (int i = -1; i <= 1; ++i)
            {
                int d = dir + i;
                if (d < 0) d += 4;
                if (d >= 4) d -= 4;
                auto bullet = new Bullet(this->world, this->pos + glm::vec3(0.0, 0.7, 0.0), this->velocity * 0.2f + 4.0f * glm::normalize(v0[dir] + 0.5f * v0[d]), 0.3f);
                Bullet::apply(bullet, this, this->items);
                this->world->getRoom()->addEntity(bullet);
                this->shotCooldown = this->shootSpeed;
            }
        } else
        {
            auto bullet = new Bullet(this->world, this->pos + glm::vec3(0.0, 0.7, 0.0), this->velocity * 0.2f + 4.0f * v0[dir], 0.3f);
            Bullet::apply(bullet, this, this->items);
            this->world->getRoom()->addEntity(bullet);
            this->shotCooldown = this->shootSpeed;
        }
        SoundManager::play("assets/sounds/shoot.wav");
    }
    this->rotation = glm::radians(90.0f * dir);
}

void Player::tick()
{
    Controller* controller = Game::getInstance()->getController();
    this->velocity = controller->getVelocity() * this->speed;
    Entity::tick();
    if (shotCooldown > 0) --shotCooldown;
    if (controller->isKeyPressed(GLFW_KEY_LEFT))
    {
        this->shoot(3);
    } else if (controller->isKeyPressed(GLFW_KEY_RIGHT))
    {
        this->shoot(1);
    } else if (controller->isKeyPressed(GLFW_KEY_UP))
    {
        this->shoot(2);
    } else if (controller->isKeyPressed(GLFW_KEY_DOWN))
    {
        this->shoot(0);
    }
    if (this->immuneTicks > 0)
    {
        this->immuneTicks --;
    }
}

void Player::gainItem(Item* item)
{
    this->items.push_back(item);
    Item::onPickup(item, this);
}

int Player::getHearts()
{
     return hearts;
}

int Player::getHealth()
{
    return this->health * 2;
}

double Player::getAtk() const
{
    return this->atk;
}

float Player::getRange() const
{
    return this->range;
}

void Player::setTripleShot()
{
    this->tripleShot = true;
}

void Player::addAtk(double v)
{
    this->atk += v;
}

void Player::addRange(float v)
{
    this->range += v;
}

void Player::addShootSpeed(int ticks)
{
    this->shootSpeed -= ticks;
}

void Player::addSpeed(float v)
{
    this->speed += v;
}

void Player::hurt(double d)
{
    if (this->immuneTicks <= 0)
    {
        this->health -= d;
        this->immuneTicks = 40;
    }
}

void Player::heal()
{
    if (this->getHealth() + 1 <= this->getHearts())
    {
        this->health += 0.5;
    }
}

void Player::addHeart(int v)
{
    hearts += v;
    health += 0.5 * v;
}
