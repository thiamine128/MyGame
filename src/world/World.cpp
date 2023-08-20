#include "World.h"

#include "world/construction/Tree.h"
#include "Game.h"

World::World()
{
    this->player = new Player(this);
    this->generateTrees();
}

World::~World()
{
    delete this->player;
}

void World::generateTrees()
{
    for (int i = 0; i < 5; ++i)
        this->constructions.push_back(new Tree(glm::vec3(0.0, 0.0, i * 3.0)));
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

glm::ivec2 World::getChunkPos(int x, int y) const
{
    return glm::ivec2(floor((double) x / 16.0), floor((double) y / 16.0));
}

TileType World::getTile(int x, int y) const
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
     x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y].getTile(x, y);
}

#include <iostream>

void World::setTile(int x, int y, TileType type)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y].setTile(x, y, type);
}

Chunk& World::getChunk(int x, int y)
{
    return this->chunks[x + CHUNK_NUM / 2][y + CHUNK_NUM / 2];
}

bool World::hasChunk(int x, int y) const
{
    glm::ivec2 p = getChunkPos(x, y) + CHUNK_NUM / 2;
    return p.x >= 0 && p.y >= 0 && p.x < CHUNK_NUM && p.y < CHUNK_NUM;
}

void World::sow(int x, int y, CropProperties* crop)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y].sow(x, y, crop);
}

void World::harvest(int x, int y)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y].harvest(x, y);
}

const Crop *World::getCrop(int x, int y) const
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y].getCrop(x, y);
}

void World::nextDay()
{
    this->days++;

    for (int i = 0; i < CHUNK_NUM; ++i)
    {
        for (int j = 0; j < CHUNK_NUM; ++j)
        {
            this->chunks[i][j].nextDay();
        }
    }
}
