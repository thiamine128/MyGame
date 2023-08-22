#pragma once

#include "world/Chunk.h"
#include "Mesh.h"
#include "rendering/TextureUVSet.h"

class ChunkTessellator
{
public:
    static void initConstructionModels();
    static void tessellate(const Chunk*, Mesh*);
protected:
    static void tessellatePlane(glm::vec3, TextureUVSet const&, Mesh*);
    static void tessellateFence(glm::vec3, Mesh*, int);

    static std::unordered_map<ConstructionType, const Model*> constructionModels;
    static std::unordered_map<TileType, std::string> tileTexture;
};