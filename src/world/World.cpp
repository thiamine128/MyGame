#include "World.h"

#include "Game.h"
#include "LayerGenerator.h"

#include <iostream>

//创建世界
World::World()
{
    this->player = new Player(this);
    this->stage = 0;
    this->nextStage();
    this->score = 10000;
    this->scoreTick = 20;
    this->newRec = false;
    this->finished = false;
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

//世界逻辑更新
void World::tick()
{
    this->player->tick();
    this->room->tick();

    if (this->scoreTick == 0 && !finished)
        this->score--, this->scoreTick = 20;
    else
        this->scoreTick--;

    if (this->prepareNext)
    {
        this->nextStage();
    }
}

//进入下一层
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

void World::addScore(int v)
{
    this->score += v;
}

int World::getScore() const
{
    return this->score;
}

//退出游戏时资源释放
void World::finish()
{
    this->finished = true;
    newRec =  Game::getInstance()->updateScore(score);
    Game::getInstance()->getScreenManager()->pushWinScreen();
}
