#include "World.h"

#include "world/construction/Tree.h"

World::World()
{
    this->player = new Player();
    this->generateTrees();
}

World::~World()
{
    delete this->player;
}

void World::generateTrees()
{
    for (int i = 0; i < 5; ++i)
    this->constructions.push_back(new Tree(glm::vec3(0.0, 0.0, i * 2.0)));
}

std::vector<Construction*> &World::getConstructions()
{
    return this->constructions;
}

Player *World::getPlayer() const
{
    return this->player;
}

void World::tick()
{
    this->player->tick();
}
