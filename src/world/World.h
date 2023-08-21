#pragma once

class Construction;

#include "Player.h"
#include "tile/Tile.h"
#include "building/Building.h"
#include "Chunk.h"

#include <vector>

#include <glm/gtc/type_ptr.hpp>

#define CHUNK_NUM 16

class World
{
public:
    World();
    ~World();

    void generateTrees();
    Player* getPlayer() const;
    void tick();
    glm::ivec2 getChunkPos(int, int) const;
    TileType getTile(int, int) const;
    void setTile(int, int, TileType);
    Chunk* getChunk(int, int) const;
    bool hasChunk(int, int) const;
    void sow(int, int, CropProperties*);
    void harvest(int, int);
    void buildConstruction(int, int, Construction*);
    const Crop* getCrop(int, int) const;
    void nextDay();
    void addBuilding(Building*);
    Building* getHouse() const;
    void getNearbyChunks(glm::vec2, std::vector<Chunk*>&) const;
protected:
    Player* player;
    Building* house;
    int days;
    Chunk* chunks[CHUNK_NUM][CHUNK_NUM];

    void setupHouse();
};