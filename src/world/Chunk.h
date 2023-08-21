#pragma once

#include "crop/Crop.h"
#include "tile/Tile.h"
#include "building/Building.h"
#include "construction/Construction.h"
#include "rendering/Mesh.h"
#include "rendering/VertexBufferObject.h"
#include "rendering/TextureUVSet.h"
#include <glm/gtc/type_ptr.hpp>

class Chunk
{
public:
    Chunk(glm::ivec2);
    ~Chunk();
    TileType getTile(int, int) const;
    void setTile(int, int, TileType);
    void sow(int, int, CropProperties*);
    const Mesh* getMesh();
    const Crop* getCrop(int, int) const;
    Construction* getConstruction(int, int, int) const;
    void harvest(int, int);
    bool canBuildAt(int, int, Construction*) const;
    void buildConstruction(int, int, Construction*);
    void addBuilding(Building*);
    void buildMesh();
    void nextDay();
    std::vector<Building*>& getBuildings();
    glm::ivec2 const& getChunkPos() const;
    bool collide(AABB const&) const;
protected:
    Tile tiles[16][16];
    Crop* crops[16][16];
    Construction* constructions[16][16][2];
    std::vector<Building*> buildings;
    bool dirty;
    Mesh* mesh;
    glm::ivec2 pos;

    static std::unordered_map<TileType, std::string> tileTexture;

    void tesselatePlane(glm::vec3, TextureUVSet const&, Mesh*) const;
    void tesselateFace(glm::vec3, glm::vec3, unsigned int, TextureUVSet const&, Mesh*) const;
    void tesselatePlanks(glm::ivec3, Mesh*) const;
};