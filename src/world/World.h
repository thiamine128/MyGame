#pragma once

#include "construction/Construction.h"
#include "Player.h"

#include <vector>

class World
{
public:
    World();
    ~World();

    void generateTrees();
    std::vector<Construction*>& getConstructions();
    Player* getPlayer() const;
    void tick();
protected:
    Player* player;
    std::vector<Construction*> constructions;
};