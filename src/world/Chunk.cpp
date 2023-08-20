#include "Chunk.h"

#include "TextureManager.h"
#include "rendering/TextureUVSet.h"
#include "rendering/Vertex.h"

std::unordered_map<TileType, std::string> Chunk::textureName =
{
    {TileType::Ground, "ground"},
    {TileType::Plowland, "plowland"}
};

Chunk::Chunk()
{
    this->mesh = new Mesh();
    this->dirty = true;

    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            crops[i][j] = nullptr;
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

void Chunk::harvest(int x, int y)
{
    if (this->crops[x][y] != nullptr)
        delete this->crops[x][y];
    this->crops[x][y] = nullptr;
}

void Chunk::buildMesh()
{
    this->mesh->clear();
    
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            TileType tile = this->getTile(i, j);
            TextureUVSet const& uvs = TextureManager::tiles->getUVSet(textureName[tile]);
            Vertex v1 = {i + 1, 0, j + 1, 0, 1, 0, uvs.coords[0].x, uvs.coords[0].y};
            Vertex v2 = {i + 1, 0, j, 0, 1, 0, uvs.coords[1].x, uvs.coords[1].y};
            Vertex v3 = {i, 0, j, 0, 1, 0, uvs.coords[2].x, uvs.coords[2].y};
            Vertex v4 = {i, 0, j + 1, 0, 1, 0, uvs.coords[3].x, uvs.coords[3].y};
            this->mesh->quad(v1, v2, v3, v4);
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
}
