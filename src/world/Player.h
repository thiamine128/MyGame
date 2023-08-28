#pragma once

#include "Items.h"
#include "Entity.h"
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
    void addAtk(double);
    void addRange(float);
    void addShootSpeed(int);
    void hurt(double);
protected:
    int shotCooldown;
    int immuneTicks;
    int shootSpeed;
    double atk;
    float range;
    std::vector<Item*> items;
};