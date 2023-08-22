#include "Chunk.h"

#include "TextureManager.h"
#include "rendering/Vertex.h"

#include "rendering/ChunkTessellator.h"

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
            fenceConnection[i][j] = 0;
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
        ChunkTessellator::tessellate(this, this->mesh);
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

void Chunk::buildConstruction(int x, int y, Construction* construction)
{
    if (this->canBuildAt(x, y, construction))
    {
        BuildType const& type = construction->getBuildType();
        if (type == BuildType::FLOOR)
            this->constructions[x][y][0] = construction;
        else
            this->constructions[x][y][1] = construction;
        
        this->dirty = true;
    }
}

void Chunk::updateFenceConnection(int x, int y, int value)
{
    this->fenceConnection[x][y] = value;
    this->dirty = true;
}

int Chunk::getFenceConnection(int x, int y) const
{
    return this->fenceConnection[x][y];
}

void Chunk::addBuilding(Building* building)
{
    this->buildings.push_back(building);
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