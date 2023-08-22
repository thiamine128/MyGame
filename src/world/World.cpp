#include "World.h"

#include "Game.h"
#include "building/House.h"
#include "building/Store.h"

#include <iostream>

World::World()
{
    for (int i = 0; i < CHUNK_NUM; ++i)
    {
        for (int j = 0; j < CHUNK_NUM; ++j)
        {
            this->chunks[i][j] = new Chunk(glm::ivec2(i - CHUNK_NUM / 2, j - CHUNK_NUM / 2));
        }
    }
    this->player = new Player(this);
    
    this->setupHouse();
    this->setupStore();
    this->timeInDay = 0;
}

World::~World()
{
    delete this->player;
    delete this->house;
    for (int i = 0; i < CHUNK_NUM; ++i)
    {
        for (int j = 0; j < CHUNK_NUM; ++j)
        {
            delete this->chunks[i][j];
        }
    }
}

void World::generateTrees()
{
    
}

Player *World::getPlayer() const
{
    return this->player;
}

void World::tick()
{
    this->player->tick();
    ++this->timeInDay;
    if (this->timeInDay == this->getTimePerDay())
    {
        this->timeInDay = 0;
        this->nextDay();
    }
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
    return chunks[chunkInd.x][chunkInd.y]->getTile(x, y);
}

#include <iostream>

void World::setTile(int x, int y, TileType type)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y]->setTile(x, y, type);
}

Chunk* World::getChunk(int x, int y) const
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
    chunks[chunkInd.x][chunkInd.y]->sow(x, y, crop);
}

void World::harvest(int x, int y)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y]->harvest(x, y);
}

bool World::canBuildAt(int x, int y, Construction* construction)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y]->canBuildAt(x, y, construction);
}

int dx[] = {0, -1, 1, 0};
int dy[] = {-1, 0, 0, 1};

void World::buildConstruction(int x, int y, Construction* construction)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    int ox = x, oy = y;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    chunks[chunkInd.x][chunkInd.y]->buildConstruction(x, y, construction);
    if (construction == Construction::fence)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (this->getConstruction(ox + dx[i], oy + dy[i], 1) == Construction::fence)
            {
                int v = this->getFenceConnection(ox, oy);
                v |= (1 << i);
                this->updateFenceConnection(ox, oy, v);
                v = this->getFenceConnection(ox + dx[i], oy + dy[i]);
                v |= (1 << (3 - i));
                this->updateFenceConnection(ox + dx[i], oy + dy[i], v);
            }
        }
    }
}

Construction *World::getConstruction(int x, int y, int z)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y]->getConstruction(x, y, z);
}

const Crop *World::getCrop(int x, int y) const
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y]->getCrop(x, y);
}

void World::nextDay()
{
    this->days++;

    for (int i = 0; i < CHUNK_NUM; ++i)
    {
        for (int j = 0; j < CHUNK_NUM; ++j)
        {
            this->chunks[i][j]->nextDay();
        }
    }
}

void World::addBuilding(Building* building)
{
    glm::vec3 pos = building->getPos();
    glm::ivec2 chunkInd = getChunkPos(pos.x, pos.z) + CHUNK_NUM / 2;
    return chunks[chunkInd.x][chunkInd.y]->addBuilding(building);
}

Building *World::getHouse() const
{
    return this->house;
}

void World::getNearbyChunks(glm::vec2 pos, std::vector<Chunk*>& list) const
{
    glm::ivec2 p = this->getChunkPos(pos.x, pos.y);
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (this->hasChunk(p.x + i, p.y + j)) {
                list.emplace_back(this->getChunk(p.x + i, p.y + j));
            }
        }
    }
}

int World::getTime() const
{
    return this->timeInDay;
}

int World::getTimePerDay() const
{
    return 200;
}

void World::setupHouse()
{
    this->house = new House(glm::vec3(8.0, -0.001, 8.0));

    for (int i = 4; i < 12; ++i)
    {
        for (int j = 4; j < 12; ++j)
        {
            this->buildConstruction(i, j, Construction::planks);
        }
    }

    this->buildConstruction(4, 10, Construction::bed);
    this->addBuilding(this->house);
}

void World::setupStore()
{
    this->store = new Store(glm::vec3(-6.0, -0.0001, 8.0));

    this->addBuilding(this->store);
}

int World::getFenceConnection(int x, int y)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y]->getFenceConnection(x, y);
}

void World::updateFenceConnection(int x, int y, int value)
{
    glm::ivec2 chunkInd = getChunkPos(x, y) + CHUNK_NUM / 2;
    x %= 16, y %= 16;
    if (x < 0) x += 16;
    if (y < 0) y += 16;
    return chunks[chunkInd.x][chunkInd.y]->updateFenceConnection(x, y, value);
}
