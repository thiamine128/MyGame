#pragma once

class Construction;

#include "Player.h"
#include "tile/Tile.h"
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
    std::vector<Construction*>& getConstructions();
    Player* getPlayer() const;
    void tick();
    glm::ivec2 getChunkPos(int, int) const;
    TileType getTile(int, int) const;
    void setTile(int, int, TileType);
    Chunk& getChunk(int, int);
    bool hasChunk(int, int) const;
    void sow(int, int, CropProperties*);
    void harvest(int, int);
    const Crop* getCrop(int, int) const;
    void nextDay();
protected:
    Player* player;
    int days;
    std::vector<Construction*> constructions;
    Chunk chunks[CHUNK_NUM][CHUNK_NUM];
};