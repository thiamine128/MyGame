#pragma once

#include "crop/Crop.h"
#include "tile/Tile.h"
#include "rendering/Mesh.h"
#include "rendering/VertexBufferObject.h"
#include <glm/gtc/type_ptr.hpp>

class Chunk
{
public:
    Chunk();
    ~Chunk();
    TileType getTile(int, int) const;
    void setTile(int, int, TileType);
    void sow(int, int, CropProperties*);
    const Mesh* getMesh();
    const Crop* getCrop(int, int) const;
    void harvest(int, int);
    void buildMesh();
    void nextDay();
protected:
    Tile tiles[16][16];
    Crop* crops[16][16];
    bool dirty;
    Mesh* mesh;

    static std::unordered_map<TileType, std::string> textureName;
};