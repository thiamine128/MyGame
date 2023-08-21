#include "Chunk.h"

#include "TextureManager.h"
#include "rendering/Vertex.h"

std::unordered_map<TileType, std::string> Chunk::tileTexture =
{
    {TileType::Ground, "ground"},
    {TileType::Plowland, "plowland"}
};

Chunk::Chunk(glm::ivec2 pos) : pos(pos)
{
    this->mesh = new Mesh();
    this->dirty = true;

    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            crops[i][j] = nullptr;
            constructions[i][j][0] = constructions[i][j][1] = nullptr;
        }
    }
}

Chunk::~Chunk()
{
    delete this->mesh;
}

TileType Chunk::getTile(int x, int y) const
{
    return this->tiles[x][y].getType();
}

void Chunk::setTile(int x, int y, TileType type)
{
    if (this->tiles[x][y].getType() != type)
        this->dirty = true;
    this->tiles[x][y].setType(type);
}

void Chunk::sow(int x, int y, CropProperties* crop)
{
    if (this->crops[x][y] == nullptr)
    {
        this->crops[x][y] = new Crop(CropProperties::potato, glm::ivec2(x, y));
        this->dirty = true;
    }
}

const Mesh* Chunk::getMesh()
{
    if (this->dirty) {
        this->buildMesh();
        this->dirty = false;
    }
    return this->mesh;
}

const Crop* Chunk::getCrop(int x, int y) const
{
    return this->crops[x][y];
}

Construction *Chunk::getConstruction(int i, int j, int k) const
{
    return this->constructions[i][j][k];
}

void Chunk::harvest(int x, int y)
{
    if (this->crops[x][y] != nullptr)
        delete this->crops[x][y];
    this->crops[x][y] = nullptr;
}

bool Chunk::canBuildAt(int x, int y, Construction* construction) const
{
    switch (construction->getBuildType())
    {
        case BuildType::BASE:
            if (this->constructions[x][y][0] == nullptr && this->constructions[x][y][1] == nullptr)
            {
                return true;
            }
            break;
        case BuildType::FLOOR:
            if (this->constructions[x][y][0] == nullptr && this->constructions[x][y][1] == nullptr)
            {
                return true;
            }
            break;
        case BuildType::BLOCK:
            if (this->constructions[x][y][1] == nullptr && (this->constructions[x][y][0] == nullptr || this->constructions[x][y][0]->getBuildType() == BuildType::FLOOR))
            {
                return true;
            }
            break;
    }
    return false;
}

#include <iostream>

void Chunk::buildConstruction(int x, int y, Construction* construction)
{
    if (this->canBuildAt(x, y, construction))
    {
        BuildType const& type = construction->getBuildType();
        if (type == BuildType::FLOOR)
            this->constructions[x][y][0] = construction;
        else
            this->constructions[x][y][1] = construction;
    }
}

void Chunk::addBuilding(Building* building)
{
    this->buildings.push_back(building);
}

void Chunk::buildMesh()
{
    this->mesh->clear();
    
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            TileType tile = this->getTile(i, j);
            TextureUVSet const& uv = TextureManager::tiles->getUVSet(tileTexture[tile]);
            this->tesselatePlane(glm::ivec3(i, 0, j), uv, this->mesh);

            for (int k = 0; k < 2; ++k)
            {
                Construction* constructions = this->constructions[i][j][k];
                if (constructions == Construction::planks)
                {
                    this->tesselatePlanks(glm::vec3(i, 0.1, j), this->mesh);
                }
            }
        }
    }
    this->mesh->build();
}

void Chunk::nextDay()
{
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            Crop* crop = this->crops[i][j];
            if (crop != nullptr) {
                if (crop->getStage() < crop->getMaxStage())
                    crop->setDay(crop->getDay() + 1);
            }
        }
    }

    this->dirty = true;
}

std::vector<Building *> &Chunk::getBuildings()
{
    return this->buildings;
}

glm::ivec2 const &Chunk::getChunkPos() const
{
    return this->pos;
}

bool Chunk::collide(AABB const& aabb) const
{
    for (auto building : buildings)
    {
        auto aabbs = building->getCollisions();
        for (auto buildingAABB : aabbs) {
            if (aabb.collideWith(buildingAABB))
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                if (this->constructions[i][j][k] != nullptr && this->constructions[i][j][k]->hasCollision())
                {
                    if (this->constructions[i][j][k]->getAABB().offset(glm::vec3(this->pos.x * 16.0 + i, 0.0, this->pos.y * 16.0 + j)).collideWith(aabb))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Chunk::tesselatePlane(glm::vec3 pos, TextureUVSet const& uvs, Mesh* mesh) const
{
    Vertex v1 = {pos.x + 1, pos.y, pos.z + 1, 0, 1, 0, uvs.coords[0].x, uvs.coords[0].y};
    Vertex v2 = {pos.x + 1, pos.y, pos.z, 0, 1, 0, uvs.coords[1].x, uvs.coords[1].y};
    Vertex v3 = {pos.x, pos.y, pos.z, 0, 1, 0, uvs.coords[3].x, uvs.coords[3].y};
    Vertex v4 = {pos.x, pos.y, pos.z + 1, 0, 1, 0, uvs.coords[2].x, uvs.coords[2].y};
    mesh->quad(v1, v2, v3, v4);
}

void Chunk::tesselatePlanks(glm::ivec3 pos, Mesh* mesh) const
{
    this->tesselatePlane(glm::vec3(pos.x, pos.y + 0.001f, pos.z), TextureManager::tiles->getUVSet("planks"), this->mesh);
}
