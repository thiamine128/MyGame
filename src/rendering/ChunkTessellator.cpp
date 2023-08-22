#include "ChunkTessellator.h"

#include "TextureManager.h"
#include "Vertex.h"

#include <iostream>

std::unordered_map<ConstructionType, const Model*> ChunkTessellator::constructionModels;
std::unordered_map<TileType, std::string> ChunkTessellator::tileTexture =
{
    {TileType::Ground, "ground"},
    {TileType::Plowland, "plowland"}
};

void ChunkTessellator::initConstructionModels()
{
    constructionModels[ConstructionType::PLANKS] = new Model("assets/model/construction/planks.obj", TextureManager::tiles->getUVSet("planks"));
    constructionModels[ConstructionType::BEDS] = new Model("assets/model/construction/bed.obj", TextureManager::tiles->getUVSet("bed"));
    constructionModels[ConstructionType::FENCE] = new Model("assets/model/construction/fence.obj", TextureManager::tiles->getUVSet("fence"));
}

void ChunkTessellator::tessellate(const Chunk *chunk, Mesh *mesh)
{
    mesh->clear();
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            TileType tile = chunk->getTile(i, j);
            TextureUVSet const& uv = TextureManager::tiles->getUVSet(tileTexture[tile]);
            tessellatePlane(glm::ivec3(i, 0, j), uv, mesh);

            for (int k = 0; k < 2; ++k)
            {
                Construction* construction = chunk->getConstruction(i, j, k);
                if (construction != nullptr) {
                    if (construction != Construction::fence)
                    {
                        auto meshes = constructionModels[construction->getType()]->getMeshes();
                        for (auto meshToMerge : meshes)
                        {
                            mesh->merge(meshToMerge, glm::vec3(i + 0.5, 0.0, j + 0.5));
                        }
                    } else
                    {
                        tessellateFence(glm::vec3(i + 0.5, 0.0, j + 0.5), mesh, chunk->getFenceConnection(i, j));
                    }
                }
            }
        }
    }
    mesh->build();
}

void ChunkTessellator::tessellatePlane(glm::vec3 pos, TextureUVSet const& uvs, Mesh* mesh)
{
    Vertex v1 = {pos.x + 1, pos.y, pos.z + 1, 0, 1, 0, uvs.coords[0].x, uvs.coords[0].y};
    Vertex v2 = {pos.x + 1, pos.y, pos.z, 0, 1, 0, uvs.coords[1].x, uvs.coords[1].y};
    Vertex v3 = {pos.x, pos.y, pos.z, 0, 1, 0, uvs.coords[3].x, uvs.coords[3].y};
    Vertex v4 = {pos.x, pos.y, pos.z + 1, 0, 1, 0, uvs.coords[2].x, uvs.coords[2].y};
    mesh->quad(v1, v2, v3, v4);
}

void ChunkTessellator::tessellateFence(glm::vec3 pos, Mesh* mesh, int conn)
{
    auto meshes = constructionModels[ConstructionType::FENCE]->getMeshes();
    mesh->merge(meshes[0], pos);
    int m[] = {2, 1, 3, 4};
    for (int i = 0; i < 4; ++i)
    {
        if (conn & (1 << i))
        {
            mesh->merge(meshes[m[i]], pos);
        }
    }
}
