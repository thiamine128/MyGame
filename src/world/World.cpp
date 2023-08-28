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
    this->room = LayerGenerator::generateRooms(this, 6, this->stage);
}

void World::prepareNextStage()
{
    this->prepareNext = true;
}
