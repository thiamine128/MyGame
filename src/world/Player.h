#pragma once

#include "Items.h"
#include "entity/Entity.h"
#include "rendering/Model.h"
#include "util/AABB.h"
#include <glm/gtc/type_ptr.hpp>

class Player : public Entity
{
public:
    Player(World*);
    ~Player();

    void shoot(int);
    virtual void tick();
    void gainItem(Item*);
    int getHearts();
    int getHealth();
    double getAtk() const;
    float getRange() const;
    int getPotatoes() const;
    void setTripleShot();
    void addAtk(double);
    void addRange(float);
    void addShootSpeed(int);
    void addSpeed(float);
    void hurt(double);
    void heal();
    void addHeart(int);
    void placeMine();
    void gainPotato(int);
protected:
    int shotCooldown;
    int immuneTicks;
    int shootSpeed;
    bool tripleShot;
    double atk;
    int hearts;
    float range;
    int potatoes;
    std::vector<Item*> items;
};