#include "World.h"

#include "Game.h"
#include "LayerGenerator.h"

#include <iostream>

World::World()
{
    this->player = new Player(this);
    this->stage = 0;
    this->nextStage();
}

World::~World()
{
    delete this->player;
    LayerGenerator::clear();
}

Player *World::getPlayer() const
{
    return this->player;
}

Room *World::getRoom() const
{
    return this->room;
}

Room *World::getRoom(int x, int y) const
{
    return grid[x][y];
}

void World::setRoom(Room* room)
{
    this->room = room;
}

void World::tick()
{
    this->player->tick();
    this->room->tick();

    if (this->prepareNext)
    {
        this->nextStage();
    }
}

void World::nextStage()
{
    this->stage++;
    LayerGenerator::clear();
    this->prepareNext = false;
    this->room = LayerGenerator::generateRooms(this, 10, this->stage);
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            this->grid[i][j] = LayerGenerator::m[i][j];
        }
    }
}

void World::prepareNextStage()
{
    this->prepareNext = true;
}
